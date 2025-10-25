import os  # 导入操作系统相关的模块
import time  # 导入时间相关的模块
import torch  # 导入PyTorch库
import matplotlib.pyplot as plt  # 导入绘图库
import numpy as np  # 导入NumPy库
from termcolor import cprint  # 导入用于彩色打印的模块
from utils_torch_filter import TORCHIEKF  # 从自定义模块导入TORCHIEKF类
from utils import prepare_data  # 从自定义模块导入prepare_data函数
import copy  # 导入复制模块

max_loss = 2e1  # 定义最大损失值
max_grad_norm = 1e0  # 定义最大梯度范数
min_lr = 1e-5  # 定义最小学习率
criterion = torch.nn.MSELoss(reduction="sum")  # 定义均方误差损失函数
lr_initprocesscov_net = 1e-4  # 初始化过程协方差网络的学习率
weight_decay_initprocesscov_net = 0e-8  # 初始化过程协方差网络的权重衰减
lr_mesnet = {'cov_net': 1e-4,  # 定义协方差网络的学习率
             'cov_lin': 1e-4,  # 定义线性协方差网络的学习率
            }
weight_decay_mesnet = {'cov_net': 1e-8,  # 定义协方差网络的权重衰减
                       'cov_lin': 1e-8,  # 定义线性协方差网络的权重衰减
                      }

def compute_delta_p(Rot, p):  # 定义计算位移增量的函数
    list_rpe = [[], [], []]  # 初始化一个列表，用于存储索引和位移增量

    # 以1 Hz的频率进行采样
    Rot = Rot[::10]  # 每10个元素取一个
    p = p[::10]  # 每10个元素取一个

    step_size = 10  # 每秒的步长
    distances = np.zeros(p.shape[0])  # 初始化距离数组
    dp = p[1:] - p[:-1]  # 计算真实位移
    distances[1:] = dp.norm(dim=1).cumsum(0).numpy()  # 计算累积距离

    seq_lengths = [100, 200, 300, 400, 500, 600, 700, 800]  # 定义序列长度
    k_max = int(Rot.shape[0] / step_size) - 1  # 计算最大索引

    for k in range(0, k_max):  # 遍历每个时间步
        idx_0 = k * step_size  # 计算起始索引
        for seq_length in seq_lengths:  # 遍历每个序列长度
            if seq_length + distances[idx_0] > distances[-1]:  # 检查是否超出最大距离
                continue
            idx_shift = np.searchsorted(distances[idx_0:], distances[idx_0] + seq_length)  # 查找结束索引
            idx_end = idx_0 + idx_shift  # 计算结束索引

            list_rpe[0].append(idx_0)  # 添加起始索引
            list_rpe[1].append(idx_end)  # 添加结束索引

        idxs_0 = list_rpe[0]  # 获取起始索引列表
        idxs_end = list_rpe[1]  # 获取结束索引列表
        delta_p = Rot[idxs_0].transpose(-1, -2).matmul(  # 计算位移增量
            ((p[idxs_end] - p[idxs_0]).float()).unsqueeze(-1)).squeeze()

        list_rpe[2] = delta_p  # 将位移增量存入列表
    return list_rpe  # 返回结果列表

def train_filter(args, dataset):  # 定义训练滤波器的函数
    # 准备滤波器，返回一个iekf实例
    iekf = prepare_filter(args, dataset)  # 准备滤波器
    # 准备损失数据
    prepare_loss_data(args, dataset)  # 准备损失数据
    # 保存iekf模型
    save_iekf(args, iekf)  # 保存模型
    # 设置优化器
    optimizer = set_optimizer(iekf)  # 设置优化器
    # 记录开始时间
    start_time = time.time()  # 记录当前时间

    # 进行训练，遍历每个epoch
    for epoch in range(1, args.epochs + 1):  # 遍历每个训练周期
        # 执行训练循环
        train_loop(args, dataset, epoch, iekf, optimizer, args.seq_dim)  # 进行训练
        # 保存当前的iekf模型
        save_iekf(args, iekf)  # 保存模型
        # 打印当前epoch所花费的时间
        print("Amount of time spent for 1 epoch: {}s\n".format(int(time.time() - start_time)))  # 打印时间
        # 重置开始时间
        start_time = time.time()  # 重置时间

def prepare_filter(args, dataset):  # 定义准备滤波器的函数
    iekf = TORCHIEKF()  # 创建TORCHIEKF实例

    # set dataset parameter
    iekf.filter_parameters = args.parameter_class()  # 设置滤波器参数
    iekf.set_param_attr()  # 设置参数属性
    if type(iekf.g).__module__ == np.__name__:  # 检查g的类型
        iekf.g = torch.from_numpy(iekf.g).double()  # 转换为PyTorch张量

    # load model
    if args.continue_training:  # 如果继续训练
        iekf.load(args, dataset)  # 加载模型
    iekf.train()  # 设置为训练模式
    # init u_loc and u_std
    iekf.get_normalize_u(dataset)  # 初始化位置和标准差
    return iekf  # 返回iekf实例

def prepare_loss_data(args, dataset):  # 定义准备损失数据的函数

    file_delta_p = os.path.join(args.path_temp, 'delta_p.p')  # 定义临时文件路径
    if os.path.isfile(file_delta_p):  # 如果文件存在
        mondict = dataset.load(file_delta_p)  # 加载数据
        dataset.list_rpe = mondict['list_rpe']  # 获取训练数据
        dataset.list_rpe_validation = mondict['list_rpe_validation']  # 获取验证数据
        if set(dataset.datasets_train_filter.keys()) <= set(dataset.list_rpe.keys()):  # 检查训练数据是否完整
            return  # 如果完整则返回

    # prepare delta_p_gt
    list_rpe = {}  # 初始化列表
    for dataset_name, Ns in dataset.datasets_train_filter.items():  # 遍历训练数据集
        t, ang_gt, p_gt, v_gt, u = prepare_data(args, dataset, dataset_name, 0)  # 准备数据
        p_gt = p_gt.double()  # 转换为双精度
        Rot_gt = torch.zeros(Ns[1], 3, 3)  # 初始化旋转矩阵
        for k in range(Ns[1]):  # 遍历每个样本
            ang_k = ang_gt[k]  # 获取角度
            Rot_gt[k] = TORCHIEKF.from_rpy(ang_k[0], ang_k[1], ang_k[2]).double()  # 转换为旋转矩阵
        list_rpe[dataset_name] = compute_delta_p(Rot_gt[:Ns[1]], p_gt[:Ns[1]])  # 计算位移增量

    list_rpe_validation = {}  # 初始化验证列表
    for dataset_name, Ns in dataset.datasets_validatation_filter.items():  # 遍历验证数据集
        t, ang_gt, p_gt, v_gt, u = prepare_data(args, dataset, dataset_name, 0)  # 准备数据
        p_gt = p_gt.double()  # 转换为双精度
        Rot_gt = torch.zeros(Ns[1], 3, 3)  # 初始化旋转矩阵
        for k in range(Ns[1]):  # 遍历每个样本
            ang_k = ang_gt[k]  # 获取角度
            Rot_gt[k] = TORCHIEKF.from_rpy(ang_k[0], ang_k[1], ang_k[2]).double()  # 转换为旋转矩阵
        list_rpe_validation[dataset_name] = compute_delta_p(Rot_gt[:Ns[1]], p_gt[:Ns[1]])  # 计算位移增量
    
    list_rpe_ = copy.deepcopy(list_rpe)  # 深拷贝训练数据
    dataset.list_rpe = {}  # 初始化训练数据列表
    for dataset_name, rpe in list_rpe_.items():  # 遍历训练数据
        if len(rpe[0]) is not 0:  # 如果数据不为空
            dataset.list_rpe[dataset_name] = list_rpe[dataset_name]  # 添加到训练数据列表
        else:  # 如果数据为空
            dataset.datasets_train_filter.pop(dataset_name)  # 从训练数据集中移除
            list_rpe.pop(dataset_name)  # 从列表中移除
            cprint("%s has too much dirty data, it's removed from training list" % dataset_name, 'yellow')  # 打印警告

    list_rpe_validation_ = copy.deepcopy(list_rpe_validation)  # 深拷贝验证数据
    dataset.list_rpe_validation = {}  # 初始化验证数据列表
    for dataset_name, rpe in list_rpe_validation_.items():  # 遍历验证数据
        if len(rpe[0]) is not 0:  # 如果数据不为空
            dataset.list_rpe_validation[dataset_name] = list_rpe_validation[dataset_name]  # 添加到验证数据列表
        else:  # 如果数据为空
            dataset.datasets_validatation_filter.pop(dataset_name)  # 从验证数据集中移除
            list_rpe_validation.pop(dataset_name)  # 从列表中移除
            cprint("%s has too much dirty data, it's removed from validation list" % dataset_name, 'yellow')  # 打印警告
    mondict = {  # 创建字典以保存数据
        'list_rpe': list_rpe, 'list_rpe_validation': list_rpe_validation,
    }
    dataset.dump(mondict, file_delta_p)  # 保存数据到文件

def train_loop(args, dataset, epoch, iekf, optimizer, seq_dim):  # 定义训练循环的函数
    loss_train = 0  # 初始化训练损失
    optimizer.zero_grad()  # 清零梯度
    for i, (dataset_name, Ns) in enumerate(dataset.datasets_train_filter.items()):  # 遍历训练数据集
        t, ang_gt, p_gt, v_gt, u, N0 = prepare_data_filter(dataset, dataset_name, Ns, iekf, seq_dim)  # 准备数据

        loss = mini_batch_step(dataset, dataset_name, iekf, dataset.list_rpe[dataset_name], t, ang_gt, p_gt, v_gt, u, N0)  # 计算损失

        if loss is -1 or torch.isnan(loss):  # 检查损失是否无效
            cprint("{} loss is invalid".format(i), 'yellow')  # 打印警告
            continue  # 跳过
        elif loss > max_loss:  # 检查损失是否过高
            cprint("{} loss is too high {:.5f}".format(i, loss), 'yellow')  # 打印警告
            continue  # 跳过
        else:  # 如果损失有效
            loss_train += loss  # 累加损失
            cprint("{} loss: {:.5f}".format(i, loss))  # 打印损失

    if loss_train == 0:  # 如果没有损失
        return  # 返回
    loss_train.backward()  # 反向传播损失
    g_norm = torch.nn.utils.clip_grad_norm_(iekf.parameters(), max_grad_norm)  # 限制梯度范数
    if np.isnan(g_norm) or g_norm > 3*max_grad_norm:  # 检查梯度范数是否无效或过大
        cprint("gradient norm: {:.5f}".format(g_norm), 'yellow')  # 打印警告
        optimizer.zero_grad()  # 清零梯度

    else:  # 如果梯度正常
        optimizer.step()  # 更新参数
        optimizer.zero_grad()  # 清零梯度
        cprint("gradient norm: {:.5f}".format(g_norm))  # 打印梯度范数
    print('Train Epoch: {:2d} \tLoss: {:.5f}'.format(epoch, loss_train))  # 打印当前周期的损失
    return loss_train  # 返回损失

def save_iekf(args, iekf):  # 定义保存iekf模型的函数
    file_name = os.path.join(args.path_temp, "iekfnets.p")  # 定义保存路径
    torch.save(iekf.state_dict(), file_name)  # 保存模型状态
    print("The IEKF nets are saved in the file " + file_name)  # 打印保存信息

def mini_batch_step(dataset, dataset_name, iekf, list_rpe, t, ang_gt, p_gt, v_gt, u, N0):  # 定义小批量训练步骤的函数
    iekf.set_Q()  # 设置过程噪声
    measurements_covs = iekf.forward_nets(u)  # 前向传播计算测量协方差
    Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i = iekf.run(t, u, measurements_covs, v_gt, p_gt, t.shape[0], ang_gt[0])  # 运行iekf
    delta_p, delta_p_gt = precompute_lost(Rot, p, list_rpe, N0)  # 预计算损失
    if delta_p is None:  # 如果位移增量无效
        return -1  # 返回无效标志
    loss = criterion(delta_p, delta_p_gt)  # 计算损失
    return loss  # 返回损失

def set_optimizer(iekf):  # 定义设置优化器的函数
    param_list = [{'params': iekf.initprocesscov_net.parameters(),  # 添加过程协方差网络的参数
                   'lr': lr_initprocesscov_net,  # 设置学习率
                   'weight_decay': weight_decay_initprocesscov_net}]  # 设置权重衰减
    for key, value in lr_mesnet.items():  # 遍历协方差网络的参数
        param_list.append({'params': getattr(iekf.mes_net, key).parameters(),  # 添加参数
                           'lr': value,  # 设置学习率
                           'weight_decay': weight_decay_mesnet[key]  # 设置权重衰减
                           })
    optimizer = torch.optim.Adam(param_list)  # 创建Adam优化器
    return optimizer  # 返回优化器

def prepare_data_filter(dataset, dataset_name, Ns, iekf, seq_dim):  # 定义准备数据的函数
    # get data with trainable instant
    t, ang_gt, p_gt, v_gt, u = dataset.get_data(dataset_name)  # 获取数据
    t = t[Ns[0]: Ns[1]]  # 切片获取时间
    ang_gt = ang_gt[Ns[0]: Ns[1]]  # 切片获取角度
    p_gt = p_gt[Ns[0]: Ns[1]] - p_gt[Ns[0]]  # 切片获取位置并归一化
    v_gt = v_gt[Ns[0]: Ns[1]]  # 切片获取速度
    u = u[Ns[0]: Ns[1]]  # 切片获取控制输入

    # subsample data
    N0, N = get_start_and_end(seq_dim, u)  # 获取起始和结束索引
    t = t[N0: N].double()  # 切片获取时间并转换为双精度
    ang_gt = ang_gt[N0: N].double()  # 切片获取角度并转换为双精度
    p_gt = (p_gt[N0: N] - p_gt[N0]).double()  # 切片获取位置并归一化
    v_gt = v_gt[N0: N].double()  # 切片获取速度并转换为双精度
    u = u[N0: N].double()  # 切片获取控制输入并转换为双精度

    # add noise
    if iekf.mes_net.training:  # 如果在训练模式
        u = dataset.add_noise(u)  # 添加噪声

    return t, ang_gt, p_gt, v_gt, u, N0  # 返回处理后的数据

def get_start_and_end(seq_dim, u):  # 定义获取起始和结束索引的函数
    if seq_dim is None:  # 如果没有序列维度
        N0 = 0  # 起始索引为0
        N = u.shape[0]  # 结束索引为数据长度
    else:  # 如果有序列维度
        N0 = 10 * int(np.random.randint(0, (u.shape[0] - seq_dim)/10))  # 随机选择起始索引
        N = N0 + seq_dim  # 计算结束索引
    return N0, N  # 返回起始和结束索引

def precompute_lost(Rot, p, list_rpe, N0):  # 定义预计算损失的函数
    N = p.shape[0]  # 获取位置数据的长度
    Rot_10_Hz = Rot[::10]  # 每10个元素取一个
    p_10_Hz = p[::10]  # 每10个元素取一个
    idxs_0 = torch.Tensor(list_rpe[0]).clone().long() - int(N0 / 10)  # 获取起始索引并调整
    idxs_end = torch.Tensor(list_rpe[1]).clone().long() - int(N0 / 10)  # 获取结束索引并调整
    delta_p_gt = list_rpe[2]  # 获取真实位移增量
    idxs = torch.Tensor(idxs_0.shape[0]).byte()  # 创建索引掩码
    idxs[:] = 1  # 初始化为1
    idxs[idxs_0 < 0] = 0  # 将负索引设为0
    idxs[idxs_end >= int(N / 10)] = 0  # 将超出范围的索引设为0
    delta_p_gt = delta_p_gt[idxs]  # 过滤真实位移增量
    idxs_end_bis = idxs_end[idxs]  # 过滤结束索引
    idxs_0_bis = idxs_0[idxs]  # 过滤起始索引
    if len(idxs_0_bis) is 0:  # 如果没有有效索引
        return None, None  # 返回无效标志
    else:  # 如果有有效索引
        delta_p = Rot_10_Hz[idxs_0_bis].transpose(-1, -2).matmul(  # 计算位移增量
        (p_10_Hz[idxs_end_bis] - p_10_Hz[idxs_0_bis]).unsqueeze(-1)).squeeze()

        distance = delta_p_gt.norm(dim=1).unsqueeze(-1)  # 计算距离
        return delta_p.double() / distance.double(), delta_p_gt.double() / distance.double()  # 返回归一化的位移增量
