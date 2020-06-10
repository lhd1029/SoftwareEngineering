#ifndef DATA_H
#define DATA_H
#include <QTime>
#include "databasetimelyreport.h"
#include "databasesteplyreport.h"
#include "globaldata.h"
#include <iostream>
using namespace std;

typedef struct{
    QString roomID;
//    QDateTime using_time_total;//总使用时间
//    QDateTime using_time_high;//高风速使用时间
//    QDateTime using_time_medium;//中风速使用时间
//    QDateTime using_time_low;//低风速使用时间
//    double rate;//费率
    QDateTime checkInTime;//入住时间
    QDateTime checkOutTime;//离店时间
    double payment;//支付金额
}Bill;

typedef struct{
    QString roomId;
    double useACTime;  //空调使用时长
    int getChangeWindTimes; //调风次数
    int getChangeDegreeTimes; //调温次数
    int dispathTimes; //被调度次数
    int detailRecordRows; //详单记录数
    double totalmoney; //总费用
}Reportlist;

typedef struct{
    list<QDate> date;
    list<list<Reportlist>> reportlist;
}Report;

class Data
{
public:
    Data();
    static Bill getBill(QString roomID);
    static Report getReport(QDate start, QDate end);
    static list<Reportlist> getReportList(QString date);
};

#endif // DATA_H
