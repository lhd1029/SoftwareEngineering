#ifndef DATA_H
#define DATA_H
#include <QTime>
#include "databasetimelyreport.h"
#include <iostream>
using namespace std;

typedef struct{
    QDateTime using_time_total;//总使用时间
    QDateTime using_time_high;//高风速使用时间
    QDateTime using_time_medium;//中风速使用时间
    QDateTime using_time_low;//低风速使用时间
    double rate;//费率
    double payment;//支付金额
}Bill;

class Data
{
public:
    Data();
    static Bill getBill(QString roomID);
};

#endif // DATA_H
