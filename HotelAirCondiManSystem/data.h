#ifndef DATA_H
#define DATA_H
#include <QTime>
#include "databasetimelyreport.h"
#include "databasesteplyreport.h"
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

class Data
{
public:
    Data();
    static Bill getBill(QString roomID);
};

#endif // DATA_H
