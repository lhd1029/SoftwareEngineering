#include "report.h"

int roomId[] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110};

Report::Report(QDate start, QDate end)
{
    int days = start.daysTo(start);
    records r[days*ROOMNUM];
    this->record = r;
    //设置报表中的记录
    for(int j = 0; j < days; j++)
    {
        for(int i =0; i < ROOMNUM; i++){
            setRecord(start.addDays(j), j*ROOMNUM + i);
        }
    }
}

void Report::setRecord(QDate date, int recordN)
{
    this->record[recordN].date = date;
    //其它数据从数据库中获取
    //详单记录数？？
}

//获取报表中某条记录
records Report::getRecord(int i)
{
    return this->record[i];
}
