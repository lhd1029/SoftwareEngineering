#include "data.h"


Data::Data()
{

}

Bill Data::getBill(QString roomID)
{
    Bill ret;
    DatabaseTimelyReport dt;
    DatabaseSteplyReport ds;
    dt.connect();
    ret.payment = dt.get_payment(roomID);
    ret.roomID = roomID;
    dt.disconnect();
    ds.connect();
    ret.checkInTime = ds.getCheckInTime("a1");
    ret.checkOutTime = ds.getCheckOutTime("a1");
    ds.disconnect();
    std::cout << ret.checkInTime.toString().toStdString() << endl;
    std::cout << ret.checkOutTime.toString().toStdString() << endl;
    std::cout << ret.payment << endl;
    return ret;
}


Report Data::getReport(QDate start, QDate end)
{
    Report report;
    for(int i = 0; start.addDays(i) <= end; i++)
    {
        report.date.push_back(start.addDays(i));
        report.reportlist.push_back(getReportList(start.addDays(i).toString()));
    }
}

list<Reportlist> Data::getReportList(QString date)
{
    DatabaseTimelyReport dt;
    DatabaseSteplyReport ds;
    dt.connect();
    ds.connect();
    list<Reportlist> reportlist;
    Reportlist list;
    for(int j = 0; j < roomNum; j++)
    {
        list.roomId = QString::number(room[j]);
        list.totalmoney = dt.get_payment(list.roomId);
        list.getChangeWindTimes = ds.getChangeWindTimes(list.roomId, date);
        list.getChangeDegreeTimes = ds.getChangeTempTimes(list.roomId, date);
        list.dispathTimes = dt.getACdispatchedTimes(list.roomId, date);
        list.useACTime = dt.getACUseTime(list.roomId, date);
        //list.detailRecordRows = ; 从详单获取
        reportlist.push_back(list);
    }
    dt.disconnect();
    ds.disconnect();
    return reportlist;
}
