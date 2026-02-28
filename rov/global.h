#ifndef GLOBAL_H
#define GLOBAL_H
#include<atomic>
#include <QObject>

//使用原子变量，相对线程锁来说更便捷安全
/*
  flag for RTSP control
*/
extern std::atomic<bool> stopRTSP;//尽量不使用全局变量，用了加static修饰并且必须初始化,extern不能和static联用，extern表示该变量在别的文件中会用到，不要在extern声明时初始化，在对应的源文件中初始化
extern std::atomic<quint64> saveVideo1;
extern std::atomic<quint64> saveVideo2;
extern std::atomic<quint64> saveVideo3;
/*
  data to be shown in the GUI,跨线程的话一定不要用指针传递数据，相应的地址很可能被free了
*/
//extern不影响生命周期：它只是扩展变量的作用域，不改变内存分配或回收时机。全局变量（包括extern声明的）在程序结束时自动回收，无需手动释放
extern std::atomic<float> jia_speed[3],jiaojia_speed[3],rpy_jiao_du[3];
extern std::atomic<float> shui_shen,shui_ya,Z1_dis, Z2_dis;
extern std::atomic<float> temporator1,temporator2,humidity1,humidity2;
extern std::atomic<float> TuiJinQi_I[9];
extern std::atomic<quint16> duoji;
/*
    basicmove data packets
*/
typedef union
{
    unsigned char byte[12];
    qint16 original_data[6];
}data_0xB1;
/*
   function packet
*/
typedef union
{
    unsigned char byte[16];
    qint16 original_data[8];
}data_0xB2;



#endif // GLOBAL_H
