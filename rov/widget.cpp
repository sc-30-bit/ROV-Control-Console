 #include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //things to be done
    qDebug()<<"主线程地址："<<QThread::currentThread();
    ui->setupUi(this);
    setWindowTitle("Host Computer");
    ui->hit_jpg->setPixmap(QPixmap(":/pictures/th-removebg-preview.png").scaled(ui->hit_jpg->width(), ui->hit_jpg->height()));
    ui->rover_jpg->setPixmap(QPixmap(":/pictures/rover-removebg-preview.png").scaled(ui->rover_jpg->width(), ui->rover_jpg->height()));
    ui->rov->setPixmap(QPixmap(":/pictures/rov2.png").scaled(ui->rov->width(), ui->rov->height()) );
    localization=new LocalizationMap(this);
    Rtsp=new rtsp;
    server1=new tcpserver();
    Saver=new saver;
    timer1=new QTimer;
    timer2=new QTimer;
    timer3=new QTimer;
    Stitcher=new stitcher;
    tcpthread=new QThread(this);
    rtspThread=new QThread(this);
    SaverThread=new QThread(this);
    stitchThread=new QThread(this);
    Rtsp->moveToThread(rtspThread);
    server1->moveToThread(tcpthread);
    Saver->moveToThread(SaverThread);
    Stitcher->moveToThread(stitchThread);
    connect(ui->opencamera,&QPushButton::clicked,[=](){
        rtspThread->start();
        SaverThread->start();
        stitchThread->start();
    });
    //拼接连接
    connect(Saver,&saver::stitching,Stitcher,&stitcher::stitch);
    //RTSP流显示控制
    connect(ui->opencamera,&QPushButton::clicked,Rtsp,&rtsp::start);
    connect(ui->closecameras,&QPushButton::clicked,this,[=](){
        stopRTSP=true;
    });
    connect(Rtsp,&rtsp::sendframes,this,&Widget::showframes);
    //保存画面
    connect(this,&Widget::sendPicture,Saver,&saver::savePicture);
    connect(ui->toolButton_9,&QToolButton::clicked,[=]{
        emit sendPicture(ui->label_2->pixmap(Qt::ReturnByValueConstant()),1);
    });
    connect(ui->toolButton_11,&QToolButton::clicked,[=]{
        emit sendPicture(ui->label_5->pixmap(Qt::ReturnByValueConstant()),2);
    });
    connect(ui->toolButton_12,&QToolButton::clicked,[=]{
        emit sendPicture(ui->stitching->pixmap(Qt::ReturnByValueConstant()),3);
    });
    //保存视频
    connect(this,&Widget::sendVideo,Saver,&saver::fillVetctor);
    connect(timer1,&QTimer::timeout,this,[=]{
        emit sendVideo(ui->label_2->pixmap(Qt::ReturnByValueConstant()),1);
    });
    connect(this,&Widget::timerStopped,Saver,&saver::saveVideo);
    connect(ui->toolButton_6,&QToolButton::clicked,[=](){
        saveVideo1++;
        if(saveVideo1%2==1){
            timer1->start(33);
        }
        else{
            timer1->stop();
            emit timerStopped(1);
        }
    });
    connect(timer2,&QTimer::timeout,this,[=]{
        emit sendVideo(ui->label_5->pixmap(Qt::ReturnByValueConstant()),2);
    });
    connect(ui->toolButton_10,&QToolButton::clicked,[=](){
        saveVideo2++;
        if(saveVideo2%2==1){
            timer2->start(33);
        }
        else{
            timer2->stop();
            emit timerStopped(2);
        }
    });
    connect(timer3,&QTimer::timeout,this,[=]{
        emit sendVideo(ui->stitching->pixmap(Qt::ReturnByValueConstant()),3);
    });
    connect(ui->jianmo,&QPushButton::clicked,[=](){
        saveVideo3++;
        if(saveVideo3%2==1){
            timer3->start(99);
        }
        else{
            timer3->stop();
            emit timerStopped(3);
        }
    });
    //TCP通讯
    connect(server1,&tcpserver::send_msg,this,&Widget::showmsg);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        tcpthread->start();
    });
    connect(ui->pushButton,&QPushButton::clicked,server1,&tcpserver::start);
    connect(ui->pushButton_2,&QPushButton::clicked,server1,&tcpserver::close);
    connect(server1,&tcpserver::send_ipport,this,&Widget::showinfo);
    connect(server1,&tcpserver::warn,this,&Widget::showwarning);
    //一定要注意不要在子线程修改ui，如果发出信号的是子线程的话，要修改ui，如弹窗，改textbrowser等一定不能用匿名函数，用了就是在子线程修改，要单独写widget曹函数，修改操作要写在对应的widget曹函数里
    connect(server1,&tcpserver::send_jy901s,this,&Widget::showjys901);
    connect(server1,&tcpserver::send_ms5837,this,&Widget::showms5837);
    connect(server1,&tcpserver::send_shtc3,this,&Widget::showshtc3);
    connect(server1,&tcpserver::send_thruster,this,&Widget::showthruster);//数据有些问题，需要商议
    connect(server1,&tcpserver::send_yuntai,this,&Widget::showyuntai);
    //没有电池connect(ui->elec,&QTextBrowser::textChanged,ui->battery,[=](){ui->battery->setValue(ui->elec->toPlainText().toFloat());});
    connect(ui->I_9,&QTextBrowser::textChanged,ui->widget_10,[=](){ui->widget_10->setValue(ui->I_9->toPlainText().toInt());});
    connect(ui->I_10,&QTextBrowser::textChanged,ui->widget_11,[=](){ui->widget_11->setValue(ui->I_10->toPlainText().toInt());});
    connect(ui->I_11,&QTextBrowser::textChanged,ui->widget_12,[=](){ui->widget_12->setValue(ui->I_11->toPlainText().toInt());});
    connect(ui->I_12,&QTextBrowser::textChanged,ui->widget_13,[=](){ui->widget_13->setValue(ui->I_12->toPlainText().toInt());});
    connect(ui->I_13,&QTextBrowser::textChanged,ui->widget_14,[=](){ui->widget_14->setValue(ui->I_13->toPlainText().toInt());});
    connect(ui->I_14,&QTextBrowser::textChanged,ui->widget_15,[=](){ui->widget_15->setValue(ui->I_14->toPlainText().toInt());});
    connect(ui->I_15,&QTextBrowser::textChanged,ui->widget_16,[=](){ui->widget_16->setValue(ui->I_15->toPlainText().toInt());});
    connect(ui->I_16,&QTextBrowser::textChanged,ui->widget_17,[=](){ui->widget_17->setValue(ui->I_16->toPlainText().toInt());});
    connect(ui->transmit_pid,&QPushButton::clicked,[this](){
        float* pid=new float[24];
        pid[0]=(float)(ui->ikp->text().toFloat());
        pid[1]=(float)(ui->iki->text().toFloat());
        pid[2]=(float)(ui->ikd->text().toFloat());
        pid[3]=(float)(ui->okp1->text().toFloat());
        pid[4]=(float)(ui->oki1->text().toFloat());
        pid[5]=(float)(ui->okd1->text().toFloat());
        pid[6]=(float)(ui->okp2->text().toFloat());
        pid[7]=(float)(ui->oki2->text().toFloat());
        pid[8]=(float)(ui->okd2->text().toFloat());
        pid[9]=(float)(ui->okp3->text().toFloat());
        pid[10]=(float)(ui->oki3->text().toFloat());
        pid[11]=(float)(ui->okd3->text().toFloat());
        pid[12]=(float)(ui->okp4->text().toFloat());
        pid[13]=(float)(ui->oki4->text().toFloat());
        pid[14]=(float)(ui->okd4->text().toFloat());
        pid[15]=(float)(ui->okp5->text().toFloat());
        pid[16]=(float)(ui->oki5->text().toFloat());
        pid[17]=(float)(ui->okd5->text().toFloat());
        pid[18]=(float)(ui->okp6->text().toFloat());
        pid[19]=(float)(ui->oki6->text().toFloat());
        pid[20]=(float)(ui->okd6->text().toFloat());
        pid[21]=(float)(ui->dkp->text().toFloat());
        pid[22]=(float)(ui->dki->text().toFloat());
        pid[23]=(float)(ui->dkd->text().toFloat());
        emit form_pidarray(pid);
    });
    connect(this,&Widget::form_pidarray,server1,&tcpserver::pack_pid);
    //定位系统
    connect(ui->openLocalization,&QPushButton::clicked,localization,&LocalizationMap::show);
    connect(ui->closeLocalization,&QPushButton::clicked,localization,&LocalizationMap::close);
    connect(server1,&tcpserver::send_ms5837,localization,&LocalizationMap::showDistance);
}
void Widget::receiveLogin()//跳转
{
    this->show();
}

void Widget::showframes(QPixmap frame1, QPixmap frame2,QPixmap frame3)
{
    ui->label_2->setPixmap(frame1.scaled(ui->label_2->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->label_5->setPixmap(frame2.scaled(ui->label_5->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->stitching->setPixmap(frame3.scaled(ui->stitching->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}
void Widget::showwarning()
{
    qDebug()<<"warn窗口线程地址"<<QThread::currentThread();
    QMessageBox::warning(this,"警告","客户端连接异常");
}

void Widget::showinfo(QString ip,QString port)
{
    qDebug()<<"info窗口线程地址"<<QThread::currentThread();
    ui->ip->setText(ip);
    ui->port->setText(port);
    QString info=QString("[%1:%2] 客户端成功建立连接").arg(ip).arg(port);
    QMessageBox::information(this,"information",info);
}

void Widget::showjys901()
{
    ui->ax->setText(QString("%4").arg(jia_speed[0]));
    ui->ay->setText(QString("%4").arg(jia_speed[1]));
    ui->az->setText(QString("%4").arg(jia_speed[2]));
    ui->wx->setText(QString("%4").arg(jiaojia_speed[0]));
    ui->wy->setText(QString("%4").arg(jiaojia_speed[1]));
    ui->wz->setText(QString("%4").arg(jiaojia_speed[2]));
    //qDebug()<<"yaw:"<<EulerianAngle[0]<<'\n'<<"pitch"<<EulerianAngle[1]<<'\n'<<"roll:"<<EulerianAngle[2]<<endl;
    ui->roll->setText(QString("%4").arg(rpy_jiao_du[0]));
    ui->pitch->setText(QString("%4").arg(rpy_jiao_du[1]));
    ui->yaw->setText(QString("%4").arg(rpy_jiao_du[2]));
    ui->gaugeCompass->setValue(rpy_jiao_du[2]);
}

void Widget::showms5837()
{
    //qDebug()<<"1，2："<<*Z1_dis<<' '<<*Z2_dis<<endl;
    ui->shui_ya->setText(QString("%4").arg(shui_ya));
    ui->shui_shen->setText(QString("%4").arg(shui_shen));
    ui->Z1_text->setText(QString("%4").arg(Z1_dis));
    ui->Z2_text->setText(QString("%4").arg(Z2_dis));
    //ui->Side_text->setText(QString("%4").arg(*side_dis));
}

void Widget::showshtc3()
{
    ui->temperator1->setText(QString("%4").arg(temporator1));
    ui->humidity1->setText(QString("%4").arg(humidity1));
    ui->temperator2->setText(QString("%4").arg(temporator2));
    ui->humidity2->setText(QString("%4").arg(humidity2));
}

void Widget::showthruster()
{
    ui->I_9->setText(QString("%4").arg(TuiJinQi_I[0]));
    ui->I_10->setText(QString("%4").arg(TuiJinQi_I[1]));
    ui->I_11->setText(QString("%4").arg(TuiJinQi_I[2]));
    ui->I_12->setText(QString("%4").arg(TuiJinQi_I[3]));
    //ui->elec->setText(QString("%2").arg((current8[4]*0.004153+0.7404-11.2)*100*2/3));
    //p->ui->elec->setText(QString("%2").arg(95));
    ui->I_13->setText(QString("%4").arg(TuiJinQi_I[5]));
    ui->I_14->setText(QString("%4").arg(TuiJinQi_I[6]));
    ui->I_15->setText(QString("%4").arg(TuiJinQi_I[7]));
    ui->I_16->setText(QString("%4").arg(TuiJinQi_I[8]));
    ui->widget_10->setValue(TuiJinQi_I[0]);
    ui->widget_11->setValue(TuiJinQi_I[1]);
    ui->widget_12->setValue(TuiJinQi_I[2]);
    ui->widget_13->setValue(TuiJinQi_I[3]);
    ui->widget_14->setValue(TuiJinQi_I[5]);
    ui->widget_15->setValue(TuiJinQi_I[6]);
    ui->widget_16->setValue(TuiJinQi_I[7]);
    ui->widget_17->setValue(TuiJinQi_I[8]);
}

void Widget::showyuntai()
{
    //ui->duoji->setText(QString("%4").arg(*angle));
}

void Widget::showmsg(QString msg)
{
    ui->textEdit->append(msg);
}

Widget::~Widget()
{
    //优雅退出线程
    rtspThread->quit();
    rtspThread->wait();
    rtspThread->deleteLater();
    tcpthread->quit();
    tcpthread->wait();
    tcpthread->deleteLater();
    SaverThread->quit();
    SaverThread->wait();
    SaverThread->deleteLater();
    stitchThread->quit();
    stitchThread->wait();
    stitchThread->deleteLater();
    Rtsp->deleteLater();
    server1->deleteLater();
    Saver->deleteLater();
    Stitcher->deleteLater();
    delete ui;
}
