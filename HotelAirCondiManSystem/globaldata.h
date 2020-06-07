#ifndef GLOBALDATE_H
#define GLOBALDATE_H

#define roomNum 5
//int room[roomNum] = {201,202,203,204,205};

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
