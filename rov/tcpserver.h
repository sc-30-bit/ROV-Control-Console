#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>
#include<QGamepad>
#include<QGamepadManager>
#include<opencv2/opencv.hpp>
#include<QMessageBox>
#include<QDebug>
#include<QThread>
#include<global.h>
#include<QTimer>

using namespace cv;

class tcpserver :public QObject
{
    Q_OBJECT
public:
    tcpserver();
    ~tcpserver();
public slots:
    void unpack_jy901s(QByteArray data_hear,int head);
    void unpack_ms5837(QByteArray data_hear,int head);
    void unpack_shtc3(QByteArray data_hear,int head);
    void unpack_pwm(QByteArray data_hear,int head);
    void unpack_yuntai(QByteArray data_hear,int head);
    void unpack_buffer(QByteArray buffer);
    void send_data_from_server(QByteArray data_send);
    void pack_pid(const float* pidarray);
    void start();
    void close();
    QByteArray createPacket(unsigned char contentDescriptor, const unsigned char* data, int dataLength);
    void sendcontrol();
    //灯，姿态锁，定速，定深，对正，自动翻滚，
    //function
    void light(double);
    void poselock(double);
    void boot(double);
    void velocitykeeping(double);
    void electromagnet(double);
    void pushstick(double);
    void autoduizheng(double);
    void autospin(double);
    //basicmove
    void gamepad_ping_x(double value);
    void gamepad_ping_y(double value);
    void gamepad_ping_z_up(double value);
    void gamepad_ping_z_down(double value);
    void gamepad_zhuan_rollLeft(double value);
    void gamepad_zhuan_rollRight(double value);
    void gamepad_zhuan_pitch(double value);
    void gamepad_zhuan_yaw(double value);


private:
    Ptr<QTcpServer> server;
    Ptr<QTcpSocket> socket;
    Ptr<QGamepad> gamepad;
    Ptr<QTimer> timer;
    data_0xB1 basic_packet;//12bytes
    data_0xB2 function_packet;//14bytes

signals:
    void send_jy901s();//9个4byte数据,float
    void send_ms5837();//2个4byte数据,float
    void send_shtc3();//4个4byte数据,float
    void send_thruster();//9个4byte数据,float
    void send_yuntai();//1个2byte数据,uint16
    void send_ipport(QString ip,QString port);
    void send_msg(QString msg);
    void warn();
};

#endif // TCPSERVER_H
