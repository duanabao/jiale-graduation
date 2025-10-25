import csv
from torch.utils.data.dataset import Dataset  # 从PyTorch的dataset模块导入Dataset类
import torch  # 导入PyTorch库
import numpy as np  # 导入NumPy库
from termcolor import cprint  # 导入用于打印彩色文本的库
import pickle  # 导入用于序列化和反序列化对象的pickle库
import matplotlib.pyplot as plt  # 导入用于绘图的matplotlib库
import os  # 导入操作系统相关的库
from collections import OrderedDict  # 从collections模块导入有序字典OrderedDict


class BaseDataset(Dataset):  # 定义一个名为BaseDataset的类，继承自Dataset
    pickle_extension = ".p"  # 定义pickle文件的扩展名
    """保存为pickle格式的文件扩展名"""
    file_normalize_factor = "normalize_factors.p"  # 定义用于归一化输入的文件名
    """用于归一化输入的文件名"""

    def __init__(self, args):  # 初始化方法，接收参数args
        # paths
        self.path_data_save = args.path_data_save  # 保存数据的路径
        """数据保存路径"""
        self.path_results = args.path_results  # 结果的路径
        """结果路径"""
        self.path_temp = args.path_temp  # 临时文件的路径
        """临时文件路径"""

        self.datasets_test = args.test_sequences  # 测试数据集
        """测试数据集"""
        self.datasets_validation = args.cross_validation_sequences  # 交叉验证数据集
        """交叉验证数据集"""

        # names of the sequences
        self.datasets = []  # 数据集名称列表
        """数据集名称"""
        self.datasets_train = []  # 训练数据集列表
        """训练数据集"""

        self.datasets_validatation_filter = OrderedDict()  # 用于存储验证数据集的有序字典
        """带有起始/结束索引的验证数据集"""
        self.datasets_train_filter = OrderedDict()  # 用于存储训练数据集的有序字典
        """带有起始/结束索引的训练数据集"""

        # noise added to the data
        self.sigma_gyro = 1.e-4  # 陀螺仪噪声标准差
        self.sigma_acc = 1.e-4  # 加速度计噪声标准差
        self.sigma_b_gyro = 1.e-5  # 陀螺仪偏置噪声标准差
        self.sigma_b_acc = 1.e-4  # 加速度计偏置噪声标准差

        # number of training data points
        self.num_data = 0  # 训练数据点的数量

        # factors for normalizing inputs
        self.normalize_factors = None  # 归一化因子
        self.get_datasets()  # 获取数据集
        self.set_normalize_factors()  # 设置归一化因子

    def __getitem__(self, i):  # 获取指定索引的项
        mondict = self.load(self.path_data_save, self.datasets[i])  # 加载数据
        
        p_gt = mondict['p_gt']  # 获取p_gt的值
        raw_temp_path = os.path.join(self.path_temp, 'raw_temp')  # 定义保存路径
        os.makedirs(raw_temp_path, exist_ok=True)  # 创建raw_temp文件夹（如果不存在）
        csv_file_path = os.path.join(raw_temp_path, f"{self.datasets[i]}_p_gt.csv")  # 定义CSV文件路径
        with open(csv_file_path, mode='w', newline='') as file:
            writer = csv.writer(file)
            # 写入 CSV 文件的标题
            writer.writerow(['x', 'y', 'z'])
            # 写入每个位置的数据
            for position in p_gt:
                writer.writerow([position[0].item(), position[1].item(), position[2].item()])  # 使用 .item() 转换Tensor为数值    
        print(f"RAW_Positions saved to {csv_file_path}")

        return mondict  # 返回加载的数据

    def __len__(self):  # 返回数据集的长度
        return len(self.datasets)  # 返回数据集的大小

    def get_datasets(self):  # 获取数据集的方法
        for dataset in os.listdir(self.path_data_save):  # 遍历保存数据的路径
            self.datasets += [dataset[:-2]]  # 仅取名称，去掉".p"后缀
        self.divide_datasets()  # 划分数据集

    def divide_datasets(self):  # 划分数据集的方法
        for dataset in self.datasets:  # 遍历所有数据集
            if (not dataset in self.datasets_test) and (not dataset in self.datasets_validation):  # 如果不在测试和验证集中
                self.datasets_train += [dataset]  # 添加到训练数据集中

    def dataset_name(self, i):  # 获取数据集名称的方法
        return self.datasets[i]  # 返回指定索引的数据集名称

    def get_data(self, i):  # 获取数据的方法
        pickle_dict = self[self.datasets.index(i) if type(i) != int else i]  # 根据索引获取数据
        return pickle_dict['t'], pickle_dict['ang_gt'], pickle_dict['p_gt'], pickle_dict['v_gt'],\
               pickle_dict['u']  # 返回时间、角度、位置、速度和输入数据

    def set_normalize_factors(self):  # 设置归一化因子的方法
        path_normalize_factor = os.path.join(self.path_temp, self.file_normalize_factor)  # 归一化因子文件的路径
        # we set factors only if file does not exist
        if os.path.isfile(path_normalize_factor):  # 如果文件存在
            pickle_dict = self.load(path_normalize_factor)  # 加载归一化因子
            self.normalize_factors = pickle_dict['normalize_factors']  # 设置归一化因子
            self.num_data = pickle_dict['num_data']  # 设置数据点数量
            return  # 返回

        # first compute mean
        self.num_data = 0  # 初始化数据点数量

        for i, dataset in enumerate(self.datasets_train):  # 遍历训练数据集
            pickle_dict = self.load(self.path_data_save, dataset)  # 加载数据
            u = pickle_dict['u']  # 获取输入数据
            if i == 0:  # 如果是第一个数据集
                u_loc = u.sum(dim=0)  # 计算输入数据的总和
            else:
                u_loc += u.sum(dim=0)  # 累加输入数据的总和
            self.num_data += u.shape[0]  # 更新数据点数量
        u_loc = u_loc / self.num_data  # 计算均值

        # second compute standard deviation
        for i, dataset in enumerate(self.datasets_train):  # 遍历训练数据集
            pickle_dict = self.load(self.path_data_save, dataset)  # 加载数据
            u = pickle_dict['u']  # 获取输入数据
            if i == 0:  # 如果是第一个数据集
                u_std = ((u - u_loc) ** 2).sum(dim=0)  # 计算方差
            else:
                u_std += ((u - u_loc) ** 2).sum(dim=0)  # 累加方差
        u_std = (u_std / self.num_data).sqrt()  # 计算标准差

        self.normalize_factors = {  # 设置归一化因子
            'u_loc': u_loc, 'u_std': u_std,
            }
        print('... ended computing normalizing factors')  # 打印计算完成信息
        pickle_dict = {  # 创建字典以保存归一化因子和数据点数量
            'normalize_factors': self.normalize_factors, 'num_data': self.num_data}
        self.dump(pickle_dict, path_normalize_factor)  # 保存归一化因子

    def normalize(self, u):  # 归一化输入数据的方法
        u_loc = self.normalize_factors["u_loc"]  # 获取均值
        u_std = self.normalize_factors["u_std"]  # 获取标准差
        u_normalized = (u - u_loc) / u_std  # 计算归一化数据
        return u_normalized  # 返回归一化数据

    def add_noise(self, u):  # 添加噪声的方法
        w = torch.randn_like(u[:, :6])  # 生成与输入数据相同形状的噪声
        w_b = torch.randn_like(u[0, :6])  # 生成与输入数据相同形状的偏置噪声
        w[:, :3] *= self.sigma_gyro  # 对陀螺仪噪声进行缩放
        w[:, 3:6] *= self.sigma_acc  # 对加速度计噪声进行缩放
        w_b[:3] *= self.sigma_b_gyro  # 对陀螺仪偏置噪声进行缩放
        w_b[3:6] *= self.sigma_b_acc  # 对加速度计偏置噪声进行缩放
        u[:, :6] += w + w_b  # 将噪声添加到输入数据
        return u  # 返回添加噪声后的数据


    @staticmethod
    def read_data(args):  # 静态方法，读取数据
        raise NotImplementedError  # 抛出未实现错误

    @classmethod
    def load(cls, *_file_name):  # 类方法，加载文件
        file_name = os.path.join(*_file_name)  # 组合文件路径
        if not file_name.endswith(cls.pickle_extension):  # 如果文件名不以指定扩展名结尾
            file_name += cls.pickle_extension  # 添加扩展名
        with open(file_name, "rb") as file_pi:  # 以二进制读取模式打开文件
            pickle_dict = pickle.load(file_pi)  # 反序列化数据
        return pickle_dict  # 返回加载的数据

    @classmethod
    def dump(cls, mondict, *_file_name):  # 类方法，保存数据
        file_name = os.path.join(*_file_name)  # 组合文件路径
        if not file_name.endswith(cls.pickle_extension):  # 如果文件名不以指定扩展名结尾
            file_name += cls.pickle_extension  # 添加扩展名
        with open(file_name, "wb") as file_pi:  # 以二进制写入模式打开文件
            pickle.dump(mondict, file_pi)  # 序列化并保存数据

    def init_state_torch_filter(self, iekf):  # 初始化Torch滤波器的状态
        b_omega0 = torch.zeros(3).double()  # 初始化陀螺仪偏置为零
        b_acc0 = torch.zeros(3).double()  # 初始化加速度计偏置为零
        Rot_c_i0 = torch.eye(3).double()  # 初始化旋转矩阵为单位矩阵
        t_c_i0 = torch.zeros(3).double()  # 初始化位置为零
        return b_omega0, b_acc0, Rot_c_i0, t_c_i0  # 返回初始化的状态

    def get_estimates(self, dataset_name):  # 获取估计值的方法
        #  Obtain  estimates
        dataset_name = self.datasets[dataset_name] if type(dataset_name) == int else \
            dataset_name  # 如果输入是索引，则获取对应的数据集名称
        file_name = os.path.join(self.path_results, dataset_name + "_filter.p")  # 结果文件的路径
        if not os.path.exists(file_name):  # 如果结果文件不存在
            print('No result for ' + dataset_name)  # 打印没有结果的信息
            return  # 返回
        mondict = self.load(file_name)  # 加载结果数据
        Rot = mondict['Rot']  # 获取旋转矩阵
        v = mondict['v']  # 获取速度
        p = mondict['p']  # 获取位置
        b_omega = mondict['b_omega']  # 获取陀螺仪偏置
        b_acc = mondict['b_acc']  # 获取加速度计偏置
        Rot_c_i = mondict['Rot_c_i']  # 获取旋转矩阵
        t_c_i = mondict['t_c_i']  # 获取位置
        measurements_covs = mondict['measurements_covs']  # 获取测量协方差
        return Rot, v, p , b_omega, b_acc, Rot_c_i, t_c_i, measurements_covs  # 返回所有估计值


