# 导入必要的库
import matplotlib.pyplot as plt
import numpy as np
np.set_printoptions(precision=2)  # 设置numpy打印选项，保留两位小数
import scipy.linalg
from termcolor import cprint
from utils import *

# 定义NUMPYIEKF类
class NUMPYIEKF:
    Id2 = np.eye(2)  # 2x2单位矩阵
    Id3 = np.eye(3)  # 3x3单位矩阵
    Id6 = np.eye(6)  # 6x6单位矩阵
    IdP = np.eye(21)  # 21x21单位矩阵

    def __init__(self, parameter_class=None):
        # 初始化时的变量
        self.g = None  # 重力加速度
        self.cov_omega = None  # 陀螺仪协方差
        self.cov_acc = None  # 加速度计协方差
        self.cov_b_omega = None  # 陀螺仪偏差协方差
        self.cov_b_acc = None  # 加速度计偏差协方差
        self.cov_Rot_c_i = None  # 车辆到IMU的方向协方差
        self.cov_t_c_i = None  # 车辆到IMU的平移协方差
        self.cov_lat = None  # 侧向速度协方差
        self.cov_up = None  # 垂直速度协方差
        self.cov_b_omega0 = None  # 初始陀螺仪偏差协方差
        self.cov_b_acc0 = None  # 初始加速度计偏差协方差
        self.cov_Rot0 = None  # 初始姿态协方差
        self.cov_v0 = None  # 初始速度协方差
        self.cov_Rot_c_i0 = None  # 初始车辆到IMU的姿态协方差
        self.cov_t_c_i0 = None  # 初始车辆到IMU的平移协方差
        self.Q = None  # 过程噪声协方差
        self.Q_dim = None  # 过程噪声维度
        self.n_normalize_rot = None  # 归一化旋转的时间戳
        self.n_normalize_rot_c_i = None  # 归一化车辆到IMU旋转的时间戳
        self.P_dim = None  # 协方差维度
        self.verbose = None  # 详细输出标志

        # 设置参数
        if parameter_class is None:
            filter_parameters = NUMPYIEKF.Parameters()  # 如果没有提供参数类，则使用默认参数
        else:
            filter_parameters = parameter_class()  # 使用提供的参数类
        self.filter_parameters = filter_parameters  # 保存参数
        self.set_param_attr()  # 设置参数属性

    class Parameters:
        g = np.array([0, 0, -9.80665])  # 重力向量

        P_dim = 21  # 协方差维度
        Q_dim = 18  # 过程噪声协方差维度

        # 过程噪声协方差
        cov_omega = 1e-3  # 陀螺仪协方差
        cov_acc = 1e-2  # 加速度计协方差
        cov_b_omega = 6e-9  # 陀螺仪偏差协方差
        cov_b_acc = 2e-4  # 加速度计偏差协方差
        cov_Rot_c_i = 1e-9  # 车辆到IMU的方向协方差
        cov_t_c_i = 1e-9  # 车辆到IMU的平移协方差

        cov_lat = 0.2  # 侧向速度协方差
        cov_up = 300  # 垂直速度协方差

        cov_Rot0 = 1e-3  # 初始姿态协方差
        cov_b_omega0 = 6e-3  # 初始陀螺仪偏差协方差
        cov_b_acc0 = 4e-3  # 初始加速度计偏差协方差
        cov_v0 = 1e-1  # 初始速度协方差
        cov_Rot_c_i0 = 1e-6  # 初始车辆到IMU的姿态协方差
        cov_t_c_i0 = 5e-3  # 初始车辆到IMU的平移协方差

        # 数值参数
        n_normalize_rot = 100  # 归一化姿态的时间戳
        n_normalize_rot_c_i = 1000  # 归一化车辆到IMU姿态的时间戳

        def __init__(self, **kwargs):
            self.set(**kwargs)  # 设置参数

        def set(self, **kwargs):
            for key, value in kwargs.items():
                setattr(self, key, value)  # 动态设置参数属性

    def set_param_attr(self):
        # 获取属性列表
        attr_list = [a for a in dir(self.filter_parameters) if not a.startswith('__')
                     and not callable(getattr(self.filter_parameters, a))]
        for attr in attr_list:
            setattr(self, attr, getattr(self.filter_parameters, attr))  # 将参数属性设置到当前对象

        # 设置过程噪声协方差矩阵
        self.Q = np.diag([self.cov_omega, self.cov_omega, self.cov_omega,
                           self.cov_acc, self.cov_acc, self.cov_acc,
                           self.cov_b_omega, self.cov_b_omega, self.cov_b_omega,
                           self.cov_b_acc, self.cov_b_acc, self.cov_b_acc,
                           self.cov_Rot_c_i, self.cov_Rot_c_i, self.cov_Rot_c_i,
                           self.cov_t_c_i, self.cov_t_c_i, self.cov_t_c_i])  # 生成对角矩阵

    def run(self, t, u, measurements_covs, v_mes, p_mes, N, ang0):
        dt = t[1:] - t[:-1]  # 计算时间间隔
        if N is None:
            N = u.shape[0]  # 如果N为None，则使用输入u的形状
        Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i, P = self.init_run(dt, u, p_mes, v_mes,
                                       ang0, N)  # 初始化运行状态

        for i in range(1, N):
            # 传播状态
            Rot[i], v[i], p[i], b_omega[i], b_acc[i], Rot_c_i[i], t_c_i[i], P = \
                self.propagate(Rot[i-1], v[i-1], p[i-1], b_omega[i-1], b_acc[i-1], Rot_c_i[i-1],
                               t_c_i[i-1], P, u[i], dt[i-1])

            # 更新状态
            Rot[i], v[i], p[i], b_omega[i], b_acc[i], Rot_c_i[i], t_c_i[i], P = \
                self.update(Rot[i], v[i], p[i], b_omega[i], b_acc[i], Rot_c_i[i], t_c_i[i], P, u[i],
                            i, measurements_covs[i])
            # 每秒纠正数值误差
            if i % self.n_normalize_rot == 0:
                Rot[i] = self.normalize_rot(Rot[i])
            # 每10秒纠正车辆到IMU的数值误差
            if i % self.n_normalize_rot_c_i == 0:
                Rot_c_i[i] = self.normalize_rot(Rot_c_i[i])
        return Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i  # 返回状态

    def init_run(self, dt, u, p_mes, v_mes, ang0, N):
        # 初始化运行状态
        Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i = self.init_saved_state(dt, N, ang0)
        Rot[0] = self.from_rpy(ang0[0], ang0[1], ang0[2])  # 从滚转、俯仰、偏航角初始化旋转矩阵
        v[0] = v_mes[0]  # 初始化速度
        P = self.init_covariance()  # 初始化协方差
        return Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i, P  # 返回初始化状态

    def init_covariance(self):
        # 初始化协方差矩阵
        P = np.zeros((self.P_dim, self.P_dim))  # 创建零矩阵
        P[:2, :2] = self.cov_Rot0*self.Id2  # 设置姿态协方差
        P[3:5, 3:5] = self.cov_v0*self.Id2  # 设置速度协方差
        P[9:12, 9:12] = self.cov_b_omega0*self.Id3  # 设置陀螺仪偏差协方差
        P[12:15, 12:15] = self.cov_b_acc0*self.Id3  # 设置加速度计偏差协方差
        P[15:18, 15:18] = self.cov_Rot_c_i0*self.Id3  # 设置车辆到IMU的姿态协方差
        P[18:21, 18:21] = self.cov_t_c_i0*self.Id3  # 设置车辆到IMU的平移协方差
        return P  # 返回协方差矩阵

    def init_saved_state(self, dt, N, ang0):
        # 初始化保存的状态
        Rot = np.zeros((N, 3, 3))  # 初始化旋转矩阵
        v = np.zeros((N, 3))  # 初始化速度
        p = np.zeros((N, 3))  # 初始化位置
        b_omega = np.zeros((N, 3))  # 初始化陀螺仪偏差
        b_acc = np.zeros((N, 3))  # 初始化加速度计偏差
        Rot_c_i = np.zeros((N, 3, 3))  # 初始化车辆到IMU的旋转矩阵
        t_c_i = np.zeros((N, 3))  # 初始化车辆到IMU的平移
        Rot_c_i[0] = np.eye(3)  # 第一个旋转矩阵为单位矩阵
        return Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i  # 返回初始化状态

    def propagate(self, Rot_prev, v_prev, p_prev, b_omega_prev, b_acc_prev, Rot_c_i_prev,
                  t_c_i_prev, P_prev, u, dt):
        # 传播状态
        acc = Rot_prev.dot(u[3:6] - b_acc_prev) + self.g  # 计算加速度
        v = v_prev + acc * dt  # 更新速度
        p = p_prev + v_prev*dt + 1/2 * acc * dt**2  # 更新位置
        omega = u[:3] - b_omega_prev  # 计算角速度
        Rot = Rot_prev.dot(self.so3exp(omega * dt))  # 更新旋转矩阵
        b_omega = b_omega_prev  # 更新陀螺仪偏差
        b_acc = b_acc_prev  # 更新加速度计偏差
        Rot_c_i = Rot_c_i_prev  # 更新车辆到IMU的旋转矩阵
        t_c_i = t_c_i_prev  # 更新车辆到IMU的平移
        P = self.propagate_cov(P_prev, Rot_prev, v_prev, p_prev, b_omega_prev,
                               b_acc_prev, u, dt)  # 更新协方差
        return Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i, P  # 返回更新后的状态

    def propagate_cov(self, P_prev, Rot_prev, v_prev, p_prev, b_omega_prev,
                      b_acc_prev, u, dt):
        # 传播协方差
        F = np.zeros((self.P_dim, self.P_dim))  # 初始化状态转移矩阵
        G = np.zeros((self.P_dim, self.Q_dim))  # 初始化输入矩阵
        v_skew_rot = self.skew(v_prev).dot(Rot_prev)  # 计算速度的反对称矩阵
        p_skew_rot = self.skew(p_prev).dot(Rot_prev)  # 计算位置的反对称矩阵

        F[3:6, :3] = self.skew(self.g)  # 设置重力影响
        F[6:9, 3:6] = self.Id3  # 设置状态转移
        G[3:6, 3:6] = Rot_prev  # 设置输入矩阵
        F[3:6, 12:15] = -Rot_prev  # 设置状态转移
        G[:3, :3] = Rot_prev  # 设置输入矩阵
        G[3:6, :3] = v_skew_rot  # 设置速度影响
        G[6:9, :3] = p_skew_rot  # 设置位置影响
        F[:3, 9:12] = -Rot_prev  # 设置状态转移
        F[3:6, 9:12] = -v_skew_rot  # 设置状态转移
        F[6:9, 9:12] = -p_skew_rot  # 设置状态转移
        G[9:15, 6:12] = self.Id6  # 设置输入矩阵
        G[15:18, 12:15] = self.Id3  # 设置输入矩阵
        G[18:21, 15:18] = self.Id3  # 设置输入矩阵

        F = F * dt  # 时间步长缩放
        G = G * dt  # 时间步长缩放
        F_square = F.dot(F)  # 计算F的平方
        F_cube = F_square.dot(F)  # 计算F的立方
        Phi = self.IdP + F + 1/2*F_square + 1/6*F_cube  # 计算状态转移矩阵
        P = Phi.dot(P_prev + G.dot(self.Q).dot(G.T)).dot(Phi.T)  # 更新协方差
        return P  # 返回更新后的协方差

    def update(self, Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i, P, u, i, measurement_cov):
        # 更新状态
        Rot_body = Rot.dot(Rot_c_i)  # 计算身体框架的方向
        v_imu = Rot.T.dot(v)  # 计算IMU框架的速度
        v_body = Rot_c_i.T.dot(v_imu)  # 计算车辆框架的速度
        v_body += self.skew(t_c_i).dot(u[:3] - b_omega)  # 计算车辆轴的速度
        Omega = self.skew(u[:3] - b_omega)  # 计算角速度的反对称矩阵

        # 计算相对于车辆框架的雅可比矩阵
        H_v_imu = Rot_c_i.T.dot(self.skew(v_imu))  # IMU速度的雅可比
        H_t_c_i = -self.skew(t_c_i)  # 平移的雅可比

        H = np.zeros((2, self.P_dim))  # 初始化雅可比矩阵
        H[:, 3:6] = Rot_body.T[1:]  # 设置速度的雅可比
        H[:, 15:18] = H_v_imu[1:]  # 设置IMU速度的雅可比
        H[:, 9:12] = H_t_c_i[1:]  # 设置平移的雅可比
        H[:, 18:21] = -Omega[1:]  # 设置角速度的雅可比
        r = - v_body[1:]  # 计算残差
        R = np.diag(measurement_cov)  # 计算测量协方差矩阵
        Rot_up, v_up, p_up, b_omega_up, b_acc_up, Rot_c_i_up, t_c_i_up, P_up = \
            self.state_and_cov_update(Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i, P, H, r, R)  # 更新状态和协方差
        return Rot_up, v_up, p_up, b_omega_up, b_acc_up, Rot_c_i_up, t_c_i_up, P_up  # 返回更新后的状态

    @staticmethod
    def state_and_cov_update(Rot, v, p, b_omega, b_acc, Rot_c_i, t_c_i, P, H, r, R):
        S = H.dot(P).dot(H.T) + R  # 计算协方差
        K = (np.linalg.solve(S, P.dot(H.T).T)).T  # 计算卡尔曼增益
        dx = K.dot(r)  # 计算状态更新量

        dR, dxi = NUMPYIEKF.sen3exp(dx[:9])  # 计算旋转和状态更新
        dv = dxi[:, 0]  # 速度更新
        dp = dxi[:, 1]  # 位置更新
        Rot_up = dR.dot(Rot)  # 更新旋转矩阵
        v_up = dR.dot(v) + dv  # 更新速度
        p_up = dR.dot(p) + dp  # 更新位置

        b_omega_up = b_omega + dx[9:12]  # 更新陀螺仪偏差
        b_acc_up = b_acc + dx[12:15]  # 更新加速度计偏差

        dR = NUMPYIEKF.so3exp(dx[15:18])  # 更新车辆到IMU的旋转矩阵
        Rot_c_i_up = dR.dot(Rot_c_i)  # 更新车辆到IMU的旋转矩阵
        t_c_i_up = t_c_i + dx[18:21]  # 更新车辆到IMU的平移

        I_KH = NUMPYIEKF.IdP - K.dot(H)  # 计算卡尔曼增益的影响
        P_up = I_KH.dot(P).dot(I_KH.T) + K.dot(R).dot(K.T)  # 更新协方差
        P_up = (P_up + P_up.T)/2  # 保证协方差矩阵对称
        return Rot_up, v_up, p_up, b_omega_up, b_acc_up, Rot_c_i_up, t_c_i_up, P_up  # 返回更新后的状态和协方差

    @staticmethod
    def skew(x):
        # 计算反对称矩阵
        X = np.array([[0, -x[2], x[1]],
                      [x[2], 0, -x[0]],
                      [-x[1], x[0], 0]])
        return X  # 返回反对称矩阵

    @staticmethod
    def rot_from_2_vectors(v1, v2):
        # 从两个向量计算旋转矩阵
        v1 = v1/np.linalg.norm(v1)  # 归一化第一个向量
        v2 = v2/np.linalg.norm(v2)  # 归一化第二个向量
        v = np.cross(v1, v2)  # 计算两个向量的叉积
        cosang = np.dot(v1, v2)  # 计算余弦值
        sinang = np.linalg.norm(v)  # 计算正弦值
        Rot = NUMPYIEKF.Id3 + NUMPYIEKF.skew(v) + \
              NUMPYIEKF.skew(v).dot(NUMPYIEKF.skew(v))*(1-cosang)/(sinang**2)  # 计算旋转矩阵
        Rot = NUMPYIEKF.normalize_rot(Rot)  # 归一化旋转矩阵
        return Rot  # 返回旋转矩阵

    @staticmethod
    def sen3exp(xi):
        # 计算三维旋转的指数映射
        phi = xi[:3]  # 提取旋转部分

        angle = np.linalg.norm(phi)  # 计算旋转角度

        # 当|phi|接近0时，使用一阶泰勒展开
        if np.abs(angle) < 1e-8:
            skew_phi = np.array([[0, -phi[2], phi[1]],
                        [phi[2], 0, -phi[0]],
                        [-phi[1], phi[0], 0]])
            J = NUMPYIEKF.Id3 + 0.5 * skew_phi  # 计算雅可比矩阵
            Rot = NUMPYIEKF.Id3 + skew_phi  # 计算旋转矩阵
        else:
            axis = phi / angle  # 计算旋转轴
            skew_axis = np.array([[0, -axis[2], axis[1]],
                        [axis[2], 0, -axis[0]],
                        [-axis[1], axis[0], 0]])
            s = np.sin(angle)  # 计算正弦值
            c = np.cos(angle)  # 计算余弦值
            J = (s / angle) * NUMPYIEKF.Id3 \
                   + (1 - s / angle) * np.outer(axis, axis) + ((1 - c) / angle) * skew_axis  # 计算雅可比矩阵
            Rot = c * NUMPYIEKF.Id3 + (1 - c) * np.outer(axis, axis) + s * skew_axis  # 计算旋转矩阵

        x = J.dot(xi[3:].reshape(-1, 3).T)  # 计算状态更新
        return Rot, x  # 返回旋转矩阵和状态更新

    @staticmethod
    def so3exp(phi):
        # 计算SO(3)的指数映射
        angle = np.linalg.norm(phi)  # 计算旋转角度

        # 当phi接近0时，使用一阶泰勒展开
        if np.abs(angle) < 1e-8:
            skew_phi = np.array([[0, -phi[2], phi[1]],
                      [phi[2], 0, -phi[0]],
                      [-phi[1], phi[0], 0]])
            return np.identity(3) + skew_phi  # 返回单位矩阵加上反对称矩阵

        axis = phi / angle  # 计算旋转轴
        skew_axis = np.array([[0, -axis[2], axis[1]],
                      [axis[2], 0, -axis[0]],
                      [-axis[1], axis[0], 0]])
        s = np.sin(angle)  # 计算正弦值
        c = np.cos(angle)  # 计算余弦值

        return c * NUMPYIEKF.Id3 + (1 - c) * np.outer(axis, axis) + s * skew_axis  # 返回旋转矩阵

    @staticmethod
    def so3left_jacobian(phi):
        # 计算SO(3)的左雅可比矩阵
        angle = np.linalg.norm(phi)  # 计算旋转角度

        # 当|phi|接近0时，使用一阶泰勒展开
        if np.abs(angle) < 1e-8:
            skew_phi = np.array([[0, -phi[2], phi[1]],
                      [phi[2], 0, -phi[0]],
                      [-phi[1], phi[0], 0]])
            return NUMPYIEKF.Id3 + 0.5 * skew_phi  # 返回单位矩阵加上反对称矩阵的一半

        axis = phi / angle  # 计算旋转轴
        skew_axis = np.array([[0, -axis[2], axis[1]],
                      [axis[2], 0, -axis[0]],
                      [-axis[1], axis[0], 0]])
        s = np.sin(angle)  # 计算正弦值
        c = np.cos(angle)  # 计算余弦值

        return (s / angle) * NUMPYIEKF.Id3 \
               + (1 - s / angle) * np.outer(axis, axis) + ((1 - c) / angle) * skew_axis  # 返回左雅可比矩阵

    @staticmethod
    def normalize_rot(Rot):
        # 归一化旋转矩阵
        U, _, V = np.linalg.svd(Rot, full_matrices=False)  # 计算SVD分解

        S = np.eye(3)  # 创建单位矩阵
        S[2, 2] = np.linalg.det(U) * np.linalg.det(V)  # 确保旋转矩阵的行列式为1
        return U.dot(S).dot(V)  # 返回归一化后的旋转矩阵

    @staticmethod
    def from_rpy(roll, pitch, yaw):
        # 从滚转、俯仰、偏航角计算旋转矩阵
        return NUMPYIEKF.rotz(yaw).dot(NUMPYIEKF.roty(pitch).dot(NUMPYIEKF.rotx(roll)))

    @staticmethod
    def rotx(t):
        # 绕x轴旋转的旋转矩阵
        c = np.cos(t)  # 计算余弦值
        s = np.sin(t)  # 计算正弦值
        return np.array([[1,  0,  0],
                         [0,  c, -s],
                         [0,  s,  c]])

    @staticmethod
    def roty(t):
        # 绕y轴旋转的旋转矩阵
        c = np.cos(t)  # 计算余弦值
        s = np.sin(t)  # 计算正弦值
        return np.array([[c,  0,  s],
                         [0,  1,  0],
                         [-s, 0,  c]])

    @staticmethod
    def rotz(t):
        # 绕z轴旋转的旋转矩阵
        c = np.cos(t)  # 计算余弦值
        s = np.sin(t)  # 计算正弦值
        return np.array([[c, -s,  0],
                         [s,  c,  0],
                         [0,  0,  1]])

    @staticmethod
    def to_rpy(Rot):
        # 从旋转矩阵计算滚转、俯仰、偏航角
        pitch = np.arctan2(-Rot[2, 0], np.sqrt(Rot[0, 0]**2 + Rot[1, 0]**2))

        if np.isclose(pitch, np.pi / 2.):
            yaw = 0.  # 当俯仰角接近90度时，偏航角为0
            roll = np.arctan2(Rot[0, 1], Rot[1, 1])  # 计算滚转角
        elif np.isclose(pitch, -np.pi / 2.):
            yaw = 0.  # 当俯仰角接近-90度时，偏航角为0
            roll = -np.arctan2(Rot[0, 1], Rot[1, 1])  # 计算滚转角
        else:
            sec_pitch = 1. / np.cos(pitch)  # 计算俯仰角的倒数
            yaw = np.arctan2(Rot[1, 0] * sec_pitch,
                             Rot[0, 0] * sec_pitch)  # 计算偏航角
            roll = np.arctan2(Rot[2, 1] * sec_pitch,
                              Rot[2, 2] * sec_pitch)  # 计算滚转角
        return roll, pitch, yaw  # 返回滚转、俯仰、偏航角

    def set_learned_covariance(self, torch_iekf):
        # 设置学习到的协方差
        torch_iekf.set_Q()  # 设置Q矩阵
        self.Q = torch_iekf.Q.cpu().detach().numpy()  # 将Q矩阵转换为numpy数组

        beta = torch_iekf.initprocesscov_net.init_cov(torch_iekf)\
            .detach().cpu().numpy()  # 获取学习到的协方差

        # 更新协方差
        self.cov_Rot0 *= beta[0]
        self.cov_v0 *= beta[1]
        self.cov_b_omega0 *= beta[2]
        self.cov_b_acc0 *= beta[3]
        self.cov_Rot_c_i0 *= beta[4]
        self.cov_t_c_i0 *= beta[5]
