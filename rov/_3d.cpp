#include "_3d.h"
#include "ui_widget.h"

_3D::_3D(Widget *parent,tcpserver *tcp)
{
    /*p=parent;
    m_windowOn3D = new Qt3DExtras::Qt3DWindow();

    p->ui->quickWidget->setResizeMode(QQuickWidget::SizeViewToRootObject);
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    p->ui->quickWidget->setFormat(format);
    p->ui->quickWidget->setSource(QUrl::fromLocalFile("/home/stephen/QtProject/rov/_3D.qml"));

    QQuickItem *item=p->ui->quickWidget->rootObject();*/
    p=parent;
    t=tcp;
    m_windowOn3D = new Qt3DExtras::Qt3DWindow();

    p->ui->quickWidget->setResizeMode(QQuickWidget::SizeViewToRootObject);
    p->ui->quickWidget->setSource(QUrl::fromLocalFile("/home/stephen/QtProject/3d/_3D.qml"));

    QQuickItem *item=p->ui->quickWidget->rootObject();

    connect(t,&tcpserver::send_jy901s,item,[=]()
            {
                int roll = rpy_jiao_du[0];
                if(roll>180)roll-=360;
                if(roll<-180)roll+=360;
                item->setProperty("v1",roll);
                item->update();
            });
    connect(t,&tcpserver::send_jy901s,item,[=]()
            {
                int pitch = rpy_jiao_du[1];
                if(pitch>180)pitch-=360;
                if(pitch<-180)pitch+=360;
                item->setProperty("v2",pitch);
                item->update();

            });
    connect(t,&tcpserver::send_jy901s,item,[=]()
            {
                int yaw = rpy_jiao_du[2];
                if(yaw>360)yaw-=360;
                if(yaw<0)yaw+=360;
                item->setProperty("v3",yaw);
                item->update();
            });
}
