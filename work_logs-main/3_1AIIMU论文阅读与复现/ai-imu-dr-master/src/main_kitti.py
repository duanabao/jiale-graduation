import os  # 导入操作系统相关的模块
import shutil  # 导入文件操作相关的模块
import numpy as np  # 导入NumPy库，用于数组和数学运算
import csv
from collections import namedtuple  # 从collections模块导入namedtuple，用于创建命名元组
import glob  # 导入glob模块，用于文件路径匹配
import time  # 导入时间模块
import datetime  # 导入日期时间模块
import pickle  # 导入pickle模块，用于对象序列化
import torch  # 导入PyTorch库
import matplotlib.pyplot as plt  # 导入Matplotlib库，用于绘图
from termcolor import cprint  # 从termcolor模块导入cprint，用于彩色打印
from navpy import lla2ned  # 从navpy模块导入lla2ned，用于坐标转换
from collections import OrderedDict  # 从collections模块导入OrderedDict，用于有序字典
from dataset import BaseDataset  # 从dataset模块导入BaseDataset类
from utils_torch_filter import TORCHIEKF  # 从utils_torch_filter模块导入TORCHIEKF类
from utils_numpy_filter import NUMPYIEKF as IEKF  # 从utils_numpy_filter模块导入IEKF类
from utils import prepare_data  # 从utils模块导入prepare_data函数
from train_torch_filter import train_filter  # 从train_torch_filter模块导入train_filter函数
from utils_plot import results_filter  # 从utils_plot模块导入results_filter函数


def launch(args):
    """
    启动函数，根据传入的参数执行不同的操作
    :param args: 参数对象
    """
    if args.read_data:  # 如果需要读取数据
        args.dataset_class.read_data(args)  # 调用数据集类的read_data方法

    dataset = args.dataset_class(args)  # 创建数据集实例，KITTIDataset

    if args.train_filter:  # 如果需要训练滤波器
        train_filter(args, dataset)  # 调用训练滤波器函数

    if args.test_filter:  # 如果需要测试滤波器
        test_filter(args, dataset)  # 调用测试滤波器函数

    if args.results_filter:  # 如果需要处理结果
        results_filter(args, dataset)  # 调用结果处理函数


class KITTIParameters(IEKF.Parameters):
    """
    KITTI参数类，继承自IEKF.Parameters
    """
    g = np.array([0, 0, -9.80655])  # 重力向量

    # 定义协方差参数
    cov_omega = 2e-4
    cov_acc = 1e-3
    cov_b_omega = 1e-8
    cov_b_acc = 1e-6
    cov_Rot_c_i = 1e-8
    cov_t_c_i = 1e-8
    cov_Rot0 = 1e-6
    cov_v0 = 1e-1
    cov_b_omega0 = 1e-8
    cov_b_acc0 = 1e-3
    cov_Rot_c_i0 = 1e-5
    cov_t_c_i0 = 1e-2
    cov_lat = 1
    cov_up = 10

    def __init__(self, **kwargs):
        """
        初始化函数
        :param kwargs: 其他参数
        """
        super(KITTIParameters, self).__init__(**kwargs)  # 调用父类初始化
        self.set_param_attr()  # 设置参数属性

    def set_param_attr(self):
        """
        设置参数属性
        """
        attr_list = [a for a in dir(KITTIParameters) if
                     not a.startswith('__') and not callable(getattr(KITTIParameters, a))]
        for attr in attr_list:
            setattr(self, attr, getattr(KITTIParameters, attr))  # 将参数属性设置到实例中


class KITTIDataset(BaseDataset):
    """
    KITTI数据集类，继承自BaseDataset
    """
    OxtsPacket = namedtuple('OxtsPacket',
                            'lat, lon, alt, ' + 'roll, pitch, yaw, ' + 'vn, ve, vf, vl, vu, '
                                                                       '' + 'ax, ay, az, af, al, '
                                                                            'au, ' + 'wx, wy, wz, '
                                                                                     'wf, wl, wu, '
                                                                                     '' +
                            'pos_accuracy, vel_accuracy, ' + 'navstat, numsats, ' + 'posmode, '
                                                                                  'velmode, '
                                                                                  'orimode')

    OxtsData = namedtuple('OxtsData', 'packet, T_w_imu')  # 将数据打包成易于访问的结构
    min_seq_dim = 25 * 100  # 最小序列维度（60秒）
    datasets_fake = ['2011_09_26_drive_0093_extract', '2011_09_28_drive_0039_extract',
                     '2011_09_28_drive_0002_extract']  # 假数据集列表

    # 训练集到KITTI数据集的原始数据
    odometry_benchmark = OrderedDict()  # 有序字典，存储里程计基准
    odometry_benchmark["2011_10_03_drive_0027_extract"] = [0, 45692]
    odometry_benchmark["2011_10_03_drive_0042_extract"] = [0, 12180]
    odometry_benchmark["2011_10_03_drive_0034_extract"] = [0, 47935]
    odometry_benchmark["2011_09_26_drive_0067_extract"] = [0, 8000]
    odometry_benchmark["2011_09_30_drive_0016_extract"] = [0, 2950]
    odometry_benchmark["2011_09_30_drive_0018_extract"] = [0, 28659]
    odometry_benchmark["2011_09_30_drive_0020_extract"] = [0, 11347]
    odometry_benchmark["2011_09_30_drive_0027_extract"] = [0, 11545]
    odometry_benchmark["2011_09_30_drive_0028_extract"] = [11231, 53650]
    odometry_benchmark["2011_09_30_drive_0033_extract"] = [0, 16589]
    odometry_benchmark["2011_09_30_drive_0034_extract"] = [0, 12744]

    odometry_benchmark_img = OrderedDict()  # 有序字典，存储图像里程计基准
    odometry_benchmark_img["2011_10_03_drive_0027_extract"] = [0, 45400]
    odometry_benchmark_img["2011_10_03_drive_0042_extract"] = [0, 11000]
    odometry_benchmark_img["2011_10_03_drive_0034_extract"] = [0, 46600]
    odometry_benchmark_img["2011_09_26_drive_0067_extract"] = [0, 8000]
    odometry_benchmark_img["2011_09_30_drive_0016_extract"] = [0, 2700]
    odometry_benchmark_img["2011_09_30_drive_0018_extract"] = [0, 27600]
    odometry_benchmark_img["2011_09_30_drive_0020_extract"] = [0, 11000]
    odometry_benchmark_img["2011_09_30_drive_0027_extract"] = [0, 11000]
    odometry_benchmark_img["2011_09_30_drive_0028_extract"] = [11000, 51700]
    odometry_benchmark_img["2011_09_30_drive_0033_extract"] = [0, 15900]
    odometry_benchmark_img["2011_09_30_drive_0034_extract"] = [0, 12000]

    def __init__(self, args):
        """
        初始化函数
        :param args: 参数对象
        """
        super(KITTIDataset, self).__init__(args)  # 调用父类初始化

        # 设置验证和训练集过滤
        self.datasets_validatation_filter['2011_09_30_drive_0028_extract'] = [11231, 53650]
        self.datasets_train_filter["2011_10_03_drive_0042_extract"] = [0, None]
        self.datasets_train_filter["2011_09_30_drive_0018_extract"] = [0, 15000]
        self.datasets_train_filter["2011_09_30_drive_0020_extract"] = [0, None]
        self.datasets_train_filter["2011_09_30_drive_0027_extract"] = [0, None]
        self.datasets_train_filter["2011_09_30_drive_0033_extract"] = [0, None]
        self.datasets_train_filter["2011_10_03_drive_0027_extract"] = [0, 18000]
        self.datasets_train_filter["2011_10_03_drive_0034_extract"] = [0, 31000]
        self.datasets_train_filter["2011_09_30_drive_0034_extract"] = [0, None]

        # 移除假数据集
        for dataset_fake in KITTIDataset.datasets_fake:
            if dataset_fake in self.datasets:
                self.datasets.remove(dataset_fake)
            if dataset_fake in self.datasets_train:
                self.datasets_train.remove(dataset_fake)

    @staticmethod
    def read_data(args):
        """
        从KITTI数据集中读取数据
        :param args: 参数对象
        :return: None
        """
        print("Start read_data")  # 打印开始读取数据
        t_tot = 0  # 所有数据集的总时间
        date_dirs = os.listdir(args.path_data_base)  # 列出数据基础路径下的所有日期目录
        for n_iter, date_dir in enumerate(date_dirs):  # 遍历每个日期目录
            path1 = os.path.join(args.path_data_base, date_dir)  # 构建路径
            if not os.path.isdir(path1):  # 如果路径不是目录，跳过
                continue
            date_dirs2 = os.listdir(path1)  # 列出日期目录下的所有子目录

            for date_dir2 in date_dirs2:  # 遍历每个子目录
                path2 = os.path.join(path1, date_dir2)  # 构建路径
                if not os.path.isdir(path2):  # 如果路径不是目录，跳过
                    continue
                # 读取数据
                # 获取指定路径下的所有oxts数据文件，文件格式为.txt，并按字母顺序排序
                oxts_files = sorted(glob.glob(os.path.join(path2, 'oxts', 'data', '*.txt')))  # 获取oxts数据文件
                # 示例文件名：'2011_09_30_drive_0028_extract_oxts_data_000000.txt'
                oxts = KITTIDataset.load_oxts_packets_and_poses(oxts_files)  # 加载oxts数据包和位姿

                print("\n Sequence name : " + date_dir2)  # 打印序列名称
                if len(oxts) < KITTIDataset.min_seq_dim:  # 如果序列长度小于最小维度
                    cprint("Dataset is too short ({:.2f} s)".format(len(oxts) / 100), 'yellow')  # 打印警告
                    continue
                # 初始化数组
                lat_oxts = np.zeros(len(oxts))  # 纬度
                lon_oxts = np.zeros(len(oxts))  # 经度
                alt_oxts = np.zeros(len(oxts))  # 高度
                roll_oxts = np.zeros(len(oxts))  # 滚转角
                pitch_oxts = np.zeros(len(oxts))  # 俯仰角
                yaw_oxts = np.zeros(len(oxts))  # 偏航角
                roll_gt = np.zeros(len(oxts))  # 滚转角（真实值）
                pitch_gt = np.zeros(len(oxts))  # 俯仰角（真实值）
                yaw_gt = np.zeros(len(oxts))  # 偏航角（真实值）
                t = KITTIDataset.load_timestamps(path2)  # 加载时间戳
                acc = np.zeros((len(oxts), 3))  # 加速度
                acc_bis = np.zeros((len(oxts), 3))  # 备用加速度
                gyro = np.zeros((len(oxts), 3))  # 陀螺仪
                gyro_bis = np.zeros((len(oxts), 3))  # 备用陀螺仪
                p_gt = np.zeros((len(oxts), 3))  # 真实位置
                v_gt = np.zeros((len(oxts), 3))  # 真实速度
                v_rob_gt = np.zeros((len(oxts), 3))  # 机器人真实速度

                k_max = len(oxts)  # oxts的最大长度
                for k in range(k_max):  # 遍历每个oxts数据
                    oxts_k = oxts[k]  # 获取当前oxts数据
                    t[k] = 3600 * t[k].hour + 60 * t[k].minute + t[k].second + t[k].microsecond / 1e6  # 转换时间为秒
                    lat_oxts[k] = oxts_k[0].lat  # 获取纬度
                    lon_oxts[k] = oxts_k[0].lon  # 获取经度
                    alt_oxts[k] = oxts_k[0].alt  # 获取高度
                    acc[k, 0] = oxts_k[0].af  # 获取前向加速度
                    acc[k, 1] = oxts_k[0].al  # 获取侧向加速度
                    acc[k, 2] = oxts_k[0].au  # 获取垂直加速度
                    acc_bis[k, 0] = oxts_k[0].ax  # 获取备用前向加速度
                    acc_bis[k, 1] = oxts_k[0].ay  # 获取备用侧向加速度
                    acc_bis[k, 2] = oxts_k[0].az  # 获取备用垂直加速度
                    gyro[k, 0] = oxts_k[0].wf  # 获取前向角速度
                    gyro[k, 1] = oxts_k[0].wl  # 获取侧向角速度
                    gyro[k, 2] = oxts_k[0].wu  # 获取垂直角速度
                    gyro_bis[k, 0] = oxts_k[0].wx  # 获取备用前向角速度
                    gyro_bis[k, 1] = oxts_k[0].wy  # 获取备用侧向角速度
                    gyro_bis[k, 2] = oxts_k[0].wz  # 获取备用垂直角速度
                    roll_oxts[k] = oxts_k[0].roll  # 获取滚转角
                    pitch_oxts[k] = oxts_k[0].pitch  # 获取俯仰角
                    yaw_oxts[k] = oxts_k[0].yaw  # 获取偏航角
                    v_gt[k, 0] = oxts_k[0].ve  # 获取真实速度（东向）
                    v_gt[k, 1] = oxts_k[0].vn  # 获取真实速度（北向）
                    v_gt[k, 2] = oxts_k[0].vu  # 获取真实速度（上向）
                    v_rob_gt[k, 0] = oxts_k[0].vf  # 获取机器人速度（前向）
                    v_rob_gt[k, 1] = oxts_k[0].vl  # 获取机器人速度（侧向）
                    v_rob_gt[k, 2] = oxts_k[0].vu  # 获取机器人速度（上向）
                    p_gt[k] = oxts_k[1][:3, 3]  # 获取真实位置
                    Rot_gt_k = oxts_k[1][:3, :3]  # 获取真实旋转矩阵
                    roll_gt[k], pitch_gt[k], yaw_gt[k] = IEKF.to_rpy(Rot_gt_k)  # 将旋转矩阵转换为欧拉角

                t0 = t[0]  # 获取初始时间
                t = np.array(t) - t[0]  # 将时间归一化
                # 检查时间间隔是否正常
                if np.max(t[:-1] - t[1:]) > 0.1:
                    cprint(date_dir2 + " has time problem", 'yellow')  # 打印时间问题警告
                ang_gt = np.zeros((roll_gt.shape[0], 3))  # 初始化角度数组
                ang_gt[:, 0] = roll_gt  # 设置滚转角
                ang_gt[:, 1] = pitch_gt  # 设置俯仰角
                ang_gt[:, 2] = yaw_gt  # 设置偏航角

                # 将经纬度转换为NED坐标系
                p_oxts = lla2ned(lat_oxts, lon_oxts, alt_oxts, lat_oxts[0], lon_oxts[0],
                                 alt_oxts[0], latlon_unit='deg', alt_unit='m', model='wgs84')
                p_oxts[:, [0, 1]] = p_oxts[:, [1, 0]]  # 交换坐标

                # 获取IMU测量值
                u = np.concatenate((gyro_bis, acc_bis), -1)  # 合并陀螺仪和加速度计数据
                # 转换为PyTorch张量
                t = torch.from_numpy(t)
                p_gt = torch.from_numpy(p_gt)
                v_gt = torch.from_numpy(v_gt)
                ang_gt = torch.from_numpy(ang_gt)
                u = torch.from_numpy(u)

                # 转换为浮点数
                t = t.float()
                u = u.float()
                p_gt = p_gt.float()
                ang_gt = ang_gt.float()
                v_gt = v_gt.float()

                mondict = {
                    't': t, 'p_gt': p_gt, 'ang_gt': ang_gt, 'v_gt': v_gt,
                    'u': u, 'name': date_dir2, 't0': t0
                }
                
                t_tot += t[-1] - t[0]  # 累加总时间
                KITTIDataset.dump(mondict, args.path_data_save, date_dir2)  # 保存数据
        print("\n Total dataset duration : {:.2f} s".format(t_tot))  # 打印总数据集持续时间

    @staticmethod
    def prune_unused_data(args):
        """
        删除未使用的图像和激光雷达数据
        :param args: 参数对象
        :return: None
        """
        unused_list = ['image_00', 'image_01', 'image_02', 'image_03', 'velodyne_points']  # 未使用的文件夹列表
        date_dirs = ['2011_09_28', '2011_09_29', '2011_09_30', '2011_10_03']  # 日期目录列表

        for date_dir in date_dirs:  # 遍历每个日期目录
            path1 = os.path.join(args.path_data_base, date_dir)  # 构建路径
            if not os.path.isdir(path1):  # 如果路径不是目录，跳过
                continue
            date_dirs2 = os.listdir(path1)  # 列出日期目录下的所有子目录

            for date_dir2 in date_dirs2:  # 遍历每个子目录
                path2 = os.path.join(path1, date_dir2)  # 构建路径
                if not os.path.isdir(path2):  # 如果路径不是目录，跳过
                    continue
                print(path2)  # 打印当前路径
                for folder in unused_list:  # 遍历未使用的文件夹
                    path3 = os.path.join(path2, folder)  # 构建路径
                    if os.path.isdir(path3):  # 如果路径是目录
                        print(path3)  # 打印当前路径
                        shutil.rmtree(path3)  # 删除目录

    @staticmethod
    def subselect_files(files, indices):
        """
        根据索引子选择文件
        :param files: 文件列表
        :param indices: 索引列表
        :return: 子选择后的文件列表
        """
        try:
            files = [files[i] for i in indices]  # 根据索引选择文件
        except:
            pass
        return files  # 返回选择后的文件列表

    @staticmethod
    def rotx(t):
        """绕x轴旋转的矩阵"""
        c = np.cos(t)  # 计算余弦
        s = np.sin(t)  # 计算正弦
        return np.array([[1, 0, 0], [0, c, -s], [0, s, c]])  # 返回旋转矩阵

    @staticmethod
    def roty(t):
        """绕y轴旋转的矩阵"""
        c = np.cos(t)  # 计算余弦
        s = np.sin(t)  # 计算正弦
        return np.array([[c, 0, s], [0, 1, 0], [-s, 0, c]])  # 返回旋转矩阵

    @staticmethod
    def rotz(t):
        """绕z轴旋转的矩阵"""
        c = np.cos(t)  # 计算余弦
        s = np.sin(t)  # 计算正弦
        return np.array([[c, -s, 0], [s, c, 0], [0, 0, 1]])  # 返回旋转矩阵

    @staticmethod
    def pose_from_oxts_packet(packet, scale):
        """从OXTS数据包计算SE(3)位姿矩阵的辅助方法"""
        er = 6378137.  # 地球半径（近似）以米为单位

        # 使用墨卡托投影计算平移向量
        tx = scale * packet.lon * np.pi * er / 180.  # 经度转换
        ty = scale * er * np.log(np.tan((90. + packet.lat) * np.pi / 360.))  # 纬度转换
        tz = packet.alt  # 高度
        t = np.array([tx, ty, tz])  # 组合平移向量

        # 使用欧拉角计算旋转矩阵
        Rx = KITTIDataset.rotx(packet.roll)  # 绕x轴旋转
        Ry = KITTIDataset.roty(packet.pitch)  # 绕y轴旋转
        Rz = KITTIDataset.rotz(packet.yaw)  # 绕z轴旋转
        R = Rz.dot(Ry.dot(Rx))  # 组合旋转矩阵

        # 将平移和旋转组合成齐次变换
        return R, t  # 返回旋转矩阵和位移向量

    @staticmethod
    def transform_from_rot_trans(R, t):
        """从旋转矩阵和平移向量生成变换矩阵"""
        R = R.reshape(3, 3)  # 确保R是3x3矩阵
        t = t.reshape(3, 1)  # 确保t是3x1矩阵
        return np.vstack((np.hstack([R, t]), [0, 0, 0, 1]))  # 返回齐次变换矩阵

    @staticmethod
    def load_oxts_packets_and_poses(oxts_files):
        """生成器，用于读取OXTS地面真实数据"""
        scale = None  # 墨卡托投影的缩放因子
        origin = None  # 全局坐标系的原点（第一个GPS位置）

        oxts = []  # 存储OXTS数据

        for filename in oxts_files:  # 遍历每个文件
            with open(filename, 'r') as f:  # 打开文件
                for line in f.readlines():  # 逐行读取
                    line = line.split()  # 分割行
                    # 最后五个条目是标志和计数
                    line[:-5] = [float(x) for x in line[:-5]]  # 转换前面的数据为浮点数
                    line[-5:] = [int(float(x)) for x in line[-5:]]  # 转换后面的数据为整数

                    packet = KITTIDataset.OxtsPacket(*line)  # 创建OxtsPacket实例

                    if scale is None:  # 如果缩放因子未定义
                        scale = np.cos(packet.lat * np.pi / 180.)  # 根据第一个纬度计算缩放因子

                    R, t = KITTIDataset.pose_from_oxts_packet(packet, scale)  # 计算旋转矩阵和平移向量

                    if origin is None:  # 如果原点未定义
                        origin = t  # 设置原点为当前平移向量

                    T_w_imu = KITTIDataset.transform_from_rot_trans(R, t - origin)  # 计算变换矩阵

                    oxts.append(KITTIDataset.OxtsData(packet, T_w_imu))  # 将数据添加到列表中
        return oxts  # 返回OXTS数据列表

    @staticmethod
    def load_timestamps(data_path):
        """从文件加载时间戳"""
        timestamp_file = os.path.join(data_path, 'oxts', 'timestamps.txt')  # 构建时间戳文件路径

        timestamps = []  # 存储时间戳
        with open(timestamp_file, 'r') as f:  # 打开时间戳文件
            for line in f.readlines():  # 逐行读取
                # 注意：datetime只支持微秒，但KITTI时间戳给出的是纳秒
                # 需要截断最后4个字符以去掉\n（算作1）和额外的3位数字
                t = datetime.datetime.strptime(line[:-4], '%Y-%m-%d %H:%M:%S.%f')  # 解析时间戳
                timestamps.append(t)  # 添加到时间戳列表
        return timestamps  # 返回时间戳列表

    def load_timestamps_img(data_path):
        """从文件加载图像时间戳"""
        timestamp_file = os.path.join(data_path, 'image_00', 'timestamps.txt')  # 构建时间戳文件路径

        timestamps = []  # 存储时间戳
        with open(timestamp_file, 'r') as f:  # 打开时间戳文件
            for line in f.readlines():  # 逐行读取
                # 注意：datetime只支持微秒，但KITTI时间戳给出的是纳秒
                # 需要截断最后4个字符以去掉\n（算作1）和额外的3位数字
                t = datetime.datetime.strptime(line[:-4], '%Y-%m-%d %H:%M:%S.%f')  # 解析时间戳
                timestamps.append(t)  # 添加到时间戳列表
        return timestamps  # 返回时间戳列表


def test_filter(args, dataset):
    """
    测试滤波器
    :param args: 参数对象
    :param dataset: 数据集对象
    """
    iekf = IEKF()  # 创建IEKF实例，扩展卡尔曼滤波（EKF）
    torch_iekf = TORCHIEKF()  # 创建TORCHIEKF实例

    # 设置KITTI参数
    iekf.filter_parameters = KITTIParameters()  # 设置IEKF的滤波参数
    iekf.set_param_attr()  # 设置参数属性
    torch_iekf.filter_parameters = KITTIParameters()  # 设置TORCHIEKF的滤波参数
    torch_iekf.set_param_attr()  # 设置参数属性

    torch_iekf.load(args, dataset)  # 加载数据
    iekf.set_learned_covariance(torch_iekf)  # 设置学习到的协方差

    for i in range(0, len(dataset.datasets)):  # 遍历数据集
        dataset_name = dataset.dataset_name(i)  # 获取数据集名称
        if dataset_name not in dataset.odometry_benchmark.keys():  # 如果数据集名称不在里程计基准中
            continue
        print("Test filter on sequence: " + dataset_name)  # 打印正在测试的序列名称
        t, ang_gt, p_gt, v_gt, u = prepare_data(args, dataset, dataset_name, i,
                                                       to_numpy=True)  # 准备数据
        N = None  # 初始化N
        u_t = torch.from_numpy(u).double()  # 将u转换为PyTorch张量
        measurements_covs = torch_iekf.forward_nets(u_t)  # 前向传播获取测量协方差
        measurements_covs = measurements_covs.detach().numpy()  # 转换为NumPy数组
        start_time = time.time()  # 记录开始时间
        Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i = iekf.run(t, u, measurements_covs,
                                                                   v_gt, p_gt, N,
                                                                   ang_gt[0])  # 运行IEKF
        diff_time = time.time() - start_time  # 计算执行时间
        print("Execution time: {:.2f} s (sequence time: {:.2f} s)".format(diff_time,
                                                                          t[-1] - t[0]))  # 打印执行时间
        mondict = {
            't': t, 'Rot': Rot, 'v': v, 'p': p, 'b_omega': b_omega, 'b_acc': b_acc,
            'Rot_c_i': Rot_c_i, 't_c_i': t_c_i,
            'measurements_covs': measurements_covs,
        }
        with open(os.path.join(args.path_temp, dataset_name + "_filter.txt"), 'w') as f:
            for key, value in mondict.items():
                f.write(f"{key}: {value}\n")

        csv_file_path = os.path.join(args.path_temp, dataset_name + "_positions.csv")
        # 打开文件并写入 CSV
        with open(csv_file_path, mode='w', newline='') as file:
            writer = csv.writer(file)
            # 写入 CSV 文件的标题
            writer.writerow(['x', 'y', 'z'])
            # 写入每个位置的数据
            for position in p:
                writer.writerow(position)       
        print(f"Positions saved to {csv_file_path}")

        dataset.dump(mondict, args.path_results, dataset_name + "_filter.p")  # 保存结果


class KITTIArgs():
    """
    KITTI参数类
    """
    path_data_base = "/media/mines/46230797-4d43-4860-9b76-ce35e699ea47/KITTI/raw"  # 数据基础路径
    path_data_save = "../data"  # 数据保存路径
    path_results = "../results"  # 结果保存路径
    path_temp = "../temp"  # 临时文件路径

    epochs = 400  # 训练轮数
    seq_dim = 6000  # 序列维度

    # 训练、交叉验证和测试数据集
    cross_validation_sequences = ['2011_09_30_drive_0028_extract']  # 交叉验证序列
    test_sequences = ['2011_09_30_drive_0028_extract']  # 测试序列
    continue_training = True  # 是否继续训练

    # 选择要执行的操作
    read_data = 1  # 读取数据
    train_filter = 0  # 训练滤波器
    test_filter = 1  # 测试滤波器
    results_filter = 1  # 处理结果
    dataset_class = KITTIDataset  # 数据集类
    parameter_class = KITTIParameters  # 参数类


if __name__ == '__main__':
    args = KITTIArgs()  # 创建参数对象
    dataset = KITTIDataset(args)  # 创建数据集对象
    launch(KITTIArgs)  # 启动程序

