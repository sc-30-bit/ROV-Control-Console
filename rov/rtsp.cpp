#include "rtsp.h"

rtsp::rtsp(){}

void rtsp::start()
{
    qDebug()<<"Rtsp线程地址："<<QThread::currentThread()<<Qt::endl;
    std::cout<<"Video streaming reading started!"<<std::endl;
    stopRTSP=false;
    cap=new VideoCapture;
    cap2=new VideoCapture;
    cap3=new VideoCapture;
    cap->open("rtspsrc location=rtsp://192.168.1.100:8554/test latency=0 ! decodebin ! videoconvert ! appsink max-buffers=1 drop=true");
    cap2->open("rtspsrc location=rtsp://192.168.1.100:8554/test2 latency=0 ! decodebin ! videoconvert ! appsink max-buffers=1 drop=true");
    cap3->open("rtspsrc location=rtsp://192.168.1.100:8554/test3 latency=0 ! decodebin ! videoconvert ! appsink max-buffers=1 drop=true");
    if (!((cap->isOpened()&&cap2->isOpened())&&cap3->isOpened())) {
        std::cerr << "Failed to open stream" << std::endl;
        return;
    }
    Mat frame,frame2,frame3;
    QImage img,img2,img3;
    QPixmap map1,map2,map3;
    while (!stopRTSP && ((cap->read(frame)&&cap2->read(frame2))&&cap3->read(frame3))) {
        cvtColor(frame,frame,COLOR_BGR2RGB);
        cvtColor(frame2,frame2,COLOR_BGR2RGB);
        cvtColor(frame3,frame3,COLOR_BGR2RGB);
        img=QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
        img2=QImage(frame2.data,frame2.cols,frame2.rows,QImage::Format_RGB888);
        img3=QImage(frame3.data,frame3.cols,frame3.rows,QImage::Format_RGB888);
        map1=QPixmap::fromImage(img);
        map2=QPixmap::fromImage(img2);
        map3=QPixmap::fromImage(img3);
        emit sendframes(map1,map2,map3);
    }
    // 清理
    close(); // 确保释放资源
    return;
}

void rtsp::close()
{
    cap->release();
    cap2->release();//release函数在open时会自动调用，打开新的视频流时旧的会自动释放
    cap3->release();
    //stopped之后再start
    std::cout<<"Video streaming reading stopped!"<<std::endl;
    //delete cap;
    //delete cap2;
}
