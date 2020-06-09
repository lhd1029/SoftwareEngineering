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
