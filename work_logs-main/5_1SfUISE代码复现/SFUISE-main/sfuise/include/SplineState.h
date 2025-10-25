#pragma once // 防止头文件被多次包含

#include "utils/common_utils.h" // 引入常用工具函数
#include "utils/math_tools.h" // 引入数学工具函数
#include "sfuise_msgs/Spline.h" // 引入Spline消息定义
#include "sfuise_msgs/Knot.h" // 引入Knot消息定义

// 定义一个模板结构体，用于存储雅可比矩阵的相关信息
template <class MatT>
struct JacobianStruct {
    size_t start_idx; // 起始索引
    std::vector<MatT> d_val_d_knot; // 存储对结点的导数值
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW // 确保内存对齐
};

// 定义不同类型的雅可比矩阵
typedef JacobianStruct<double> Jacobian; // 双精度雅可比
typedef JacobianStruct<Eigen::Matrix<double, 4, 3>> Jacobian43; // 4x3矩阵雅可比
typedef JacobianStruct<Eigen::Matrix3d> Jacobian33; // 3x3矩阵雅可比
typedef JacobianStruct<Eigen::Vector3d> Jacobian13; // 3维向量雅可比
typedef JacobianStruct<Eigen::Matrix<double, 6, 1>> Jacobian16; // 6维列向量雅可比
typedef JacobianStruct<Eigen::Matrix<double, 3, 6>> Jacobian36; // 3x6矩阵雅可比

// SplineState类用于管理样条状态
class SplineState
{
  public:
    SplineState() {}; // 默认构造函数

    // 初始化样条状态
    void init(int64_t dt_ns_, int num_knot_, int64_t start_t_ns_, int start_i_ = 0)
    {
        if_first = true; // 标记是否为第一次初始化
        dt_ns = dt_ns_; // 设置时间间隔
        start_t_ns = start_t_ns_; // 设置起始时间
        num_knot = num_knot_; // 设置结点数量
        inv_dt = 1e9 / dt_ns; // 计算时间间隔的倒数
        start_i = start_i_; // 设置起始索引
        pow_inv_dt[0] = 1.0; // 初始化幂数组
        pow_inv_dt[1] = inv_dt;
        pow_inv_dt[2] = inv_dt * inv_dt;
        pow_inv_dt[3] = pow_inv_dt[2] * inv_dt;
        Eigen::Quaterniond q0 = Eigen::Quaterniond::Identity(); // 初始化四元数
        Eigen::Vector3d t0 = Eigen::Vector3d::Zero(); // 初始化位置向量
        Eigen::Matrix<double, 6, 1> b0 = Eigen::Matrix<double, 6, 1>::Zero(); // 初始化偏置
        q_idle = {q0, q0, q0}; // 初始化空闲四元数数组
        t_idle = {t0, t0, t0}; // 初始化空闲位置数组
        b_idle = {b0, b0, b0}; // 初始化空闲偏置数组
    }

    // 设置单个状态结点
    void setOneStateKnot(int i, Eigen::Quaterniond q, Eigen::Vector3d pos, Eigen::Matrix<double, 6, 1> bias)
    {
        t_knots[i] = pos; // 设置位置
        q_knots[i] = q; // 设置四元数
        b_knots[i] = bias; // 设置偏置
    }

    // 更新结点信息
    void updateKnots(SplineState* other)
    {
        size_t num_knots = other->numKnots(); // 获取其他样条的结点数量
        for (size_t i = 0; i < num_knots; i++) {
            // 根据索引更新结点
            if (i + other->start_i < num_knot) {
                setOneStateKnot(i + other->start_i, other->q_knots[i], other->t_knots[i], other->b_knots[i]);
            } else {
                addOneStateKnot(other->q_knots[i], other->t_knots[i], other->b_knots[i]);
            }
        }
        // 更新空闲状态
        q_idle = other->q_idle;
        t_idle = other->t_idle;
        b_idle = other->b_idle;
    }

    // 获取空闲位置
    Eigen::Vector3d getIdlePos(int idx)
    {
        return t_idle[idx]; // 返回指定索引的空闲位置
    }

    // 设置空闲状态
    void setIdles(int idx, Eigen::Vector3d t, Eigen::Quaterniond q, Eigen::Matrix<double, 6, 1> b)
    {
         t_idle[idx] = t; // 设置空闲位置
         q_idle[idx] = q; // 设置空闲四元数
         b_idle[idx] = b; // 设置空闲偏置
    }

    // 更新第一次窗口的偏置
    void updateBiasIdleFirstWindow()
    {
        if (!if_first) {
            return; // 如果不是第一次，直接返回
        } else {
            b_idle = {b_knots[0], b_knots[0], b_knots[0]}; // 将偏置设置为第一个结点的偏置
        }
    }

    // 添加单个状态结点
    void addOneStateKnot(Eigen::Quaterniond q, Eigen::Vector3d pos, Eigen::Matrix<double, 6, 1> bias)
    {
        // 检查结点数量
        if (num_knot > 1) {
            Eigen::Quaterniond q0 = q_knots[num_knot - 1]; // 获取最后一个四元数
            Eigen::Quaterniond q1 = q; // 当前四元数
            double dot_product = q0.dot(q1); // 计算点积
            if (dot_product < 0) {
               q = Eigen::Quaterniond(-q.w(), -q.x(), -q.y(), -q.z()); // 反转四元数
            }
        }
        // 归一化四元数
        if (abs(q.norm() - 1) > 1e-5) {
            q.normalize();
        }
        // 添加结点
        q_knots.push_back(q);
        t_knots.push_back(pos);
        b_knots.push_back(bias);
        num_knot++; // 增加结点数量
    }

    // 检查四元数控制点
    void checkQuaternionControlPoints()
    {
        if (num_knot > 1) {
            for (size_t i = 1; i < num_knot; i++) {
                Eigen::Quaterniond q1 = q_knots[i]; // 当前四元数
                // 如果前一个四元数与当前四元数的点积小于0，反转当前四元数
                if (q_knots[i - 1].dot(q1) < 0) {
                    q_knots[i] = Eigen::Quaterniond(-q1.w(), -q1.x(), -q1.y(), -q1.z());
                }
            }
        }
    }

    // 移除一个旧状态
    void removeOneOldState()
    {
        // 更新空闲状态
        q_idle = {q_idle[1], q_idle[2], q_knots.front()};
        t_idle = {t_idle[1], t_idle[2], t_knots.front()};
        b_idle = {b_idle[1], b_idle[2], b_knots.front()};
        // 移除结点
        q_knots.pop_front();
        t_knots.pop_front();
        b_knots.pop_front();
        num_knot--; // 减少结点数量
        start_i++; // 更新起始索引
        start_t_ns += dt_ns; // 更新起始时间
        if_first = false; // 标记为非第一次
    }

    // 获取所有状态结点
    void getAllStateKnots(Eigen::aligned_deque<Eigen::Vector3d>& knots_trans,
        Eigen::aligned_deque<Eigen::Quaterniond>& knots_rot,
        Eigen::aligned_deque<Eigen::Matrix<double,6, 1>>& knots_bias)
    {
        knots_trans = t_knots; // 获取位置结点
        knots_rot = q_knots; // 获取四元数结点
        knots_bias = b_knots; // 获取偏置结点
    }

    // 设置所有结点
    void setAllKnots(Eigen::aligned_deque<Eigen::Vector3d>& knots_trans,
        Eigen::aligned_deque<Eigen::Quaterniond>& knots_rot,
        Eigen::aligned_deque<Eigen::Matrix<double,6, 1>>& knots_bias)
    {
        t_knots = knots_trans; // 设置位置结点
        q_knots = knots_rot; // 设置四元数结点
        b_knots = knots_bias; // 设置偏置结点
        updateBiasIdleFirstWindow(); // 更新偏置
    }

    // 获取结点时间
    int64_t getKnotTimeNs(size_t i) const
    {
        return start_t_ns + i * dt_ns; // 返回结点的时间
    }

    // 获取结点的四元数
    Eigen::Quaterniond getKnotOrt(size_t i)
    {
        return q_knots[i]; // 返回指定索引的四元数
    }

    // 获取结点的位置
    Eigen::Vector3d getKnotPos(size_t i)
    {
        return t_knots[i]; // 返回指定索引的位置
    }

    // 获取结点的偏置
    Eigen::Matrix<double, 6, 1> getKnotBias(size_t i)
    {
        return b_knots[i]; // 返回指定索引的偏置
    }

    // 外推位置结点
    Eigen::Vector3d extrapolatePosKnot(size_t idx)
    {
        Eigen::Quaterniond last_ort = q_knots[num_knot - idx - 1]; // 获取最后一个四元数
        Eigen::Quaterniond cur_ort = q_knots[num_knot - idx]; // 当前四元数
        Eigen::Vector3d last_trans = t_knots[num_knot - idx - 1]; // 获取最后一个位置
        Eigen::Vector3d cur_trans = t_knots[num_knot - idx]; // 当前位置信息
        Eigen::Vector3d rel_trans = last_ort.inverse() * (cur_trans - last_trans); // 计算相对位置
        return cur_trans + cur_ort * rel_trans; // 返回外推位置
    }

    // 外推四元数结点
    Eigen::Quaterniond extrapolateOrtKnot(size_t idx)
    {
        Eigen::Quaterniond last_ort = q_knots[num_knot - idx - 1]; // 获取最后一个四元数
        Eigen::Quaterniond cur_ort = q_knots[num_knot - idx]; // 当前四元数
        return cur_ort * last_ort.inverse() * cur_ort; // 返回外推四元数
    }

    // 应用姿态增量
    void applyPoseInc(int i, const Eigen::Matrix<double, 6, 1> &inc)
    {
        t_knots[i] += inc.head<3>(); // 更新位置
        Eigen::Quaterniond q_inc; // 定义增量四元数
        Quater::exp(inc.tail<3>(), q_inc); // 计算增量四元数
        q_knots[i] *= q_inc; // 更新四元数
    }

    // 应用偏置增量
    void applyBiasInc(int i, const Eigen::Matrix<double, 6, 1>& inc)
    {
        b_knots[i] += inc; // 更新偏置
    }

    // 获取最大时间
    int64_t maxTimeNs()
    {
        if (num_knot == 1) {
           return start_t_ns; // 如果只有一个结点，返回起始时间
        }
        return start_t_ns + (num_knot - 1) * dt_ns - 1; // 返回最大时间
    }

    // 获取最小时间
    int64_t minTimeNs()
    {
        return start_t_ns + dt_ns * (!if_first ?  -1 : 0); // 返回最小时间
    }

    // 获取下一个最大时间
    int64_t nextMaxTimeNs()
    {
        return start_t_ns + num_knot * dt_ns - 1; // 返回下一个最大时间
    }

    // 获取结点数量
    size_t numKnots()
    {
        return num_knot; // 返回结点数量
    }

    // 插值位置
    template <int Derivative = 0>
    Eigen::Vector3d itpPosition (int64_t time_ns, Jacobian* J = nullptr) const
    {
        return itpEuclidean<Eigen::Vector3d, Derivative>(time_ns, t_idle, t_knots, J); // 返回插值位置
    }

    // 插值偏置
    Eigen::Matrix<double, 6, 1> itpBias (int64_t time_ns, Jacobian* J = nullptr) const
    {
        return itpEuclidean<Eigen::Matrix<double, 6, 1>>(time_ns, b_idle, b_knots, J); // 返回插值偏置
    }

    // 插值四元数
    void itpQuaternion(int64_t t_ns, Eigen::Quaterniond* q_out = nullptr,
        Eigen::Vector3d* w_out = nullptr, Jacobian43* J_q = nullptr, Jacobian33* J_w = nullptr) const
    {
        double u; // 插值因子
        int64_t idx0; // 索引0
        int idx_r; // 右索引
        std::array<Eigen::Quaterniond, 4> cps; // 控制点数组
        prepareInterpolation(t_ns, q_idle, q_knots, idx0, u, cps, idx_r); // 准备插值
        Eigen::Vector4d p; // 插值系数
        Eigen::Vector4d coeff; // 计算系数
        baseCoeffsWithTime<0>(p, u); // 计算基系数
        coeff = cumulative_blending_matrix * p; // 计算最终系数
        Eigen::Quaterniond q_delta[3]; // 四元数增量数组
        q_delta[0] = cps[0].inverse() * cps[1]; // 计算四元数增量
        q_delta[1] = cps[1].inverse() * cps[2];
        q_delta[2] = cps[2].inverse() * cps[3];
        Eigen::Vector3d t_delta[3]; // 位置增量数组
        Eigen::Vector3d t_delta_scale[3]; // 缩放位置增量数组
        Eigen::Quaterniond q_delta_scale[3]; // 缩放四元数增量数组
        Eigen::Quaterniond q_itps[4]; // 插值四元数数组
        Eigen::Vector3d w_itps[4]; // 插值角速度数组
        Eigen::Vector4d dcoeff; // 导数系数
        if (J_q || J_w) { // 如果需要雅可比
            Eigen::Matrix<double, 3, 4> dlog_dq[3]; // 四元数对数导数
            Eigen::Matrix<double, 4, 3> dexp_dt[3]; // 四元数指数导数
            Quater::dlog(q_delta[0], t_delta[0], dlog_dq[0]); // 计算对数导数
            Quater::dlog(q_delta[1], t_delta[1], dlog_dq[1]);
            Quater::dlog(q_delta[2], t_delta[2], dlog_dq[2]);
            t_delta_scale[0] = t_delta[0] * coeff[1]; // 缩放位置增量
            t_delta_scale[1] = t_delta[1] * coeff[2];
            t_delta_scale[2] = t_delta[2] * coeff[3];
            Quater::dexp(t_delta_scale[0], q_delta_scale[0], dexp_dt[0]); // 计算指数导数
            Quater::dexp(t_delta_scale[1], q_delta_scale[1], dexp_dt[1]);
            Quater::dexp(t_delta_scale[2], q_delta_scale[2], dexp_dt[2]);
            int size_J = std::min(idx_r + 1, 4); // 计算雅可比大小
            Eigen::Matrix4d d_X_d_dj[3]; // 雅可比矩阵
            Eigen::Matrix<double, 3, 4> d_r_d_dj[3]; // 位置雅可比
            Eigen::Quaterniond q_r_all[4]; // 四元数数组
            q_r_all[3] = Eigen::Quaterniond::Identity(); // 初始化为单位四元数
            for (int i = 2; i >= 0; i-- ) {
                q_r_all[i] = q_delta_scale[i] * q_r_all[i+1]; // 计算四元数
            }
            Eigen::Matrix4d Q_l[size_J - 1]; // 左侧矩阵
            Eigen::Matrix4d Q_r[size_J - 1]; // 右侧矩阵
            for (int i = 0; i < size_J - 1; i++) {
                Quater::Qleft(q_delta[4 - size_J + i], Q_l[i]); // 计算左侧矩阵
                Quater::Qright(q_delta[4 - size_J + i], Q_r[i]); // 计算右侧矩阵
            }
            if (J_q) { // 如果需要四元数雅可比
                q_itps[0] = cps[0]; // 初始化插值四元数
                q_itps[1] = q_itps[0] * q_delta_scale[0];
                q_itps[2] = q_itps[1] * q_delta_scale[1];
                q_itps[3] = q_itps[2] * q_delta_scale[2];
                *q_out = q_itps[3]; // 输出插值四元数
                Eigen::Matrix4d Q_l_all[3]; // 所有左侧矩阵
                Quater::Qleft(q_itps[0], Q_l_all[0]);
                Quater::Qleft(q_itps[1], Q_l_all[1]);
                Quater::Qleft(q_itps[2], Q_l_all[2]);
                for (int i = 2; i >= 0; i--) {
                    Eigen::Matrix4d Q_r_all; // 所有右侧矩阵
                    Quater::Qright(q_r_all[i+1], Q_r_all);
                    d_X_d_dj[i].noalias() = coeff[i + 1] * Q_r_all * Q_l_all[i] * dexp_dt[i] * dlog_dq[i]; // 计算雅可比
                }
                J_q->d_val_d_knot.resize(size_J); // 调整雅可比大小
                for (int i = 0; i < size_J; i++) {
                    J_q->d_val_d_knot[i].setZero(); // 初始化雅可比
                }
                for (int i = 0; i < size_J - 1; i++) {
                    J_q->d_val_d_knot[i].noalias() -= d_X_d_dj[4 - size_J + i] * Q_r[i].rightCols(3); // 更新雅可比
                    J_q->d_val_d_knot[i + 1].noalias() += d_X_d_dj[4 - size_J + i] * Q_l[i].rightCols(3);
                }
                J_q->start_idx = idx0; // 设置雅可比起始索引
                if (size_J == 4) {
                    Eigen::Matrix4d Q_r_all; // 右侧矩阵
                    Eigen::Matrix4d Q0_left; // 左侧矩阵
                    Quater::Qright(q_r_all[0], Q_r_all);
                    Quater::Qleft(cps[0], Q0_left);
                    J_q->d_val_d_knot[0].noalias() += Q_r_all * Q0_left.rightCols(3); // 更新雅可比
                } else {
                    Eigen::Matrix4d Q_left; // 左侧矩阵
                    Quater::Qleft(q_delta[3 - size_J], Q_left);
                    J_q->d_val_d_knot[0].noalias() += d_X_d_dj[3 - size_J] * Q_left.rightCols(3); // 更新雅可比
                }
            }
            if (J_w) { // 如果需要角速度雅可比
                baseCoeffsWithTime<1>(p, u); // 计算基系数
                dcoeff = inv_dt * cumulative_blending_matrix * p; // 计算导数系数
                w_itps[0].setZero(); // 初始化角速度
                w_itps[1] = 2 * dcoeff[1] * t_delta[0]; // 计算角速度
                w_itps[2] = q_delta_scale[1].inverse() * w_itps[1] + 2 * dcoeff[2] * t_delta[1];
                w_itps[3] = q_delta_scale[2].inverse() * w_itps[2] + 2 * dcoeff[3] * t_delta[2];
                *w_out = w_itps[3]; // 输出角速度
                Eigen::Matrix<double, 3, 4> drot_dq[3]; // 角速度对四元数的导数
                Quater::drot(w_itps[0], q_delta_scale[0], drot_dq[0]); // 计算导数
                Quater::drot(w_itps[1], q_delta_scale[1], drot_dq[1]);
                Quater::drot(w_itps[2], q_delta_scale[2], drot_dq[2]);
                for (int i = 2; i >= 0; i--) {
                    Eigen::Matrix3d d_vel_d_dj = coeff[i + 1] * drot_dq[i] * dexp_dt[i]; // 计算速度导数
                    d_vel_d_dj.noalias() += 2 * dcoeff[i + 1] * Eigen::Matrix3d::Identity(); // 更新速度导数
                    d_r_d_dj[i].noalias() = q_r_all[i+1].inverse().toRotationMatrix() * d_vel_d_dj * dlog_dq[i]; // 更新位置雅可比
                }
                J_w->d_val_d_knot.resize(size_J); // 调整雅可比大小
                for (int i = 0; i < size_J; i++) {
                    J_w->d_val_d_knot[i].setZero(); // 初始化雅可比
                }
                for (int i = 0; i < size_J - 1; i++) {
                    J_w->d_val_d_knot[i].noalias() -= d_r_d_dj[4 - size_J + i] * Q_r[i].rightCols(3); // 更新雅可比
                    J_w->d_val_d_knot[i + 1].noalias() += d_r_d_dj[4 - size_J + i] * Q_l[i].rightCols(3);
                }
                J_w->start_idx = idx0; // 设置雅可比起始索引
                if (size_J != 4) {
                    Eigen::Matrix4d Q_left; // 左侧矩阵
                    Quater::Qleft(q_delta[4 - size_J - 1], Q_left);
                    J_w->d_val_d_knot[0].noalias() += d_r_d_dj[3 - size_J] *  Q_left.rightCols(3); // 更新雅可比
                }
            }
        } else { // 如果不需要雅可比
            Quater::log(q_delta[0], t_delta[0]); // 计算对数
            Quater::log(q_delta[1], t_delta[1]);
            Quater::log(q_delta[2], t_delta[2]);
            t_delta_scale[0] = t_delta[0] * coeff[1]; // 缩放位置增量
            t_delta_scale[1] = t_delta[1] * coeff[2];
            t_delta_scale[2] = t_delta[2] * coeff[3];
            Quater::exp(t_delta_scale[0], q_delta_scale[0]); // 计算指数
            Quater::exp(t_delta_scale[1], q_delta_scale[1]);
            Quater::exp(t_delta_scale[2], q_delta_scale[2]);
            if (q_out) { // 如果需要输出四元数
                q_itps[0] = cps[0]; // 初始化插值四元数
                q_itps[1] = q_itps[0] * q_delta_scale[0];
                q_itps[2] = q_itps[1] * q_delta_scale[1];
                q_itps[3] = q_itps[2] * q_delta_scale[2];
                q_itps[3].normalize(); // 归一化四元数
                *q_out = q_itps[3]; // 输出插值四元数
            }
            if (w_out) { // 如果需要输出角速度
                baseCoeffsWithTime<1>(p, u); // 计算基系数
                dcoeff = inv_dt * cumulative_blending_matrix * p; // 计算导数系数

                w_itps[0].setZero(); // 初始化角速度
                w_itps[1] = 2 * dcoeff[1] * t_delta[0]; // 计算角速度
                w_itps[2] = q_delta_scale[1].inverse() * w_itps[1] + 2 * dcoeff[2] * t_delta[1];
                w_itps[3] = q_delta_scale[2].inverse() * w_itps[2] + 2 * dcoeff[3] * t_delta[2];
                *w_out = w_itps[3]; // 输出角速度
            }
        }
    }

    // 获取样条消息
    void getSplineMsg(sfuise_msgs::Spline& spline_msg)
    {
        spline_msg.dt = dt_ns; // 设置时间间隔
        spline_msg.start_t = start_t_ns; // 设置起始时间
        spline_msg.start_idx = start_i; // 设置起始索引
        for (size_t i = 0; i < num_knot; i++) {
            sfuise_msgs::Knot knot_msg; // 创建结点消息
            knot_msg.position.x = t_knots[i].x(); // 设置位置
            knot_msg.position.y = t_knots[i].y();
            knot_msg.position.z = t_knots[i].z();
            knot_msg.orientation.w = q_knots[i].w(); // 设置四元数
            knot_msg.orientation.x = q_knots[i].x();
            knot_msg.orientation.y = q_knots[i].y();
            knot_msg.orientation.z = q_knots[i].z();
            Eigen::Matrix<double, 6, 1> bias = b_knots[i]; // 获取偏置
            knot_msg.bias_acc.x = bias[0]; // 设置加速度偏置
            knot_msg.bias_acc.y = bias[1];
            knot_msg.bias_acc.z = bias[2];
            knot_msg.bias_gyro.x = bias[3]; // 设置陀螺仪偏置
            knot_msg.bias_gyro.y = bias[4];
            knot_msg.bias_gyro.z = bias[5];
            spline_msg.knots.push_back(knot_msg); // 添加结点消息
        }
        for (int i = 0; i < 3; i++) {
            sfuise_msgs::Knot idle_msg; // 创建空闲结点消息
            idle_msg.position.x = t_idle[i].x(); // 设置空闲位置
            idle_msg.position.y = t_idle[i].y();
            idle_msg.position.z = t_idle[i].z();
            idle_msg.orientation.w = q_idle[i].w(); // 设置空闲四元数
            idle_msg.orientation.x = q_idle[i].x();
            idle_msg.orientation.y = q_idle[i].y();
            idle_msg.orientation.z = q_idle[i].z();
            Eigen::Matrix<double, 6, 1> bias = b_idle[i]; // 获取空闲偏置
            idle_msg.bias_acc.x = bias[0]; // 设置加速度偏置
            idle_msg.bias_acc.y = bias[1];
            idle_msg.bias_acc.z = bias[2];
            idle_msg.bias_gyro.x = bias[3]; // 设置陀螺仪偏置
            idle_msg.bias_gyro.y = bias[4];
            idle_msg.bias_gyro.z = bias[5];
            spline_msg.idles.push_back(idle_msg); // 添加空闲结点消息
        }
    }

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW // 确保内存对齐

  private:
    bool if_first; // 标记是否为第一次初始化

    static constexpr double S_TO_NS = 1e9; // 秒转纳秒的常量
    static const Eigen::Matrix4d blending_matrix; // 混合矩阵
    static const Eigen::Matrix4d base_coefficients; // 基系数矩阵
    static const Eigen::Matrix4d cumulative_blending_matrix; // 累积混合矩阵

    int64_t dt_ns; // 时间间隔（纳秒）
    double inv_dt; // 时间间隔的倒数
    std::array<double, 4> pow_inv_dt; // 幂数组
    int num_knot; // 结点数量
    int64_t start_i; // 起始索引
    int64_t start_t_ns; // 起始时间（纳秒）

    std::array<Eigen::Quaterniond, 3> q_idle; // 空闲四元数数组
    std::array<Eigen::Vector3d, 3> t_idle; // 空闲位置数组
    std::array<Eigen::Matrix<double, 6, 1>, 3> b_idle; // 空闲偏置数组
    Eigen::aligned_deque<Eigen::Quaterniond> q_knots; // 四元数结点队列
    Eigen::aligned_deque<Eigen::Vector3d> t_knots; // 位置结点队列
    Eigen::aligned_deque<Eigen::Matrix<double, 6, 1>> b_knots; // 偏置结点队列

    // 插值函数
    template <typename _KnotT, int Derivative = 0>
    _KnotT itpEuclidean(int64_t t_ns, const std::array<_KnotT, 3>& knots_idle,
                        const Eigen::aligned_deque<_KnotT>& knots, Jacobian* J = nullptr) const
    {
        double u; // 插值因子
        int64_t idx0; // 索引0
        int idx_r; // 右索引
        std::array<_KnotT,4> cps; // 控制点数组
        prepareInterpolation(t_ns, knots_idle, knots, idx0, u, cps, idx_r); // 准备插值
        Eigen::Vector4d p, coeff; // 插值系数
        baseCoeffsWithTime<Derivative>(p, u); // 计算基系数
        coeff = pow_inv_dt[Derivative] * (blending_matrix * p); // 计算最终系数
        _KnotT res_out = coeff[0] * cps[0] + coeff[1] * cps[1] + coeff[2] * cps[2] + coeff[3] * cps[3]; // 计算插值结果
        if (J) { // 如果需要雅可比
            int size_J = std::min(idx_r + 1, 4); // 计算雅可比大小
            J->d_val_d_knot.resize(size_J); // 调整雅可比大小
            for (int i = 0; i < size_J; i++) {
                J->d_val_d_knot[i] = coeff[4 - size_J + i]; // 设置雅可比值
            }
            J->start_idx = idx0; // 设置雅可比起始索引
        }
        return res_out; // 返回插值结果
    }

    // 准备插值
    template<typename _KnotT>
    void prepareInterpolation(int64_t t_ns, const std::array<_KnotT, 3>& knots_idle,
                              const Eigen::aligned_deque<_KnotT>& knots, int64_t& idx0, double& u,
                              std::array<_KnotT,4>& cps, int& idx_r) const
    {
        int64_t t_ns_rel = t_ns - start_t_ns; // 计算相对时间
        int idx_l = floor(double(t_ns_rel) / double(dt_ns)); // 计算左索引
        idx_r = idx_l + 1; // 计算右索引
        idx0 = std::max(idx_l - 2, 0); // 计算控制点起始索引
        for (int i = 0; i < 2 - idx_l; i++) {
            cps[i] = knots_idle[i + idx_l + 1]; // 设置控制点
        }
        int idx_window = std::max(0, 2 - idx_l); // 计算窗口索引
        for (int i = 0; i < std::min(idx_l + 2, 4); i++) {
            cps[i + idx_window] = knots[idx0 + i]; // 设置控制点
        }
        u = (t_ns - start_t_ns - idx_l * dt_ns) / double(dt_ns); // 计算插值因子
    }

    // 计算基系数
    template <int Derivative, class Derived>
    static void baseCoeffsWithTime(const Eigen::MatrixBase<Derived>& res_const, double t)
    {
        EIGEN_STATIC_ASSERT_VECTOR_SPECIFIC_SIZE(Derived, 4); // 确保大小为4
        Eigen::MatrixBase<Derived>& res = const_cast<Eigen::MatrixBase<Derived>&>(res_const); // 获取结果引用
        res.setZero(); // 初始化为零
        res[Derivative] = base_coefficients(Derivative, Derivative); // 设置基系数
        double ti = t; // 临时变量
        for (int j = Derivative + 1; j < 4; j++) {
            res[j] = base_coefficients(Derivative, j) * ti; // 计算基系数
            ti = ti * t; // 更新临时变量
        }
    }

    // 计算混合矩阵
    template <bool _Cumulative = false>
    static Eigen::Matrix4d computeBlendingMatrix()
    {
        Eigen::Matrix4d m; // 初始化混合矩阵
        m.setZero(); // 设置为零
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                double sum = 0; // 初始化和
                for (int s = j; s < 4; ++s) {
                    sum += std::pow(-1.0, s - j) * binomialCoefficient(4, s - j) *
                    std::pow(4 - s - 1.0, 4 - 1.0 - i); // 计算和
                }
                m(j, i) = binomialCoefficient(3, 3 - i) * sum; // 设置混合矩阵值
            }
        }
        if (_Cumulative) { // 如果是累积混合
            for (int i = 0; i < 4; i++) {
                for (int j = i + 1; j < 4; j++) {
                    m.row(i) += m.row(j); // 累积行
                }
            }
        }
        uint64_t factorial = 1; // 初始化阶乘
        for (int i = 2; i < 4; ++i) {
            factorial *= i; // 计算阶乘
        }
        return m / factorial; // 返回归一化的混合矩阵
    }

    // 计算二项式系数
    constexpr static inline uint64_t binomialCoefficient(uint64_t n, uint64_t k)
    {
        if (k > n) return 0; // 如果k大于n，返回0
        uint64_t r = 1; // 初始化结果
        for (uint64_t d = 1; d <= k; ++d) {
            r *= n--; // 计算结果
            r /= d; // 除以d
        }
        return r; // 返回结果
    }

    // 计算基系数矩阵
    static Eigen::Matrix4d computeBaseCoefficients()
    {
        Eigen::Matrix4d base_coeff; // 初始化基系数矩阵
        base_coeff.setZero(); // 设置为零
        base_coeff.row(0).setOnes(); // 第一行设置为1
        int order = 3; // 初始化阶数
        for (int n = 1; n < 4; n++) {
            for (int i = 3 - order; i < 4; i++) {
                base_coeff(n, i) = (order - 3 + i) * base_coeff(n - 1, i); // 计算基系数
            }
            order--; // 减少阶数
        }
        return base_coeff; // 返回基系数矩阵
    }
};

// 计算并初始化静态成员
const Eigen::Matrix4d SplineState::base_coefficients = SplineState::computeBaseCoefficients();
const Eigen::Matrix4d SplineState::blending_matrix = SplineState::computeBlendingMatrix();
const Eigen::Matrix4d SplineState::cumulative_blending_matrix = SplineState::computeBlendingMatrix<true>();
