#include "tcpserver.h"

tcpserver::tcpserver() {
    for (int var = 0; var < 6; ++var) {
        basic_packet.original_data[var]=0;
    }
}

tcpserver::~tcpserver()
{
    delete timer;
    delete server;
    delete socket;
}
//##################################################//
//########################TCP#######################//
//##################################################//
void tcpserver::unpack_jy901s(QByteArray data_hear, int head)
{
    typedef union
    {
        unsigned char byte[36];
        float original_data[9];
    }jy901s;
    Ptr<jy901s> data=new jy901s;

    unsigned char check = 0;

    head = head + 3;

    for(int i=head;i<head+36;i++)
    {
        data->byte[i-head]=data_hear[i];
        check += data_hear[i];
    }
    check += data_hear[head-1];
    check += data_hear[head-2];
    qDebug()<<check;

    if(check==(unsigned char)data_hear[head+36])
    {
        //xyz加速度
        //Ptr<float> jia_speed=new float[3];
        for(int i = 0 ; i < 3 ; i++)
        {
            jia_speed[i]=(float)data->original_data[i];
        }
        //三轴角加速度
        //Ptr<float> jiaojia_speed=new float[3];
        for(int i = 3 ; i < 6 ; i++)
        {
            jiaojia_speed[i-3]=(float)data->original_data[i];
        }

        //r、p、y角度
        //Ptr<float> rpy_jiao_du=new float[3];
        for(int i = 6 ; i < 9 ; i++)
        {
            rpy_jiao_du[i-6]=(float)data->original_data[i];
        }
        //qDebug()<<"yaw:"<<rpy_jiao_du[0]<<'\n'<<"pitch"<<rpy_jiao_du[1]<<'\n'<<"roll:"<<rpy_jiao_du[2]<<endl;
        emit send_jy901s();

    }
    else
    {
        qDebug()<<"bushi1";
    }
}

void tcpserver::unpack_ms5837(QByteArray data_hear, int head)
{
    typedef union
    {
        unsigned char byte[16];
        float original_data[4];
    }ms5837;
    Ptr<ms5837> data=new ms5837;

    unsigned char check = 0;

    head = head + 3;

    for(int i=head;i<head+16;i++)
    {
        data->byte[i-head]=data_hear[i];
        check += data_hear[i];
    }
    check += data_hear[head-1];
    check += data_hear[head-2];
    qDebug()<<check;

    if(check==(unsigned char)data_hear[head+16])
    {
        //水深
        shui_shen = data->original_data[0];
        //水压
        shui_ya = data->original_data[1];
        //正面距离1
        Z1_dis = data->original_data[2];
        //正面距离2
        Z2_dis = data->original_data[3];
        //侧面距离
        //float* Side_dis = &data->original_data[4];
        emit send_ms5837();

    }
    else
    {
        qDebug()<<"bushi2";
    }
}

void tcpserver::unpack_shtc3(QByteArray data_hear, int head)
{
    typedef union
    {
        unsigned char byte[16];
        float original_data[4];
    }shtc3;
    Ptr<shtc3> data=new shtc3;

    unsigned char check = 0;

    head = head + 3;

    for(int i=head;i<head+16;i++)
    {
        data->byte[i-head]=data_hear[i];
        check += data_hear[i];
    }
    check += data_hear[head-1];
    check += data_hear[head-2];
    qDebug()<<check;

    if(check==(unsigned char)data_hear[head+16])
    {
        //温度
        temporator1 = (data->original_data[0]);
        temporator2 = (data->original_data[2]);

        //湿度
        humidity1 = (data->original_data[1]);
        humidity2 = (data->original_data[3]);
        emit send_shtc3();
    }
    else
    {
        qDebug()<<"bushi3";
    }
}

void tcpserver::unpack_pwm(QByteArray data_hear, int head)
{
    typedef union
    {
        unsigned char byte[36];
        float original_data[9];
    }pwm;
    Ptr<pwm> data=new pwm;

    unsigned char check = 0;

    head = head + 3;

    for(int i=head;i<head+36;i++)
    {
        data->byte[i-head]=data_hear[i];
        check += data_hear[i];
    }
    check += data_hear[head-1];
    check += data_hear[head-2];
    check=check&0xFF;
    qDebug()<<check;

    if(check==(unsigned char)data_hear[head+36])
    {
        for(int i=0;i<9;i++)
        {
            TuiJinQi_I[i] = data->original_data[i];
        }
        emit send_thruster();
    }
    else
    {
        qDebug()<<"bushi4";
    }
}

void tcpserver::unpack_yuntai(QByteArray data_hear, int head)
{
    typedef union
    {
        unsigned char byte[2];
        quint16 original_data;
    }yuntai;
    Ptr<yuntai> data=new yuntai;

    unsigned char check = 0;

    head = head + 3;

    for(int i=head;i<head+2;i++)
    {
        data->byte[i-head]=data_hear[i];
        check += data_hear[i];
    }
    check += data_hear[head-1];
    check += data_hear[head-2];
    qDebug()<<check;

    if(check==(unsigned char)data_hear[head+2])
    {
        //舵机
        duoji = (data->original_data);
        emit send_yuntai();
    }
    else
    {
        qDebug()<<"bushi5";
    }
}

void tcpserver::unpack_buffer(QByteArray buffer)
{
    qDebug()<<"服务器线程地址2："<<QThread::currentThread();
    for(int i = 0; i < buffer.length()-2; i++)
    {

        if((unsigned char)buffer.at(i) != 0xFF) continue;
        if((unsigned char)buffer.at(i+1) == 0xA1) unpack_jy901s(buffer,i);
        if((unsigned char)buffer.at(i+1) == 0xA2) unpack_ms5837(buffer,i);
        if((unsigned char)buffer.at(i+1) == 0xA3) unpack_shtc3(buffer,i);
        if((unsigned char)buffer.at(i+1) == 0xA4) unpack_pwm(buffer,i);
        if((unsigned char)buffer.at(i+1) == 0xA5) unpack_yuntai(buffer,i);
    }
}

void tcpserver::send_data_from_server(QByteArray data_send)
{
    int size = data_send.size();
    /*for(int i = 0; i<size ;i++)
    {
        //qDebug()<<"debug_send_upup_tcp : data["<<i<<"] = "<<(unsigned char)data_send.at(i);
    }*/
    //qDebug()<<"\n";
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        qint64 byteswritten=socket->write(data_send);
        qDebug()<<"发送成功\n"<<"共"<<byteswritten<<"字节\n";
    }
    else
    {
        qDebug()<<"发送失败\n";
    }
}

void tcpserver::pack_pid(const float *pidarray)
{    typedef union
    {
        unsigned char byte[96];
        float original_data[24];
    }pid;
    pid data;
    QByteArray data_send;
    data_send.resize(100);
    for (int i=0; i < 24; ++i) {
        data.original_data[i]=pidarray[i];
    }
    data_send[0]=0xFF;
    data_send[1]=0xB6;
    data_send[2]=24*sizeof(float);
    data_send[99]=0x00;
    for(int i=3;i<99;i++)
    {
        data_send[i]=data.byte[i-3];
    }
    for(int i=0;i<99;i++)
    {
        data_send[99]=data_send[99]+data_send[i];
    }
    send_data_from_server(data_send);
}

void tcpserver::start()
{
    qDebug()<<"服务器线程地址1："<<QThread::currentThread();
    server=new QTcpServer(this);//将父对象设为this,有助于管理内存回收
    socket=new QTcpSocket(this);
    timer=new QTimer(this);
    // 初始化已连接的游戏手柄
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (!gamepads.isEmpty()) {
        gamepad = new QGamepad(*gamepads.begin(), this);
    } else {
        qDebug() << "No gamepad connected";
    }
    server->listen(QHostAddress::Any,8000);
    timer->start(200);
    /*
      gamepad映射关系
    */
    for(int i=0;i<8;++i)
        function_packet.original_data[i]=0x02;
    connect(gamepad,&QGamepad::axisLeftYChanged,this,&tcpserver::gamepad_ping_y);
    connect(gamepad,&QGamepad::axisLeftXChanged,this,&tcpserver::gamepad_ping_x);
    connect(gamepad,&QGamepad::axisRightXChanged,this,&tcpserver::gamepad_zhuan_yaw);
    connect(gamepad,&QGamepad::axisRightYChanged,this,&tcpserver::gamepad_zhuan_pitch);
    connect(gamepad,&QGamepad::buttonL2Changed,this,&tcpserver::gamepad_zhuan_rollLeft);
    connect(gamepad,&QGamepad::buttonR2Changed,this,&tcpserver::gamepad_zhuan_rollRight);
    connect(gamepad,&QGamepad::buttonL1Changed,this,&tcpserver::gamepad_ping_z_up);
    connect(gamepad,&QGamepad::buttonR1Changed,this,&tcpserver::gamepad_ping_z_down);
    connect(gamepad,&QGamepad::buttonAChanged,this,&tcpserver::light);
    connect(gamepad,&QGamepad::buttonUpChanged,this,&tcpserver::pushstick);
    connect(gamepad,&QGamepad::buttonDownChanged,this,&tcpserver::electromagnet);
    connect(gamepad,&QGamepad::buttonRightChanged,this,&tcpserver::poselock);
    connect(gamepad,&QGamepad::buttonYChanged,this,&tcpserver::boot);
    connect(gamepad,&QGamepad::buttonXChanged,this,&tcpserver::velocitykeeping);
    connect(gamepad,&QGamepad::buttonLeftChanged,this,&tcpserver::autoduizheng);
    connect(gamepad,&QGamepad::buttonBChanged,this,&tcpserver::autospin);

    connect(server,&QTcpServer::newConnection,[this](){
        socket=server->nextPendingConnection();//返回一个指向 QTcpSocket 对象的指针，表示即将用于与客户端进行通信的套接字，取出连接好的套接字
        QString ip=socket->peerAddress().toString();
        quint16 port=socket->peerPort();
        QString numberstr=QString::number(port);// 使用 QString::number() 转换为 QString
        //QString info=QString("[%1:%2] 客户端成功建立连接").arg(ip).arg(port);
        emit send_ipport(ip,numberstr);
        connect(socket,&QTcpSocket::disconnected,[=](){
            emit warn();
            //QMessageBox::warning(p,"警告","客户端连接异常");
        });
        connect(timer,&QTimer::timeout,this,&tcpserver::sendcontrol);
        //QMessageBox::information(p,"information",info);
        connect(socket,&QTcpSocket::readyRead,[=](){
            QByteArray buffer;
            buffer.resize(120);
            //array.resize(120);
            buffer = socket->readAll();
            if(!buffer.isEmpty())
            {
                //在服务端发送时写入客户端通话记录
                QString msg;
                msg += "\n";
                msg += "【服务端】";
                msg += buffer.toHex();
                //刷新显示
                //ui->textEdit->setText(msg);
                emit send_msg(msg);
            }
            qDebug()<<"buffer:length"<<buffer.length()<<"\n";
            unpack_buffer(buffer);
        });//可以改进
    });
}

void tcpserver::close()
{
    timer->stop();
    //通信套接字主动与服务端断开连接
    socket->disconnectFromHost();//结束聊天
    socket->close();//关闭通信套接字
    socket=nullptr;//指针悬空防止误用
    server->close();
}

QByteArray tcpserver::createPacket(unsigned char contentDescriptor, const unsigned char* data, int dataLength) {
    // 计算数据包的总长度
    int packetLength = 4 + dataLength * sizeof(qint16); // 包长度
    QByteArray packet(packetLength, '\0');

    // 填充数据
    int index = 0;
    packet[index++] = 0xFF; // 第一个字节 0xFF
    packet[index++] = contentDescriptor; // 内容描述
    packet[index++] = static_cast<unsigned char>(dataLength*2); // 数据长度

    // 添加有效数据内容
    for (int i = 0; i < dataLength; ++i) {
        // 直接从 unsigned char* 读取 qint16 数据
        packet[index++] = data[i * 2]; // 低字节
        packet[index++] = data[i * 2 + 1]; // 高字节
    }

    // 计算校验位
    unsigned char checksum = 0;
    for (const auto& byte : packet) {
        checksum += static_cast<unsigned char>(byte);
    }
    checksum %= 256; // 计算 % 256

    // 添加校验位
    packet[index] = checksum; // 直接在最后一个位置加入校验位

    return packet;
}


void tcpserver::sendcontrol()
{
    QByteArray basic_move(16, '\0');
    QByteArray function_button(20,'\0');
    basic_move=createPacket(0xB1,basic_packet.byte,6);
    function_button=createPacket(0xB2,function_packet.byte,8);
    send_data_from_server(basic_move);
    send_data_from_server(function_button);
}

//##################################################//
//########################辅助#######################//
//##################################################//

//使之一按一松算一次而不是两次

static qint16 light_switch = 0x02,a=0;
static qint16 velocity_switch = 0x02,b=0;
static qint16 duizheng_switch = 0x02,c=0;
static qint16 boot_switch = 0x02,d=0;
static qint16 poselock_switch = 0x02,e=0;
static qint16 electromagnet_switch = 0x02,f=0;
static qint16 pushstick_switch = 0x02,g=0;
static qint16 spin_switch = 0x02,h=0;


void tcpserver::light(double)
{
    if(++a%2==0){
        // 切换值
        if (light_switch == 0x01) {
            light_switch = 0x02;
        } else {
            light_switch = 0x01;
        }
        function_packet.original_data[0]=light_switch;
    }
}

void tcpserver::poselock(double)
{
    if(++b%2==0){
        // 切换值
        if ( poselock_switch== 0x01) {
             poselock_switch= 0x02;
        } else {
             poselock_switch= 0x01;
        }
        function_packet.original_data[1]=poselock_switch;
    }
}

void tcpserver::boot(double)
{
    if(++c%2==0){
        // 切换值
        if (boot_switch == 0x01) {
            boot_switch = 0x02;
        } else {
            boot_switch = 0x01;
        }
        function_packet.original_data[2]=boot_switch;
    }
}

void tcpserver::velocitykeeping(double)
{
    if(++d%2==0){
        // 切换值
        if (velocity_switch == 0x01) {
            velocity_switch = 0x02;
        } else {
            velocity_switch = 0x01;
        }
        function_packet.original_data[3]=velocity_switch;
    }
}

void tcpserver::electromagnet(double)
{
    if(++e%2==0){
        // 切换值
        if (electromagnet_switch == 0x01) {
            electromagnet_switch = 0x02;
        } else {
            electromagnet_switch = 0x01;
        }
        function_packet.original_data[4]=electromagnet_switch;
    }
}

void tcpserver::pushstick(double)
{
    if(++f%2==0){
        // 切换值
        if (pushstick_switch == 0x01) {
            pushstick_switch = 0x02;
        } else {
            pushstick_switch = 0x01;
        }
        function_packet.original_data[5]=pushstick_switch;
    }
}

void tcpserver::autoduizheng(double)
{
    if(++g%2==0){
        // 切换值
        if (duizheng_switch == 0x01) {
            duizheng_switch = 0x02;
        } else {
            duizheng_switch = 0x01;
        }
        function_packet.original_data[6]=duizheng_switch;
    }
}

void tcpserver::autospin(double)
{
    if(++h%2==0){
        // 切换值
        if (spin_switch == 0x01) {
            spin_switch = 0x02;
        } else {
            spin_switch = 0x01;
        }
        function_packet.original_data[7]=spin_switch;
    }
}

//##################################################//
//########################平动#######################//
//##################################################//

void tcpserver::gamepad_ping_x(double value)
{
    qint16 num=0;
    if(value>=0.1)
    {    //把0.1～1.0映射到0～100
        num = 100.0*(value-0.1)/0.9;
    }
    else if(value<=-0.1)
    {   //把-1.0～-0.1映射到-100～0
        num = 100.0*(value+0.1)/0.9;
    }
    basic_packet.original_data[1]=num;
}

void tcpserver::gamepad_ping_y(double value)
{
    qint16 num=0;
    if(value>=0.1)
    {    //把0.1～1.0映射到0～100,y要反转*(-1)
        num = 100.0*(value-0.1)/0.9*(-1.0);
    }
    else if(value<=-0.1)
    {   //把-1.0～-0.1映射到-100～0,y要反转*(-1)
        num = 100.0*(value+0.1)/0.9*(-1.0);
    }
    basic_packet.original_data[0]=num;
}

//################### z平动控制上下 ####################

void tcpserver::gamepad_ping_z_up(double value)
{
    qint16 num=0;
    if(value >= 0.2)
    {
        num = 100.0*(value-0.1)/0.9;
    }
    basic_packet.original_data[2]=num;
}
void tcpserver::gamepad_ping_z_down(double value)
{
    qint16 num=0;
    if(value >= 0.2)
    {
        num = 100.0*(value-0.1)/0.9*(-1);
    }
    basic_packet.original_data[2]=num;
}

//##################################################//
//########################转动#######################//
//##################################################//

void tcpserver::gamepad_zhuan_rollLeft(double value)
{
    qint16 num=0;
    if(value>=0.1)
        num=100*(0.1-value)/0.9;
    basic_packet.original_data[5]=num;
}

void tcpserver::gamepad_zhuan_rollRight(double value)
{
    qint16 num=0;
    if(value>=0.1)
        num=100*(value-0.1)/0.9;
    basic_packet.original_data[5]=num;
}

void tcpserver::gamepad_zhuan_pitch(double value)
{
    qint16 num = 0;

/*
    // --- 参数定义 ---
    // 手柄摇杆的中心位置是 0.5
    const double center_point = 0.5;
    // 在中心点左右设置一个死区范围，防止摇杆漂移void Gamepad::gamepad_zhuan_pitch(double value)
{
    if(value < 0.1 && value > -0.1)
    {   //认定为0
        p->ui->zhuan_p->setText(QString::number(0));
    }
    else if(value>=0.1)
    {    //把0.1～1.0映射到0～100，要反转
        int num = 100.0*(value-0.1)/0.9*(-1.0);
        p->ui->zhuan_p->setText(QString::number(num));
    }

    else if(value<=-0.1)
    {   //把-1.0～-0.1映射到-100～0，要反转
        int num = 100.0*(value+0.1)/0.9*(-1.0);
        p->ui->zhuan_p->setText(QString::number(num));
    }
}

void Gamepad::gamepad_zhuan_yaw(double value)
{
    if(value < 0.1 && value > -0.1)
    {   //认定为0
        p->ui->zhuan_y->setText(QString::number(0));
    }
    else if(value>=0.1)
    {    //把0.1～1.0映射到0～100
        int num = 100.0*(value-0.1)/0.9;
        p->ui->zhuan_y->setText(QString::number(num));
    }
    else if(value<=-0.1)
    {   //把-1.0～-0.1映射到-100～0
        int num = 100.0*(value+0.1)/0.9;
        p->ui->zhuan_y->setText(QString::number(num));
    }
}

    // 例如，0.05 意味着 [0.45, 0.55] 范围内的输入都会被当作中心点
    const double deadzone = 0.05;

    // --- 核心逻辑 ---
    // 1. 判断摇杆是否已经离开了中心点的死区范围
    if (abs(value - center_point) > deadzone)
    {
        // 2. 将 [0, 1] 的范围映射到 [-100, 100]
        //    - 先将 [0, 1] 映射到 [-0.5, 0.5]  (通过减去 center_point)
        //    - 再将 [-0.5, 0.5] 映射到 [-100, 100] (通过乘以 200)
        //    一个更简单的数学公式是：output = (input * 200.0) - 100.0
        double mapped_value = (value * 200.0) - 100.0;

        // 3. 【可选】进行反转，这和您之前的逻辑一致
        // 如果您发现俯仰方向反了，可以移除或注释掉下面这行
        mapped_value *= -1.0;

        // 4. 将计算出的浮点数转换为整数
        num = static_cast<qint16>(mapped_value);

        // 限制最终值在 [-100, 100] 之间，防止意外溢出
        if (num > 100) num = 100;
        if (num < -100) num = -100;
    }
    // 如果摇杆在死区内，num 保持为 0，设备不动
*/
    if(value>=0.1)
    {    //把0.1～1.0映射到0～100，要反转
        num = 100.0*(value-0.1)/0.9*(-1.0);
    }
    else if(value<=-0.1)
    {   //把-1.0～-0.1映射到-100～0，要反转
        num = 100.0*(value+0.1)/0.9*(-1.0);
    }
    // 5. 将最终计算出的值赋给数据包
    basic_packet.original_data[4] = num;
}

void tcpserver::gamepad_zhuan_yaw(double value)
{
    qint16 num = 0;
/*
    // --- 参数定义 ---
    // 手柄摇杆的中心位置是 0.5
    const double center_point = 0.5;
    // 在中心点左右设置一个死区范围，防止摇杆漂移
    // 例如，0.05 意味着 [0.45, 0.55] 范围内的输入都会被当作中心点
    const double deadzone = 0.05;

    // --- 核心逻辑 ---
    // 1. 判断摇杆是否已经离开了中心点的死区范围
    if (abs(value - center_point) > deadzone)
    {
        // 2. 将 [0, 1] 的范围映射到 [-100, 100]
        //    - 先将 [0, 1] 映射到 [-0.5, 0.5]  (通过减去 center_point)
        //    - 再将 [-0.5, 0.5] 映射到 [-100, 100] (通过乘以 200)
        //    一个更简单的数学公式是：output = (input * 200.0) - 100.0
        double mapped_value = (value * 200.0) - 100.0;

        // 3. 【可选】进行反转，这和您之前的逻辑一致
        // 如果您发现俯仰方向反了，可以移除或注释掉下面这行
        //mapped_value *= -1.0;

        // 4. 将计算出的浮点数转换为整数
        num = static_cast<qint16>(mapped_value);

        // 限制最终值在 [-100, 100] 之间，防止意外溢出
        if (num > 100) num = 100;
        if (num < -100) num = -100;
    }
    // 如果摇杆在死区内，num 保持为 0，设备不动
*/
    if(value>=0.1)
    {    //把0.1～1.0映射到0～100
        num = 100.0*(value-0.1)/0.9;
    }
    else if(value<=-0.1)
    {   //把-1.0～-0.1映射到-100～0
        num = 100.0*(value+0.1)/0.9;
    }
    // 5. 将最终计算出的值赋给数据包
    basic_packet.original_data[3] = num;
}




