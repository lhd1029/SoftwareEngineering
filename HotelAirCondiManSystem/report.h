#ifndef REPORT_H
#define REPORT_H
#include "QDate"
#define ROOMNUM 10

struct records{
    QDate date;
    int roomId;
    int useACTimes;  //空调使用次数
    int comTarDegree; //常用目标温度
    int comWind; //常用风速
    int getTarDegreeTimes; //达到目标温度次数
    int dispathTimes; //被调度次数
    int detailRecordRows; //详单记录数
    int totalmoney; //总费用
};

class Report
{
public:
    Report(QDate start, QDate end);
    void setRecord(QDate date, int recordN);
    records getRecord(int i);
private:
    QDate start;
    QDate end;
    records *record;
};

#endif // REPORT_H
