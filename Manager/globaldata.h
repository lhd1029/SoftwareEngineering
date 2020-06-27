#ifndef GLOBALDATE_H
#define GLOBALDATE_H

#define roomNum 5
#define RUNNING 1 //空调正在运行
#define WAITING 2 //空调等待被调度
#define NOUSE 0 //空调开启但未操作
#define POWERON 1 //空调开启
#define POWEROFF 0 //空调关闭
#include <QVector>

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
