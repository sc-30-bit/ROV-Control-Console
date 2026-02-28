#include "mapview.h"
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QLinearGradient>
#include <QApplication> // <-- 新增：为了获取拖拽距离阈值
#include<QStyle>

MapView::MapView(QWidget *parent) : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag); // 保持NoDrag，我们自己实现拖动
    setTransformationAnchor(AnchorUnderMouse);
    setCursor(Qt::ArrowCursor); // 初始光标为箭头
}

void MapView::drawBackground(QPainter *painter, const QRectF &rect)
{
    // ... 这部分代码保持不变 ...
    // 1. 绘制深蓝色渐变背景
    QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());
    gradient.setColorAt(0, QColor(26, 32, 53));
    gradient.setColorAt(1, QColor(15, 18, 30));
    painter->fillRect(rect, gradient);

    // 2. 绘制网格
    const int gridSize = 50;
    QPen gridPen(QColor(74, 85, 125, 80));
    gridPen.setWidth(1);
    painter->setPen(gridPen);

    qreal left = int(rect.left() / gridSize) * gridSize;
    qreal top = int(rect.top() / gridSize) * gridSize;
    for (qreal x = left; x < rect.right(); x += gridSize) {
        painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
    }
    for (qreal y = top; y < rect.bottom(); y += gridSize) {
        painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
    }

    // 3. 绘制距离圈 (以(0,0)为中心)
    QPen ringPen(QColor(0, 255, 255, 100)); // 青色
    ringPen.setStyle(Qt::DashLine);
    painter->setPen(ringPen);
    QFont textFont = painter->font();
    textFont.setPointSize(8);
    painter->setFont(textFont);

    // 真实世界距离 - 每2米一个圈
    const int ringDistance = 2;
    for (int r = ringDistance; r < 100; r += ringDistance) {
        double radius = r * m_scale_factor; // 转换为屏幕像素
        painter->drawEllipse(QPointF(0, 0), radius, radius);
        painter->drawText(QRectF(5, -radius - 12, 50, 12), Qt::AlignLeft, QString("%1m").arg(r));
    }
}

void MapView::wheelEvent(QWheelEvent *event)
{
    // ... 这部分代码保持不变 ...
    if (event->angleDelta().y() > 0) {
        scale(1.1, 1.1);
    } else {
        scale(1.0 / 1.1, 1.0 / 1.1);
    }
}


// =======================================================================
// |                      👇 这里是核心修改 👇                           |
// =======================================================================

void MapView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_lastPanPoint = event->pos();
        m_isPanning = false; // 按下时，先假设不是拖动
        event->accept();
        return;
    }
    // 其他鼠标按键，交给基类处理
    QGraphicsView::mousePressEvent(event);
}

void MapView::mouseMoveEvent(QMouseEvent *event)
{
    // 检查左键是否被按下 (通过 buttons() 方法)
    if ((event->buttons() & Qt::LeftButton) && !m_lastPanPoint.isNull()) {
        if (!m_isPanning) {
            // 计算鼠标移动的距离
            QPointF delta = event->pos() - m_lastPanPoint;
            // 如果移动距离超过一个阈值，我们才认为是拖动
            // QStyle::PM_StartDragDistance 是一个系统推荐的拖动起始距离
            if (delta.manhattanLength() > QApplication::style()->pixelMetric(QStyle::PM_MaximumDragDistance)) {
                m_isPanning = true;
                setCursor(Qt::ClosedHandCursor);
            }
        }

        if (m_isPanning) {
            // 正在拖动，执行平移逻辑
            QPointF delta = mapToScene(m_lastPanPoint) - mapToScene(event->pos());
            m_lastPanPoint = event->pos();
            setSceneRect(sceneRect().translated(delta.x(), delta.y()));
        }
        event->accept();
        return;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MapView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ArrowCursor); // 恢复光标

        // 如果不是拖动状态，说明这是一个点击事件
        if (!m_isPanning) {
            // 将事件传递给基类，以处理正常的点击、选择等操作
            // 我们需要模拟一次完整的点击事件
            QGraphicsView::mousePressEvent(event);
            QGraphicsView::mouseReleaseEvent(event);
        }

        // 重置状态
        m_lastPanPoint = QPoint();
        m_isPanning = false;
        event->accept();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
}
