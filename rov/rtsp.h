#ifndef RTSP_H
#define RTSP_H

#include <QObject>
#include<opencv2/opencv.hpp>
#include<QPixmap>
#include<QDebug>
#include<QThread>
#include<QImage>
#include<atomic>
#include<global.h>

using namespace cv;

//extern std::atomic<bool> stopRTSP=false;//尽量不使用全局变量，用了加static修饰并且必须初始化

class rtsp : public QObject
{
    Q_OBJECT
public:
    rtsp();
public slots:
    void start();
    void close();
signals:
    void sendframes(QPixmap frame1,QPixmap frame2,QPixmap frame3);
private:
    Ptr<VideoCapture> cap,cap2,cap3;

};

#endif // RTSP_H
