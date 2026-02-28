#ifndef LOCALIZATIONMAP_H
#define LOCALIZATIONMAP_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QTimer>
#include <QList>
#include <QLabel>  // <-- 新增
#include<mapview.h>
#include<global.h>
#include<RovKalmanFilter.h>
#include<opencv2/objdetect.hpp>

using namespace cv;

namespace Ui {
class LocalizationMap;
}

class LocalizationMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit LocalizationMap(QWidget *parent = nullptr);
    ~LocalizationMap();
private slots:
    void simulateRovData();
public slots:
    void showDistance();
private:
    void setupScene();
    void applyStyles();
    QPointF calculateRovPosition(double distA, double distB, double depth, bool& ok);
    void updateDisplay(double distA, double distB, double depth, double heading, const QPointF& position);
    QGraphicsScene *m_scene;
    // 计算原始位置的函数，现在设为私有
    QPointF calculateRawPosition(double distA, double distB, double depth, bool& ok);
    // 返回经过卡尔曼滤波后的平滑位置
    QPointF updateRovPosition(double distA, double distB, double depth, double current_timestamp);
    // 图形元素
    QGraphicsPixmapItem *m_buoyA_item;
    QGraphicsPixmapItem *m_buoyB_item;
    QGraphicsPixmapItem *m_rov_item;
    QGraphicsPathItem *m_historyPath;
    QList<QPointF> m_rovHistory;

    // 系统参数
    // 新增：ROV上声呐B相对于声呐A的局部坐标（单位：米）
    double m_sonar_dx; // = 0.260;
    double m_sonar_dy; // = 0.212;
    double m_d_sonars_sq; // 声呐间距离的平方，用于优化计算
    const double m_scale_factor = 25;    // 视觉缩放因子 (米 -> 像素)

    // 数据模拟器
    QTimer *m_simulationTimer;
    // 新增：数据滤波相关
    const int m_filter_window_size = 5; // 滤波器窗口大小，取最近5个数据
    QList<double> m_distA_history;
    QList<double> m_distB_history;
    QList<double> m_depth_history;

    // 新增：用于在UI上显示状态的标签
    QLabel *m_statusLabel;

    // 新增：不确定性可视化
    QGraphicsEllipseItem *m_uncertainty_circle;

    // 新增：滤波器函数
    double applyFilter(QList<double>& history, double newValue);
    // 卡尔曼滤波器实例
    Ptr<RovKalmanFilter> m_kalman_filter;
    bool is_raw_pos_valid = false;
    // 上一次更新的时间戳，用于计算dt
    double m_last_timestamp;

    Ui::LocalizationMap *ui;
};

#endif // LOCALIZATIONMAP_H
