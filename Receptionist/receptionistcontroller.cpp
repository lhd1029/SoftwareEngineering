#include "receptionistcontroller.h"

ReceptionistController::ReceptionistController()
{
    tm = new TCPClient();
    QJsonObject json;
    json.insert("Header", "init");
    json.insert("User", "receptionist");
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray msg = doc.toJson(QJsonDocument::Compact);
    tm->write(msg);
    QString strJson(msg);
    qDebug() << strJson;

    connect(tm, SIGNAL(sig_data_return(QByteArray)), this, SLOT(slotDealReturn(QByteArray)));
}


void ReceptionistController::check_in()
{
    // ask the server for a list of free roomID
    // (randomly) choose one and show it in the box
    // server should change the status of the room to occupied
    QJsonObject obj;
    obj.insert("Header", "request");
    obj.insert("User", "receptionist");
    obj.insert("Type", "checkin");
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray arr = doc.toJson(QJsonDocument::Compact);
    tm->write(arr);
    qDebug()<<arr;


}

void ReceptionistController::check_out(int roomID)
{
    // ask the server for a report
    // decode the report and show it in the box
    QJsonObject obj;
    obj.insert("Header", "request");
    obj.insert("User", "receptionist");
    obj.insert("Type", "checkout");
    obj.insert("roomID", QString::number(roomID));
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray arr = doc.toJson(QJsonDocument::Compact);
    tm->write(arr);
    qDebug() << arr;

}

void ReceptionistController::download_bill(int roomID)
{
    QJsonObject json;

    json.insert("Header", "request");  // header: request
    json.insert("User", "receptionist");  // user: receptionist
    json.insert("Type", "bill");  // type: bill
    json.insert("roomID", QString::number(roomID));
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray msg = doc.toJson(QJsonDocument::Compact);
    tm->write(msg);
    QString strJson(msg);
    qDebug() << strJson;
}

void ReceptionistController::download_list(int roomID)
{
    // TODO: just like get_bill()
    QJsonObject json;

    json.insert("Header", "request");  // header: request
    json.insert("User", "receptionist");  // user: receptionist
    json.insert("Type", "list");  // type: list
    json.insert("roomID", QString::number(roomID));
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray msg = doc.toJson(QJsonDocument::Compact);
    tm->write(msg);
    QString strJson(msg);
    qDebug() << strJson;

}


void ReceptionistController:: slotDealReturn(QByteArray msg)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(msg, &err);
    QJsonObject obj;
    qDebug() << "slt dealing return data";
    if (err.error == QJsonParseError::NoError && !doc.isNull())  // no error not null
    {
        obj = doc.object();
        if (obj.contains("checkin")) // check in msg
        {
            int roomID = obj.value("roomID").toInt();
            qDebug()<<"slot dealing checkin:";
            emit sig_get_checkin(roomID);
        }
        else if (obj.contains("checkout")) // check out msg
        {
            int roomID = obj.value("roomID").toInt();
            emit sig_get_checkout(roomID);
        }
        else if (obj.contains("bill"))  // bill msg
        {
            bill.roomID = obj.value("roomID").toInt();
            bill.checkInTime = QDateTime::fromString(obj.value("checkintime").toString());
            bill.checkOutTime = QDateTime::fromString(obj.value("checkouttime").toString());
            bill.payment = obj.value("payment").toDouble();
            emit sig_get_bill();
        }
        else if (obj.contains("list"))  // list msg
        {
            List list;
            int roomID = obj.value("roomID").toInt();
            list.roomID = roomID;
            QJsonArray arr = obj.value("list").toArray();

            for (auto i = 0; i <= arr.size(); i++)
            {
                QJsonObject listObj = arr[i].toObject();
                list.startTime.push_back(QDateTime::fromString(listObj.value("starttime").toString()));
                list.endTime.push_back(QDateTime::fromString(listObj.value("endtime").toString()));
                list.duration.push_back(listObj.value("duration").toInt());
                list.windSpeed.push_back(listObj.value("windspeed").toInt());
                list.rate.push_back(listObj.value("rate").toDouble());
                list.fee.push_back(listObj.value("fee").toDouble());
            }
            this->list = list;
            emit sig_get_list();
        }

    }
    else
    {
        qDebug() << "FAILED TO GET MSG FROM SERVER";
    }

}
