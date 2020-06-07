#ifndef REPORT_H
#define REPORT_H
#include <QDate>
#include <list>
#include "globaldata.h"

struct record{
    QDate date;
    int roomId;
    int useACTimes;  //空调使用次数
    double comTarDegree; //常用目标温度
    int comWind; //常用风速
    int getTarDegreeTimes; //达到目标温度次数
    int dispathTimes; //被调度次数
    int detailRecordRows; //详单记录数
    double totalmoney; //总费用
};

class Report
{
public:
    Report();
    Report(QDate start, QDate end);

    //get set
    QDate getStart() const;
    void setStart(const QDate &value);

    QDate getEnd() const;
    void setEnd(const QDate &value);

    std::list<record> getRecords() const;
    void setRecords(const std::list<record> &value);

private:
    QDate start;
    QDate end;
    std::list<record> records;
};

#endif // REPORT_H
