#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QTimer>
#include <QList>
#include <QLabel>  // <-- 新增


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void simulateRovData();

private:
    void setupScene();
    void applyStyles();
    QPointF calculateRovPosition(double distA, double distB, double depth, bool& ok);
    void updateDisplay(double distA, double distB, double depth, double heading, const QPointF& position);

    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;

    // 图形元素
    QGraphicsPixmapItem *m_buoyA_item;
    QGraphicsPixmapItem *m_buoyB_item;
    QGraphicsPixmapItem *m_rov_item;
    QGraphicsPathItem *m_historyPath;
    QList<QPointF> m_rovHistory;

    // 系统参数
    const double m_base_distance = 15; // 浮漂基线距离 (米)
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
};
#endif // MAINWINDOW_H
