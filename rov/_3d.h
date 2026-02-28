#ifndef _3D_H
#define _3D_H

#include <QQuickWidget>
#include <QQuickItem>
#include <QTimer>
#include <Qt3DWindow>
#include <widget.h>
#include <tcpserver.h>
#include <global.h>


class _3D:public Widget
{
public:
    _3D(Widget *parent = nullptr,tcpserver *tcp=nullptr);

signals:
    qreal change(qreal v);
    void c();

private:
    QPointer<Qt3DExtras::Qt3DWindow> m_windowOn3D;
    Widget *p;
    tcpserver *t;
};

#endif // _3D_H
