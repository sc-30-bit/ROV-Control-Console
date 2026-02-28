// mapview.h
#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>

class MapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = nullptr);
    void setScaleFactor(double factor) { m_scale_factor = factor; }


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;

    // 事件处理函数
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    double m_scale_factor = 2.5; // 1米 = 2.5像素

    QPoint m_lastPanPoint;
    bool m_isPanning = false; // <-- 新增：用于标记是否正在拖动
};

#endif // MAPVIEW_H
