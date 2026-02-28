#include "RovKalmanFilter.h"
#include <iostream>

RovKalmanFilter::RovKalmanFilter() : is_initialized_(false) {
    // 状态向量维度为4 ([px, py, vx, vy])
    x_hat_ = Eigen::Vector4d::Zero();

    // 1. 初始化状态协方差矩阵 P
    // 开始时，我们对状态非常不确定，所以给予一个较大的协方差
    // 位置不确定性大，速度不确定性更大
    P_ = Eigen::Matrix4d::Identity();
    P_(0, 0) = P_(1, 1) = 500; // 位置不确定性 (m^2)
    P_(2, 2) = P_(3, 3) = 500; // 速度不确定性 (m^2/s^2)

    // 2. 初始化测量矩阵 H
    // 我们只能测量到位置 (px, py)，不能直接测量速度
    H_ = Eigen::Matrix<double, 2, 4>::Zero();
    H_(0, 0) = 1; // 测量.x() 对应于状态 px
    H_(1, 1) = 1; // 测量.y() 对应于状态 py

    // 3. 初始化测量噪声协方差矩阵 R
    // **这是一个关键的调整参数**
    // 它代表了你的声学定位解算结果的噪声水平。
    // 假设x和y方向的测量标准差为0.1米 (10cm)
    double measurement_noise = 0.1;
    R_ = Eigen::Matrix2d::Identity() * (measurement_noise * measurement_noise);

    // F_ 和 Q_ 依赖于时间差dt，将在predict()中更新
}

void RovKalmanFilter::init(const Eigen::Vector2d& initial_position) {
    // 使用第一个有效的测量值来初始化状态
    x_hat_ << initial_position.x(), initial_position.y(), 0, 0;
    is_initialized_ = true;
    std::cout << "Kalman Filter Initialized at: (" << x_hat_(0) << ", " << x_hat_(1) << ")" << std::endl;
}

void RovKalmanFilter::predict(double dt) {
    if (dt <= 0) {
        // 时间间隔无效，不进行预测
        return;
    }

    // 1. 更新状态转移矩阵 F (基于恒定速度模型)
    // px_k = px_{k-1} + vx_{k-1} * dt
    // py_k = py_{k-1} + vy_{k-1} * dt
    // vx_k = vx_{k-1}
    // vy_k = vy_{k-1}
    F_ = Eigen::Matrix4d::Identity();
    F_(0, 2) = dt;
    F_(1, 3) = dt;

    // 2. 更新过程噪声协方差矩阵 Q
    // **这是另一个关键的调整参数**
    // 它代表了ROV运动模型的不确定性（如未建模的加速度、水流等）。
    // process_noise_magnitude 越大，说明你认为ROV的运动越不平滑，滤波器会更多地依赖测量值。
    double process_noise_magnitude = 0.5;
    double dt2 = dt * dt;
    double dt3 = dt2 * dt;
    double dt4 = dt3 * dt;

    Q_ = Eigen::Matrix4d::Zero();
    Q_(0,0) = dt4/4.0; Q_(0,2) = dt3/2.0;
    Q_(1,1) = dt4/4.0; Q_(1,3) = dt3/2.0;
    Q_(2,0) = dt3/2.0; Q_(2,2) = dt2;
    Q_(3,1) = dt3/2.0; Q_(3,3) = dt2;
    Q_ *= process_noise_magnitude;

    // 3. 执行预测
    x_hat_ = F_ * x_hat_;
    P_ = F_ * P_ * F_.transpose() + Q_;
}

void RovKalmanFilter::update(const Eigen::Vector2d& measurement) {
    // 1. 计算创新（Innovation）
    Eigen::Vector2d y = measurement - (H_ * x_hat_);

    // 2. 计算创新协方差（Innovation Covariance）
    Eigen::Matrix2d S = H_ * P_ * H_.transpose() + R_;

    // 3. 计算卡尔曼增益（Kalman Gain）
    Eigen::Matrix<double, 4, 2> K = P_ * H_.transpose() * S.inverse();

    // 4. 更新状态估计
    x_hat_ = x_hat_ + (K * y);

    // 5. 更新状态协方差
    Eigen::Matrix4d I = Eigen::Matrix4d::Identity();
    P_ = (I - K * H_) * P_;
}

Eigen::Vector4d RovKalmanFilter::getState() const { return x_hat_; }
Eigen::Vector2d RovKalmanFilter::getPosition() const { return x_hat_.head<2>(); }
Eigen::Vector2d RovKalmanFilter::getVelocity() const { return x_hat_.tail<2>(); }
bool RovKalmanFilter::isInitialized() const { return is_initialized_; }
