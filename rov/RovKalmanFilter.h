#ifndef ROVKALMANFILTER_H
#define ROVKALMANFILTER_H

#include <QObject>
#include <Eigen/Dense>

class RovKalmanFilter : public QObject{
    Q_OBJECT

public:
    // 构造函数: 初始化滤波器参数
    RovKalmanFilter();

    // 初始化滤波器的状态
    void init(const Eigen::Vector2d& initial_position);

    // 预测步骤: 根据上一时刻的状态和时间差dt，预测当前状态
    void predict(double dt);

    // 更新步骤: 使用新的测量值来校正预测的状态
    void update(const Eigen::Vector2d& measurement);

    // 获取当前的状态向量 [px, py, vx, vy]
    Eigen::Vector4d getState() const;

    // 获取当前的位置估计 [px, py]
    Eigen::Vector2d getPosition() const;

    // 获取当前的速度估计 [vx, vy]
    Eigen::Vector2d getVelocity() const;

    // 检查滤波器是否已初始化
    bool isInitialized() const;

private:
    // --- 卡尔曼滤波器核心矩阵 ---

    // 状态向量 [px, py, vx, vy]
    Eigen::Vector4d x_hat_;

    // 状态协方差矩阵 P: 表示状态估计的不确定性
    Eigen::Matrix4d P_;

    // 状态转移矩阵 F: 描述状态如何从k-1演变到k
    Eigen::Matrix4d F_;

    // 过程噪声协方差矩阵 Q: 表示模型本身的不确定性 (e.g., 水流影响)
    Eigen::Matrix4d Q_;

    // 测量矩阵 H: 将状态向量映射到测量空间
    Eigen::Matrix<double, 2, 4> H_;

    // 测量噪声协方差矩阵 R: 表示测量值的不确定性 (来自声学定位的噪声)
    Eigen::Matrix2d R_;

    // --- 状态 ---
    bool is_initialized_;
};


#endif // ROVKALMANFILTER_H
