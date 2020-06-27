#ifndef REPORT_H
#define REPORT_H
#include <QDate>
#include <list>

struct record{
    QDate date;
    QString roomId;
    int useACTimes;  //空调使用次数
    int changeDegreeTimes; //调温次数
    int changeWindTimes; //调风次数
    int dispathTimes; //被调度次数
    int detailRecordRows; //详单记录数
    double useACtime; //空调使用时长
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
