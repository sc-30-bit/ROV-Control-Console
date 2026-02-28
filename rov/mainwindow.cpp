#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapview.h" // 确保包含了自定义视图的头文件
#include <cmath>
#include <QDebug>
#include <QPainterPath>
#include <QStatusBar> // <-- 新增
#include <QGraphicsEllipseItem> // <-- 新增
#include <numeric> // <-- 新增 std::accumulate

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("专业ROV声学定位系统");
    // 新增：在状态栏添加一个永久的标签用于显示定位状态
    m_statusLabel = new QLabel("状态: 初始化...");
    m_statusLabel->setStyleSheet("padding-left: 10px; color: #f0f0f0;");
    statusBar()->addPermanentWidget(m_statusLabel);

    applyStyles();
    setupScene();

    // 新增：创建不确定性圆圈
    m_uncertainty_circle = new QGraphicsEllipseItem();
    m_uncertainty_circle->setPen(QPen(QColor(0, 255, 255, 70))); // 青色，半透明
    m_uncertainty_circle->setBrush(QBrush(QColor(0, 255, 255, 40)));
    m_uncertainty_circle->setZValue(0); // 确保在ROV图标下面
    m_scene->addItem(m_uncertainty_circle);

    m_simulationTimer = new QTimer(this);
    connect(m_simulationTimer, &QTimer::timeout, this, &MainWindow::simulateRovData);
    m_simulationTimer->start(200); // 10Hz 更新率
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::applyFilter(QList<double>& history, double newValue)
{
    history.append(newValue);
    if (history.size() > m_filter_window_size) {
        history.removeFirst();
    }

    // 计算队列中所有元素的总和
    double sum = std::accumulate(history.begin(), history.end(), 0.0);

    // 返回平均值
    return sum / history.size();
}

void MainWindow::applyStyles()
{
    this->setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #1a2035;
            color: #e0e0e0;
            font-family: "Microsoft YaHei", "Segoe UI", Arial, sans-serif;
        }
        QFrame {
            background-color: #2c354d;
            border: 1px solid #4a557d;
            border-radius: 5px;
        }
        QLabel {
            background-color: transparent;
            border: none;
            font-size: 14px;
            padding: 4px;
        }
        QLabel#label_base_dist, QLabel#label_pos_x, QLabel#label_pos_y, QLabel#label_pos_z {
            font-weight: bold;
            color: #4dd0e1; /* Cyan */
        }
    )");
}

void MainWindow::setupScene()
{
    m_scene = new QGraphicsScene(this);
    ui->mapView->setScene(m_scene);
    ui->mapView->setScaleFactor(m_scale_factor); // 告诉视图缩放因子，用于绘制距离圈

    // 加载图标
    QPixmap buoyPixmap("/home/stephen/QtProject/Localization2DVisualization/icon_浮漂-IV.png");
    QPixmap rovPixmap("/home/stephen/QtProject/Localization2DVisualization/用户.png");

    // 创建浮漂A和B
    m_buoyA_item = m_scene->addPixmap(buoyPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_buoyA_item->setPos(QPointF(0, 0) - QPointF(16, 16)); // 偏移以使其中心在(0,0)

    m_buoyB_item = m_scene->addPixmap(buoyPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPointF buoyB_pos(m_base_distance * m_scale_factor, 0);
    m_buoyB_item->setPos(buoyB_pos - QPointF(16, 16)); // 偏移以使其中心在目标位置

    // 创建历史轨迹路径
    m_historyPath = m_scene->addPath(QPainterPath(), QPen(QColor(255, 100, 100, 150), 2));

    // 创建ROV图标
    m_rov_item = m_scene->addPixmap(rovPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_rov_item->setTransformOriginPoint(20, 20); // 设置旋转中心为图片中心
    m_rov_item->setZValue(1); // 确保ROV在轨迹之上

    // 初始化UI标签
    ui->label_base_dist->setText(QString("基线距离: %1 m").arg(m_base_distance));
}

QPointF MainWindow::calculateRovPosition(double distA, double distB, double depth, bool& ok)
{
    // ... 这部分代码与第一个回答完全相同，无需修改 ...
    ok = false;
    if (depth >= distA || depth >= distB) {
        qWarning() << "Error: Depth is greater or equal to slant range.";
        return QPointF();
    }
    double rA = std::sqrt(distA * distA - depth * depth);
    double rB = std::sqrt(distB * distB - depth * depth);
    if (rA + rB < m_base_distance || std::abs(rA - rB) > m_base_distance) {
        qWarning() << "Error: Distances do not form a valid triangle.";
        return QPointF();
    }
    double x = (rA*rA - rB*rB + m_base_distance*m_base_distance) / (2 * m_base_distance);
    if (x * x > rA * rA) {
        qWarning() << "Error: Calculation resulted in no real solution for y.";
        return QPointF();
    }
    double y = std::sqrt(rA*rA - x*x);
    ok = true;
    return QPointF(x, y);
}

void MainWindow::updateDisplay(double distA, double distB, double depth, double heading, const QPointF& position)
{
    // 更新文本标签
    ui->label_dist_a->setText(QString("Dist A: %1 m").arg(distA, 0, 'f', 2));
    ui->label_dist_b->setText(QString("Dist B: %1 m").arg(distB, 0, 'f', 2));
    ui->label_depth->setText(QString("Depth: %1 m").arg(depth, 0, 'f', 2));
    ui->label_pos_x->setText(QString("X: %1 m").arg(position.x(), 0, 'f', 2));
    ui->label_pos_y->setText(QString("Y: %1 m").arg(position.y(), 0, 'f', 2));
    ui->label_pos_z->setText(QString("Z: %1 m").arg(-depth, 0, 'f', 2));
    ui->label_heading->setText(QString("航向: %1°").arg(heading, 0, 'f', 1));

    // 恢复图标透明度
    m_rov_item->setOpacity(1.0);

    // 更新地图上的ROV位置和朝向
    QPointF scaledPos = position * m_scale_factor;
    m_rov_item->setPos(scaledPos - m_rov_item->boundingRect().center());
    m_rov_item->setRotation(heading);

    // =======================================================================
    // |                👇 核心修改：更新不确定性圆圈 👇                        |
    // =======================================================================

    // 1. 计算距离数据的标准差来估算不确定性
    double meanA = std::accumulate(m_distA_history.begin(), m_distA_history.end(), 0.0) / m_distA_history.size();
    double stddevA = 0;
    for(double val : m_distA_history) { stddevA += (val - meanA) * (val - meanA); }
    stddevA = std::sqrt(stddevA / m_distA_history.size());

    double meanB = std::accumulate(m_distB_history.begin(), m_distB_history.end(), 0.0) / m_distB_history.size();
    double stddevB = 0;
    for(double val : m_distB_history) { stddevB += (val - meanB) * (val - meanB); }
    stddevB = std::sqrt(stddevB / m_distB_history.size());

    // 2. 将不确定性（标准差）映射为圆圈的半径
    // (stddevA + stddevB) 是一个综合不确定性的指标
    // 乘以一个系数（如 10.0）来调整视觉效果
    double uncertainty_radius = (stddevA + stddevB) * 5.0 * m_scale_factor;

    // 限制最大和最小半径，避免过大或过小
    uncertainty_radius = std::max(5.0, std::min(uncertainty_radius, 50.0));

    // 3. 更新圆圈的位置和大小
    m_uncertainty_circle->setRect(
        scaledPos.x() - uncertainty_radius,
        scaledPos.y() - uncertainty_radius,
        uncertainty_radius * 2,
        uncertainty_radius * 2
        );
    m_uncertainty_circle->show();

    // 更新历史轨迹
    if (m_rovHistory.isEmpty()) {
        QPainterPath path(scaledPos);
        m_historyPath->setPath(path);
    } else {
        QPainterPath path = m_historyPath->path();
        path.lineTo(scaledPos);
        m_historyPath->setPath(path);
    }
    m_rovHistory.append(scaledPos);

    // 限制轨迹长度
    const int maxHistory = 200;
    while (m_rovHistory.size() > maxHistory) {
        m_rovHistory.removeFirst();
    }
    if(m_rovHistory.size() > 1 && m_historyPath->path().elementCount() > maxHistory) {
        QPainterPath efficientPath(m_rovHistory.first());
        for(int i=1; i<m_rovHistory.size(); ++i) {
            efficientPath.lineTo(m_rovHistory[i]);
        }
        m_historyPath->setPath(efficientPath);
    }
}

void MainWindow::simulateRovData()
{
    // 模拟ROV在一个椭圆路径上移动，同时深度和朝向也在变化
    static double angle = 0;
    static double last_x = 0, last_y = 0;
    angle += 0.03;

    double true_x = m_base_distance / 2 + 5 * std::cos(angle);
    double true_y = 4 + 3 * std::sin(angle);
    double true_depth = 1.5 + 0.5 * std::sin(angle * 2);

    // 模拟航向角 (基于移动方向)
    double heading_rad = std::atan2(true_y - last_y, true_x - last_x);
    double heading_deg = heading_rad * 180.0 / M_PI;
    last_x = true_x;
    last_y = true_y;

    // 根据模拟的真实位置反向计算出传感器应该读到的距离值
    double sim_rA = std::sqrt(true_x * true_x + true_y * true_y);
    double sim_rB = std::sqrt(std::pow(true_x - m_base_distance, 2) + true_y * true_y);

    double sim_distA = std::sqrt(sim_rA * sim_rA + true_depth * true_depth);
    double sim_distB = std::sqrt(sim_rB * sim_rB + true_depth * true_depth);

    // ---- 在真实项目中，您将从这里开始，用从硬件接收到的真实数据替换以上模拟数据 ----
    // 您会得到 sim_distA, sim_distB, true_depth, heading_deg 这四个值

    // =======================================================================
    // |               👇 核心修改：模拟噪声并应用滤波器 👇                     |
    // =======================================================================

    // 1. 模拟噪声。真实世界的数据就是这样的。
    // rand() / (double)RAND_MAX 生成 0-1 的随机数
    // (rand() / (double)RAND_MAX - 0.5) * 2.0 生成 -1.0 到 1.0 的噪声
    double noiseA = (rand() / (double)RAND_MAX - 0.5) * 1.5; // ±0.75m 的噪声
    double noiseB = (rand() / (double)RAND_MAX - 0.5) * 1.5;
    double noiseD = (rand() / (double)RAND_MAX - 0.5) * 0.4; // ±0.2m 的噪声

    // 偶尔模拟一个大的“野点” (outlier)
    if (rand() % 100 < 10) { // 2% 的概率出现野点
        noiseA *= 10.0;
        qDebug() << "!!! Outlier detected in Dist A";
    }

    double noisy_distA = sim_distA + noiseA;
    double noisy_distB = sim_distB + noiseB;
    double noisy_depth = true_depth + noiseD;

    // 2. 应用滤波器
    double filtered_distA = applyFilter(m_distA_history, noisy_distA);
    double filtered_distB = applyFilter(m_distB_history, noisy_distB);
    double filtered_depth = applyFilter(m_depth_history, noisy_depth);


    // 3. 使用【滤波后】的数据进行计算
    bool calculation_ok;
    QPointF calculated_pos = calculateRovPosition(filtered_distA, filtered_distB, filtered_depth, calculation_ok);

    // 4. 根据计算结果更新UI和状态
    if (calculation_ok) {
        // 使用原始噪声数据和滤波后的最终位置来更新显示
        updateDisplay(noisy_distA, noisy_distB, noisy_depth, heading_deg, calculated_pos);
        m_statusLabel->setText("✅ 定位正常 (数据已平滑)");
        m_statusLabel->setStyleSheet("padding-left: 10px; color: #4CAF50;font-size: 24px;"); // 绿色
    } else {
        // 当计算失败时，我们不更新ROV的位置，但要告诉用户
        // 我们可以让ROV图标变灰，或者保持在最后一次成功的位置
        m_statusLabel->setText("❌ 定位失败: 数据无效或无解");
        m_statusLabel->setStyleSheet("padding-left: 10px; color: #F44336;font-size: 24px;"); // 红色

        // 可选：让ROV图标变灰或半透明
        m_rov_item->setOpacity(0.5);
        m_uncertainty_circle->hide();
    }
}
