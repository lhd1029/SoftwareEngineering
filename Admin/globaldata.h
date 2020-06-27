#ifndef GLOBALDATE_H
#define GLOBALDATE_H

#include <QVector>

#define RUNNING 1 //空调正在运行
#define WAITING 2 //空调等待被调度
#define NOUSE 0 //空调开启但未操作
#define POWERON 1 //空调开启
#define POWEROFF 0 //空调关闭
#define NOWIND 0 //无风
#define WINDLOW 1//低风
#define WINDMID 2//中风
#define WINDHIGH 3//高风

#define initDefaultTemp 25 //默认温度
#define initDefaultWind 1 //默认风速
#define initColdLowLimit 18 //默认制冷最低温
#define initColdHighLimit 25 //默认制冷最高温
#define initHotLowLimit 25 //默认制热最低温度
#define initHotHighLimit 30//默认制热最高温
#define initFeeRate 1//默认费率
#define initServeNum 5//默认服务数

//int room[roomNum] = {201,202,203,204,205};
static QVector<int> roomIdVec{101,102,103,104,105,106,107,108,109,110,201,202,203,204,205,206,207,208,209,210,301,302,303,304,305,306,307,308,309,310};


struct roomState{
    int roomId;
    int powerOnOff; //是否开机
    int serveOrHangUp; //服务=1 挂起=0
    double currentTemp;
    double targetTemp;
    int wind;
    double feeRate;
    double fee;
    int serveTime; //格式？int? QTime？
};

#endif // GLOBALDATE_H
