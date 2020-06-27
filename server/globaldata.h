#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QDateTime>
#include <QVector>
#include <vector>
//#define roomNum 30
//int room[roomNum]={101,102,103,104,105,106,107,108,109,110,201,202,203,204,205,206,207,208,209,210,301,302,303,304,305,306,307,308,309,310}

#define roomNum 5
#define RUNNING 1 //空调正在运行
#define WAITING 2 //空调等待被调度
#define NOUSE 0 //空调开启但未操作
#define POWERON 1 //空调开启
#define POWEROFF 0 //空调关闭
#define WINDLOW 1//低风
#define WINDMID 2//中风
#define WINDHIGH 3//高风

static QVector<int> roomIdVec{101,102,103,104,105,106,107,108,109,110,201,202,203,204,205,206,207,208,209,210,301,302,303,304,305,306,307,308,309,310};

typedef struct{
    int roomID;//房间号
    QDateTime checkInTime;//入住时间
    QDateTime checkOutTime;//离店时间
    double payment;//支付金额
}Bill;

typedef struct{
    int roomID;
    std::vector<QDateTime> startTime;//开始送风时间
    std::vector<QDateTime> endTime;//结束送风时间
    std::vector<int> duration;//送风时长
    std::vector<int> windSpeed;//风速
    std::vector<double> rate;//费率
    std::vector<double> fee;//费用

}List;

typedef struct{
    int roomID;
    int ACUseTimes;
    int ChangeTempTimes;
    int ChangeWindTimes;
    int ACdispatchedTimes;
    double ACUseTime;
    int detailedNum;
    double fee;
}ReportOne;

typedef struct{
    int occupied;
}roomState;


#endif // GLOBALDATA_H
