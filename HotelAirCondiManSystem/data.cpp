#include "data.h"


Data::Data()
{

}

Bill Data::getBill(QString roomID)
{
    Bill ret;
    DatabaseTimelyReport d;
    d.connect();
    ret.using_time_high = d.get_time(roomID, 3);
    ret.using_time_medium = d.get_time(roomID, 2);
    ret.using_time_low = d.get_time(roomID, 1);
    ret.rate = d.get_rate(roomID);
    ret.payment = d.get_payment(roomID);
    return ret;
}
