#pragma once  // 防止头文件被重复包含

#include "utils/common_utils.h"  // 包含通用工具函数
#include "utils/math_tools.h"    // 包含数学工具函数
#include "sfuise_msgs/msg/spline.hpp"  // 包含样条消息定义
#include "sfuise_msgs/msg/knot.hpp"    // 包含节点消息定义

// 定义雅可比矩阵结构体模板
template <class MatT>
struct JacobianStruct {
    size_t start_idx;  // 起始索引
    std::vector<MatT> d_val_d_knot;  // 对节点的导数向量
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW  // Eigen内存对齐宏
};

// 定义不同类型的雅可比矩阵
typedef JacobianStruct<double> Jacobian;  // 标量雅可比
typedef JacobianStruct<Eigen::Matrix<double, 4, 3>> Jacobian43;  // 4x3矩阵雅可比
typedef JacobianStruct<Eigen::Matrix3d> Jacobian33;  // 3x3矩阵雅可比
typedef JacobianStruct<Eigen::Vector3d> Jacobian13;  // 3维向量雅可比
typedef JacobianStruct<Eigen::Matrix<double, 6, 1>> Jacobian16;  // 6维向量雅可比
typedef JacobianStruct<Eigen::Matrix<double, 3, 6>> Jacobian36;  // 3x6矩阵雅可比

// 样条状态类定义
class SplineState {
  public:
    SplineState() {};  // 默认构造函数

    // 初始化函数
    void init(int64_t dt_ns_, int num_knot_, int64_t start_t_ns_, int start_i_ = 0) {
        if_first = true;  // 标记是否为第一次初始化
        dt_ns = dt_ns_;  // 设置时间间隔(纳秒)
        start_t_ns = start_t_ns_;  // 设置起始时间，imu开头ts
        num_knot = num_knot_;  // 设置节点数量
        inv_dt = 1e9 / dt_ns;  // 计算时间间隔的倒数
        start_i = start_i_;  // 设置起始索引
        // 计算时间间隔的幂次
        pow_inv_dt[0] = 1.0;
        pow_inv_dt[1] = inv_dt;
        pow_inv_dt[2] = inv_dt * inv_dt;
        pow_inv_dt[3] = pow_inv_dt[2] * inv_dt;
        // 初始化空闲状态
        Eigen::Quaterniond q0 = Eigen::Quaterniond::Identity();
        Eigen::Vector3d t0 = Eigen::Vector3d::Zero();
        Eigen::Matrix<double, 6, 1> b0 = Eigen::Matrix<double, 6, 1>::Zero();
        q_idle = {q0, q0, q0};
        t_idle = {t0, t0, t0};
        b_idle = {b0, b0, b0};
    }

    // 设置单个状态节点
    void setOneStateKnot(int i, Eigen::Quaterniond q, Eigen::Vector3d pos, Eigen::Matrix<double, 6, 1> bias) {
        t_knots[i] = pos;  // 设置位置
        q_knots[i] = q;    // 设置姿态
        b_knots[i] = bias; // 设置偏差
    }

    // 更新节点
    void updateKnots(SplineState* other) {
        size_t num_knots = other->numKnots();
        for (size_t i = 0; i < num_knots; i++) {
            if (i + other->start_i < num_knot) {
                setOneStateKnot(i + other->start_i, other->q_knots[i], other->t_knots[i], other->b_knots[i]);
            } else {
                addOneStateKnot(other->q_knots[i], other->t_knots[i], other->b_knots[i]);
            }
        }
        q_idle = other->q_idle;
        t_idle = other->t_idle;
        b_idle = other->b_idle;
    }

    // 获取空闲位置
    Eigen::Vector3d getIdlePos(int idx) {
        return t_idle[idx];
    }

    // 设置空闲状态
    void setIdles(int idx, Eigen::Vector3d t, Eigen::Quaterniond q, Eigen::Matrix<double, 6, 1> b) {
        t_idle[idx] = t;
        q_idle[idx] = q;
        b_idle[idx] = b;
    }

    // 更新第一个窗口的偏差空闲状态
    void updateBiasIdleFirstWindow() {
        if (!if_first) {
            return;
        } else {
            b_idle = {b_knots[0], b_knots[0], b_knots[0]};
        }
    }

    // 添加一个状态节点
    void addOneStateKnot(Eigen::Quaterniond q, Eigen::Vector3d pos, Eigen::Matrix<double, 6, 1> bias) {
        // 处理四元数方向
        if (num_knot > 1) {
            Eigen::Quaterniond q0 = q_knots[num_knot - 1];
            Eigen::Quaterniond q1 = q;
            double dot_product = q0.dot(q1);
            if (dot_product < 0) {
                q = Eigen::Quaterniond(-q.w(), -q.x(), -q.y(), -q.z());
            }
        }
        // 归一化四元数
        if (abs(q.norm() - 1) > 1e-5) {
            q.normalize();
        }
        // 添加节点
        q_knots.push_back(q);
        t_knots.push_back(pos);
        b_knots.push_back(bias);
        num_knot++;
    }

    // 检查四元数控制点
    void checkQuaternionControlPoints() {
        if (num_knot > 1) {
            for (size_t i = 1; i < num_knot; i++) {
                Eigen::Quaterniond q1 = q_knots[i];
                if (q_knots[i - 1].dot(q1) < 0) {
                    q_knots[i] = Eigen::Quaterniond(-q1.w(), -q1.x(), -q1.y(), -q1.z());
                }
            }
        }
    }

    // 移除一个旧状态
    void removeOneOldState() {
        q_idle = {q_idle[1], q_idle[2], q_knots.front()};
        t_idle = {t_idle[1], t_idle[2], t_knots.front()};
        b_idle = {b_idle[1], b_idle[2], b_knots.front()};
        q_knots.pop_front();
        t_knots.pop_front();
        b_knots.pop_front();
        num_knot--;
        start_i++;
        start_t_ns += dt_ns;
        if_first = false;
    }

    // 获取所有状态节点
    void getAllStateKnots(Eigen::aligned_deque<Eigen::Vector3d>& knots_trans,
        Eigen::aligned_deque<Eigen::Quaterniond>& knots_rot,
        Eigen::aligned_deque<Eigen::Matrix<double,6, 1>>& knots_bias) {
        knots_trans = t_knots;
        knots_rot = q_knots;
        knots_bias = b_knots;
    }

    // 设置所有节点
    void setAllKnots(Eigen::aligned_deque<Eigen::Vector3d>& knots_trans,
        Eigen::aligned_deque<Eigen::Quaterniond>& knots_rot,
        Eigen::aligned_deque<Eigen::Matrix<double,6, 1>>& knots_bias) {
        t_knots = knots_trans;
        q_knots = knots_rot;
        b_knots = knots_bias;
        updateBiasIdleFirstWindow();
    }

    // 获取节点时间(纳秒)
    int64_t getKnotTimeNs(size_t i) const {
        return start_t_ns + i * dt_ns;
    }

    // 获取节点姿态
    Eigen::Quaterniond getKnotOrt(size_t i) {
        return q_knots[i];
    }

    // 获取节点位置
    Eigen::Vector3d getKnotPos(size_t i) {
        return t_knots[i];
    }

    // 获取节点偏差
    Eigen::Matrix<double, 6, 1> getKnotBias(size_t i) {
        return b_knots[i];
    }

    // 外推位置节点
    Eigen::Vector3d extrapolatePosKnot(size_t idx) {
        Eigen::Quaterniond last_ort = q_knots[num_knot - idx - 1];
        Eigen::Quaterniond cur_ort = q_knots[num_knot - idx];
        Eigen::Vector3d last_trans = t_knots[num_knot - idx - 1];
        Eigen::Vector3d cur_trans = t_knots[num_knot - idx];
        Eigen::Vector3d rel_trans = last_ort.inverse() * (cur_trans - last_trans);
        return cur_trans + cur_ort * rel_trans;
    }
    // 外推姿态节点
    Eigen::Quaterniond extrapolateOrtKnot(size_t idx)
    {
        // 获取前一个和当前姿态节点
        Eigen::Quaterniond last_ort = q_knots[num_knot - idx - 1];
        Eigen::Quaterniond cur_ort = q_knots[num_knot - idx];
        // 计算并返回外推姿态
        return cur_ort * last_ort.inverse() * cur_ort;
    }

    // 应用姿态增量
    void applyPoseInc(int i, const Eigen::Matrix<double, 6, 1> &inc)
    {
        // 更新位置增量
        t_knots[i] += inc.head<3>();
        // 计算姿态增量并更新姿态
        Eigen::Quaterniond q_inc;
        Quater::exp(inc.tail<3>(), q_inc);
        q_knots[i] *= q_inc;
    }

    // 应用偏差增量
    void applyBiasInc(int i, const Eigen::Matrix<double, 6, 1>& inc)
    {
        // 更新偏差
        b_knots[i] += inc;
    }

    // 获取最大时间(纳秒)
    int64_t maxTimeNs()
    {
        // 如果只有一个节点,返回起始时间
        if (num_knot == 1) {
           return start_t_ns;
        }
        // 否则返回最后一个节点的时间
        return start_t_ns + (num_knot - 1) * dt_ns - 1;
    }

    // 获取最小时间(纳秒)
    int64_t minTimeNs()
    {
        // 根据是否第一个节点返回最小时间
        // 返回最小时间：如果不是第一个节点(if_first为false)，则返回起始时间减去一个时间间隔；
        // 否则直接返回起始时间
        return start_t_ns + dt_ns * (!if_first ? -1 : 0);
    }

    // 获取下一个最大时间(纳秒)
    int64_t nextMaxTimeNs()
    {
        // 返回下一个节点的时间
        return start_t_ns + num_knot * dt_ns - 1;
    }

    // 获取节点数量
    size_t numKnots()
    {
        return num_knot;
    }

    // 插值位置
    template <int Derivative = 0>
    Eigen::Vector3d itpPosition (int64_t time_ns, Jacobian* J = nullptr) const
    {
        // 调用欧几里得空间插值
        return itpEuclidean<Eigen::Vector3d, Derivative>(time_ns, t_idle, t_knots, J);
    }

    // 插值偏差
    Eigen::Matrix<double, 6, 1> itpBias (int64_t time_ns, Jacobian* J = nullptr) const
    {
        // 调用欧几里得空间插值
        return itpEuclidean<Eigen::Matrix<double, 6, 1>>(time_ns, b_idle, b_knots, J);
    }

    // 插值四元数
    void itpQuaternion(int64_t t_ns, Eigen::Quaterniond* q_out = nullptr,
        Eigen::Vector3d* w_out = nullptr, Jacobian43* J_q = nullptr, Jacobian33* J_w = nullptr) const
    {
        // 准备插值参数
        double u;
        int64_t idx0;
        int idx_r;
        std::array<Eigen::Quaterniond, 4> cps;
        prepareInterpolation(t_ns, q_idle, q_knots, idx0, u, cps, idx_r);
        
        // 计算基函数系数
        Eigen::Vector4d p;
        Eigen::Vector4d coeff;
        baseCoeffsWithTime<0>(p, u);
        coeff = cumulative_blending_matrix * p;
        
        // 计算姿态增量
        Eigen::Quaterniond q_delta[3];
        q_delta[0] = cps[0].inverse() * cps[1];
        q_delta[1] = cps[1].inverse() * cps[2];
        q_delta[2] = cps[2].inverse() * cps[3];
        
        // 计算对数映射和指数映射
        Eigen::Vector3d t_delta[3];
        Eigen::Vector3d t_delta_scale[3];
        Eigen::Quaterniond q_delta_scale[3];
        Eigen::Quaterniond q_itps[4];
        Eigen::Vector3d w_itps[4];
        Eigen::Vector4d dcoeff;
        
        // 如果需要计算雅可比矩阵
        if (J_q || J_w) {
            // 计算对数映射的导数
            Eigen::Matrix<double, 3, 4> dlog_dq[3];
            Eigen::Matrix<double, 4, 3> dexp_dt[3];
            Quater::dlog(q_delta[0], t_delta[0], dlog_dq[0]);
            Quater::dlog(q_delta[1], t_delta[1], dlog_dq[1]);
            Quater::dlog(q_delta[2], t_delta[2], dlog_dq[2]);
            
            // 计算缩放后的增量
            t_delta_scale[0] = t_delta[0] * coeff[1];
            t_delta_scale[1] = t_delta[1] * coeff[2];
            t_delta_scale[2] = t_delta[2] * coeff[3];
            
            // 计算指数映射的导数
            Quater::dexp(t_delta_scale[0], q_delta_scale[0], dexp_dt[0]);
            Quater::dexp(t_delta_scale[1], q_delta_scale[1], dexp_dt[1]);
            Quater::dexp(t_delta_scale[2], q_delta_scale[2], dexp_dt[2]);
            
            // 计算雅可比矩阵
            int size_J = std::min(idx_r + 1, 4);
            Eigen::Matrix4d d_X_d_dj[3];
            Eigen::Matrix<double, 3, 4> d_r_d_dj[3];
            Eigen::Quaterniond q_r_all[4];
            q_r_all[3] = Eigen::Quaterniond::Identity();
            
            // 计算累积姿态
            for (int i = 2; i >= 0; i-- ) {
                q_r_all[i] = q_delta_scale[i] * q_r_all[i+1];
            }
            
            // 计算左右乘矩阵
            Eigen::Matrix4d Q_l[size_J - 1];
            Eigen::Matrix4d Q_r[size_J - 1];
            for (int i = 0; i < size_J - 1; i++) {
                Quater::Qleft(q_delta[4 - size_J + i], Q_l[i]);
                Quater::Qright(q_delta[4 - size_J + i], Q_r[i]);
            }
            
            // 计算姿态雅可比矩阵
            if (J_q) {
                // 计算插值姿态
                q_itps[0] = cps[0];
                q_itps[1] = q_itps[0] * q_delta_scale[0];
                q_itps[2] = q_itps[1] * q_delta_scale[1];
                q_itps[3] = q_itps[2] * q_delta_scale[2];
                *q_out = q_itps[3];
                
                // 计算左乘矩阵
                Eigen::Matrix4d Q_l_all[3];
                Quater::Qleft(q_itps[0], Q_l_all[0]);
                Quater::Qleft(q_itps[1], Q_l_all[1]);
                Quater::Qleft(q_itps[2], Q_l_all[2]);
                
                // 计算姿态雅可比矩阵
                for (int i = 2; i >= 0; i--) {
                    Eigen::Matrix4d Q_r_all;
                    Quater::Qright(q_r_all[i+1], Q_r_all);
                    d_X_d_dj[i].noalias() = coeff[i + 1] * Q_r_all * Q_l_all[i] * dexp_dt[i] * dlog_dq[i];
                }
                
                // 设置雅可比矩阵
                J_q->d_val_d_knot.resize(size_J);
                for (int i = 0; i < size_J; i++) {
                    J_q->d_val_d_knot[i].setZero();
                }
                
                // 计算雅可比矩阵
                for (int i = 0; i < size_J - 1; i++) {
                    J_q->d_val_d_knot[i].noalias() -= d_X_d_dj[4 - size_J + i] * Q_r[i].rightCols(3);
                    J_q->d_val_d_knot[i + 1].noalias() += d_X_d_dj[4 - size_J + i] * Q_l[i].rightCols(3);
                }
                
                // 设置姿态雅可比矩阵的起始索引
                J_q->start_idx = idx0;
                // 根据雅可比矩阵大小选择不同的计算方式
                if (size_J == 4) {
                    // 当雅可比矩阵大小为4时，计算完整的右乘和左乘矩阵
                    Eigen::Matrix4d Q_r_all;
                    Eigen::Matrix4d Q0_left;
                    // 计算右乘矩阵
                    Quater::Qright(q_r_all[0], Q_r_all);
                    // 计算左乘矩阵
                    Quater::Qleft(cps[0], Q0_left);
                    // 更新第一个控制点的雅可比矩阵
                    J_q->d_val_d_knot[0].noalias() += Q_r_all * Q0_left.rightCols(3);
                } else {
                    // 当雅可比矩阵大小不为4时，计算简化的左乘矩阵
                    Eigen::Matrix4d Q_left;
                    Quater::Qleft(q_delta[3 - size_J], Q_left);
                    // 更新第一个控制点的雅可比矩阵
                    J_q->d_val_d_knot[0].noalias() += d_X_d_dj[3 - size_J] * Q_left.rightCols(3);
                }
            }
            // 如果角速度雅可比矩阵存在
            if (J_w) {
                // 计算一阶导数系数
                baseCoeffsWithTime<1>(p, u);
                // 计算累积混合矩阵
                dcoeff = inv_dt * cumulative_blending_matrix * p;
                // 初始化角速度插值
                w_itps[0].setZero();
                // 计算各时间点的角速度
                w_itps[1] = 2 * dcoeff[1] * t_delta[0];
                w_itps[2] = q_delta_scale[1].inverse() * w_itps[1] + 2 * dcoeff[2] * t_delta[1];
                w_itps[3] = q_delta_scale[2].inverse() * w_itps[2] + 2 * dcoeff[3] * t_delta[2];
                // 输出最终角速度
                *w_out = w_itps[3];
                // 计算旋转矩阵的导数
                Eigen::Matrix<double, 3, 4> drot_dq[3];
                Quater::drot(w_itps[0], q_delta_scale[0], drot_dq[0]);
                Quater::drot(w_itps[1], q_delta_scale[1], drot_dq[1]);
                Quater::drot(w_itps[2], q_delta_scale[2], drot_dq[2]);
                // 计算角速度雅可比矩阵
                for (int i = 2; i >= 0; i--) {
                    // 计算速度对控制点的导数
                    Eigen::Matrix3d d_vel_d_dj = coeff[i + 1] * drot_dq[i] * dexp_dt[i];
                    d_vel_d_dj.noalias() += 2 * dcoeff[i + 1] * Eigen::Matrix3d::Identity();
                    // 计算旋转对控制点的导数
                    d_r_d_dj[i].noalias() = q_r_all[i+1].inverse().toRotationMatrix() * d_vel_d_dj * dlog_dq[i];
                }
                // 初始化角速度雅可比矩阵
                J_w->d_val_d_knot.resize(size_J);
                for (int i = 0; i < size_J; i++) {
                    J_w->d_val_d_knot[i].setZero();
                }
                // 计算角速度雅可比矩阵
                for (int i = 0; i < size_J - 1; i++) {
                    J_w->d_val_d_knot[i].noalias() -= d_r_d_dj[4 - size_J + i] * Q_r[i].rightCols(3);
                    J_w->d_val_d_knot[i + 1].noalias() += d_r_d_dj[4 - size_J + i] * Q_l[i].rightCols(3);
                }
                // 设置角速度雅可比矩阵的起始索引
                J_w->start_idx = idx0;
                // 当雅可比矩阵大小不为4时，更新第一个控制点的雅可比矩阵
                if (size_J != 4) {
                    Eigen::Matrix4d Q_left;
                    Quater::Qleft(q_delta[4 - size_J - 1], Q_left);
                    J_w->d_val_d_knot[0].noalias() += d_r_d_dj[3 - size_J] *  Q_left.rightCols(3);
                }
            }
        } else {
            // 计算四元数对数
            Quater::log(q_delta[0], t_delta[0]);
            Quater::log(q_delta[1], t_delta[1]);
            Quater::log(q_delta[2], t_delta[2]);
            // 计算缩放后的四元数对数
            t_delta_scale[0] = t_delta[0] * coeff[1];
            t_delta_scale[1] = t_delta[1] * coeff[2];
            t_delta_scale[2] = t_delta[2] * coeff[3];
            // 计算缩放后的四元数
            Quater::exp(t_delta_scale[0], q_delta_scale[0]);
            Quater::exp(t_delta_scale[1], q_delta_scale[1]);
            Quater::exp(t_delta_scale[2], q_delta_scale[2]);
            // 如果输出四元数存在
            if (q_out) {
                // 计算插值四元数
                q_itps[0] = cps[0];
                q_itps[1] = q_itps[0] * q_delta_scale[0];
                q_itps[2] = q_itps[1] * q_delta_scale[1];
                q_itps[3] = q_itps[2] * q_delta_scale[2];
                // 归一化四元数
                q_itps[3].normalize();
                // 输出最终四元数
                *q_out = q_itps[3];
            }
            // 如果输出角速度存在
            if (w_out) {
                // 计算一阶导数系数
                baseCoeffsWithTime<1>(p, u);
                dcoeff = inv_dt * cumulative_blending_matrix * p;

                // 初始化角速度插值
                w_itps[0].setZero();
                // 计算各时间点的角速度
                w_itps[1] = 2 * dcoeff[1] * t_delta[0];
                w_itps[2] = q_delta_scale[1].inverse() * w_itps[1] + 2 * dcoeff[2] * t_delta[1];
                w_itps[3] = q_delta_scale[2].inverse() * w_itps[2] + 2 * dcoeff[3] * t_delta[2];
                // 输出最终角速度
                *w_out = w_itps[3];
            }
        }
    }

    // 将样条状态转换为消息格式
    void getSplineMsg(sfuise_msgs::msg::Spline& spline_msg)
    {
        // 设置样条消息的基本参数
        spline_msg.dt = dt_ns;
        spline_msg.start_t = start_t_ns;
        spline_msg.start_idx = start_i;
        // 遍历所有控制点
        for (size_t i = 0; i < num_knot; i++) {
            // 创建控制点消息
            sfuise_msgs::msg::Knot knot_msg;
            // 设置位置
            knot_msg.position.x = t_knots[i].x();
            knot_msg.position.y = t_knots[i].y();
            knot_msg.position.z = t_knots[i].z();
            // 设置姿态
            knot_msg.orientation.w = q_knots[i].w();
            knot_msg.orientation.x = q_knots[i].x();
            knot_msg.orientation.y = q_knots[i].y();
            knot_msg.orientation.z = q_knots[i].z();
            // 设置偏差
            Eigen::Matrix<double, 6, 1> bias = b_knots[i];
            knot_msg.bias_acc.x = bias[0];
            knot_msg.bias_acc.y = bias[1];
            knot_msg.bias_acc.z = bias[2];
            knot_msg.bias_gyro.x = bias[3];
            knot_msg.bias_gyro.y = bias[4];
            knot_msg.bias_gyro.z = bias[5];
            // 添加控制点到消息
            spline_msg.knots.push_back(knot_msg);
        }
        // 遍历所有空闲控制点
        for (int i = 0; i < 3; i++) {
            sfuise_msgs::msg::Knot idle_msg;
            idle_msg.position.x = t_idle[i].x();
            idle_msg.position.y = t_idle[i].y();
            idle_msg.position.z = t_idle[i].z();
            idle_msg.orientation.w = q_idle[i].w();
            idle_msg.orientation.x = q_idle[i].x();
            idle_msg.orientation.y = q_idle[i].y();
            idle_msg.orientation.z = q_idle[i].z();
            Eigen::Matrix<double, 6, 1> bias = b_idle[i];
            idle_msg.bias_acc.x = bias[0];
            idle_msg.bias_acc.y = bias[1];
            idle_msg.bias_acc.z = bias[2];
            idle_msg.bias_gyro.x = bias[3];
            idle_msg.bias_gyro.y = bias[4];
            idle_msg.bias_gyro.z = bias[5];
            spline_msg.idles.push_back(idle_msg);
        }
    }  // 结束getSplineMsg函数

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW  // Eigen内存对齐宏

  private:  // 私有成员声明开始

    bool if_first;  // 首次运行标志

    static constexpr double S_TO_NS = 1e9;  // 秒到纳秒的转换系数
    static const Eigen::Matrix4d blending_matrix;  // 混合矩阵
    static const Eigen::Matrix4d base_coefficients;  // 基础系数矩阵
    static const Eigen::Matrix4d cumulative_blending_matrix;  // 累积混合矩阵

    int64_t dt_ns;  // 时间间隔(纳秒)
    double inv_dt;  // 时间间隔的倒数
    std::array<double, 4> pow_inv_dt;  // 时间间隔倒数的幂次数组
    int num_knot;  // 节点数量
    int64_t start_i;  // 起始索引
    int64_t start_t_ns;  // 起始时间(纳秒)

    std::array<Eigen::Quaterniond, 3> q_idle;  // 空闲姿态四元数数组
    std::array<Eigen::Vector3d, 3> t_idle;  // 空闲位置向量数组
    std::array<Eigen::Matrix<double, 6, 1>, 3> b_idle;  // 空闲偏差向量数组
    Eigen::aligned_deque<Eigen::Quaterniond> q_knots;  // 姿态四元数队列
    Eigen::aligned_deque<Eigen::Vector3d> t_knots;  // 位置向量队列
    Eigen::aligned_deque<Eigen::Matrix<double, 6, 1>> b_knots;  // 偏差向量队列

    // 欧几里得空间插值模板函数
    template <typename _KnotT, int Derivative = 0>
    _KnotT itpEuclidean(int64_t t_ns, const std::array<_KnotT, 3>& knots_idle,
                        const Eigen::aligned_deque<_KnotT>& knots, Jacobian* J = nullptr) const
    {
        double u;  // 归一化时间
        int64_t idx0;  // 起始索引
        int idx_r;  // 右边界索引
        std::array<_KnotT,4> cps;  // 控制点数组
        prepareInterpolation(t_ns, knots_idle, knots, idx0, u, cps, idx_r);  // 准备插值
        Eigen::Vector4d p, coeff;  // 基函数系数和最终系数
        baseCoeffsWithTime<Derivative>(p, u);  // 计算基函数系数
        coeff = pow_inv_dt[Derivative] * (blending_matrix * p);  // 计算最终系数
        _KnotT res_out = coeff[0] * cps[0] + coeff[1] * cps[1] + coeff[2] * cps[2] + coeff[3] * cps[3];  // 计算插值结果
        if (J) {  // 如果需要计算雅可比矩阵
            int size_J = std::min(idx_r + 1, 4);  // 确定雅可比矩阵大小
            J->d_val_d_knot.resize(size_J);  // 调整雅可比矩阵大小
            for (int i = 0; i < size_J; i++) {
                J->d_val_d_knot[i] = coeff[4 - size_J + i];  // 填充雅可比矩阵
            }
            J->start_idx = idx0;  // 设置起始索引
        }
        return res_out;  // 返回插值结果
    }

    // 准备插值数据模板函数
    template<typename _KnotT>
    void prepareInterpolation(int64_t t_ns, const std::array<_KnotT, 3>& knots_idle,
                              const Eigen::aligned_deque<_KnotT>& knots, int64_t& idx0, double& u,
                              std::array<_KnotT,4>& cps, int& idx_r) const
    {
        int64_t t_ns_rel = t_ns - start_t_ns;  // 计算相对时间
        int idx_l = floor(double(t_ns_rel) / double(dt_ns));  // 计算左边界索引
        idx_r = idx_l + 1;  // 计算右边界索引
        idx0 = std::max(idx_l - 2, 0);  // 计算起始索引
        for (int i = 0; i < 2 - idx_l; i++) {  // 填充空闲控制点
            cps[i] = knots_idle[i + idx_l + 1];
        }
        int idx_window = std::max(0, 2 - idx_l);  // 计算窗口索引
        for (int i = 0; i < std::min(idx_l + 2, 4); i++) {  // 填充实际控制点
            cps[i + idx_window] = knots[idx0 + i];
        }
        u = (t_ns - start_t_ns - idx_l * dt_ns) / double(dt_ns);  // 计算归一化时间
    }

    // 计算基函数系数模板函数
    template <int Derivative, class Derived>
    static void baseCoeffsWithTime(const Eigen::MatrixBase<Derived>& res_const, double t)
    {
        EIGEN_STATIC_ASSERT_VECTOR_SPECIFIC_SIZE(Derived, 4);  // 确保向量大小为4
        Eigen::MatrixBase<Derived>& res = const_cast<Eigen::MatrixBase<Derived>&>(res_const);
        res.setZero();  // 清零结果向量
        res[Derivative] = base_coefficients(Derivative, Derivative);  // 设置初始值
        double ti = t;  // 初始化时间幂次
        for (int j = Derivative + 1; j < 4; j++) {  // 计算其他系数
            res[j] = base_coefficients(Derivative, j) * ti;
            ti = ti * t;
        }
    }

    // 计算混合矩阵模板函数
    template <bool _Cumulative = false>
    static Eigen::Matrix4d computeBlendingMatrix()
    {
        Eigen::Matrix4d m;  // 创建4x4矩阵
        m.setZero();  // 清零矩阵
        for (int i = 0; i < 4; ++i) {  // 计算矩阵元素
            for (int j = 0; j < 4; ++j) {
                double sum = 0;
                for (int s = j; s < 4; ++s) {
                    sum += std::pow(-1.0, s - j) * binomialCoefficient(4, s - j) *
                    std::pow(4 - s - 1.0, 4 - 1.0 - i);
                }
                m(j, i) = binomialCoefficient(3, 3 - i) * sum;
            }
        }
        if (_Cumulative) {  // 如果需要累积
            for (int i = 0; i < 4; i++) {
                for (int j = i + 1; j < 4; j++) {
                    m.row(i) += m.row(j);  // 累积行
                }
            }
        }
        uint64_t factorial = 1;  // 计算阶乘
        for (int i = 2; i < 4; ++i) {
            factorial *= i;
        }
        return m / factorial;  // 返回归一化后的矩阵
    }

    // 计算二项式系数函数
    constexpr static inline uint64_t binomialCoefficient(uint64_t n, uint64_t k)
    {
        if (k > n) return 0;  // 如果k大于n返回0
        uint64_t r = 1;  // 初始化结果
        for (uint64_t d = 1; d <= k; ++d) {  // 计算二项式系数
            r *= n--;
            r /= d;
        }
        return r;  // 返回结果
    }

    // 计算基础系数矩阵函数
    static Eigen::Matrix4d computeBaseCoefficients()
    {
        Eigen::Matrix4d base_coeff;  // 创建4x4矩阵
        base_coeff.setZero();  // 清零矩阵
        base_coeff.row(0).setOnes();  // 第一行设为1
        int order = 3;  // 初始化阶数
        
        // 计算基础系数矩阵的每一行
        for (int n = 1; n < 4; n++) {  // 遍历每一行
            for (int i = 3 - order; i < 4; i++) {  // 遍历每一列
                // 计算当前元素值: (order - 3 + i) * 上一行对应位置的值
                base_coeff(n, i) = (order - 3 + i) * base_coeff(n - 1, i);
            }
            order--;  // 阶数递减
        }
        return base_coeff;  // 返回计算好的基础系数矩阵
    }
};

// 定义静态成员变量
const Eigen::Matrix4d SplineState::base_coefficients = SplineState::computeBaseCoefficients();  // 基础系数矩阵
const Eigen::Matrix4d SplineState::blending_matrix = SplineState::computeBlendingMatrix();  // 混合矩阵
const Eigen::Matrix4d SplineState::cumulative_blending_matrix = SplineState::computeBlendingMatrix<true>();  // 累积混合矩阵
