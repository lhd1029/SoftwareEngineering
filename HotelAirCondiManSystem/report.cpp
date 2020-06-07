#include "report.h"

Report::Report()
{

}

Report::Report(QDate start, QDate end)
{
    int days = start.daysTo(start) + 1;
    //this->recordsNum = days * ROOMNUM; 记录数=报表天数*房间数
}

QDate Report::getStart() const
{
    return start;
}

void Report::setStart(const QDate &value)
{
    start = value;
}

QDate Report::getEnd() const
{
    return end;
}

void Report::setEnd(const QDate &value)
{
    end = value;
}

void Report::setRecords(const std::list<record> &value)
{
    records = value;
}

std::list<record> Report::getRecords() const
{
    return records;
}
