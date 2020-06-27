#include "data.h"


Data::Data()
{

}

Bill Data::getBill(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID)
{


    Bill ret;

    ret.payment = dt.get_payment(roomID);
    qDebug()<<"Bill Data::getBill: "<<ret.payment<<endl;
    ret.roomID = roomID;

    ret.checkInTime = ds.getCheckInTime(roomID);
    ret.checkOutTime = ds.getCheckOutTime(roomID);


    return ret;
}

List Data::getList(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID)
{



    List ret;
    ret.roomID = roomID;
    dt.getList(roomID, &ret);


    return ret;
}

ReportOne Data::getReportOne(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID, QString date)
{



    ReportOne ret;
    ret.roomID = roomID;
    ret.ACUseTimes = ds.getACUseTimes(roomID, date);
    ret.ChangeTempTimes = ds.getChangeTempTimes(roomID, date);
    ret.ChangeWindTimes = ds.getChangeWindTimes(roomID, date);
    ret.ACdispatchedTimes = dt.getACdispatchedTimes(roomID, date);
    ret.ACUseTime = dt.getACUseTime(roomID, date);
    ret.detailedNum = dt.getListNum(roomID, date);


    return ret;
}

//wait for owx
bool Data::checkIn(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID, QString date)//办理入住，将occupied改为1
{

    ds.setCheckIn(roomID,date);

    return true;
}

bool Data::checkOut(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID, QString date)
{
    ds.setCheckOut(roomID,date);
    return true;
}

Data::~Data()
{

}
