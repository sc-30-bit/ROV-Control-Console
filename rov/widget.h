#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<opencv2/opencv.hpp>
#include<QPixmap>
#include<quiwidget.h>
#include<QTcpServer>
#include<QTcpSocket>
#include<tcpserver.h>
#include<QThread>
#include<QTimer>
#include<rtsp.h>
#include<global.h>
#include<saver.h>
#include<stitcher.h>
#include<localizationmap.h>


using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void receiveLogin();
    void showframes(QPixmap frame1,QPixmap frame2,QPixmap frame3);
    void showshtc3();
    void showms5837();
    void showjys901();
    void showthruster();
    void showyuntai();
    void showmsg(QString msg);
private slots:
    void showwarning();
    void showinfo(QString ip,QString port);
signals:
    void form_pidarray(const float* pidparameter);
    void sendPicture(QPixmap map,int cameraIndex);
    void sendVideo(QPixmap videoFrame,int cameraIndex);
    void timerStopped(int cameraIndex);
public:
    Ui::Widget *ui;
    Ptr<tcpserver> server1;
    Ptr<LocalizationMap> localization;
private:
    //Ui::Widget *ui;
    Ptr<rtsp> Rtsp;
    Ptr<QThread> rtspThread;
    Ptr<QThread> tcpthread;
    Ptr<saver> Saver;
    Ptr<QThread> SaverThread;
    Ptr<QThread> stitchThread;
    Ptr<stitcher> Stitcher;
    Ptr<QTimer> timer1;
    Ptr<QTimer> timer2;
    Ptr<QTimer> timer3;
};
#endif // WIDGET_H
