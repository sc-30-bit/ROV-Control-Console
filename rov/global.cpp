#include<global.h>

std::atomic<bool> stopRTSP(false);
std::atomic<quint64> saveVideo1=0;
std::atomic<quint64> saveVideo2=0;
std::atomic<quint64> saveVideo3=0;
std::atomic<float> jia_speed[3]={0,0,0},jiaojia_speed[3]={0,0,0},rpy_jiao_du[3]={0,0,0};
std::atomic<float> shui_shen=0,shui_ya=0,Z1_dis=0, Z2_dis=0;
std::atomic<float> temporator1=0,temporator2=0,humidity1=0,humidity2=0;
std::atomic<float> TuiJinQi_I[9]={0};
std::atomic<quint16> duoji=0;
