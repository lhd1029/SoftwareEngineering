#ifndef RECEPTIONISTCONTROLLER_H
#define RECEPTIONISTCONTROLLER_H

#include <QString>
#include <QDateTime>
#include "tcpclient.h"
#include "globaldata.h"

class ReceptionistController : public QObject
{
    Q_OBJECT
public:
    ReceptionistController();
    void check_in();
    void check_out(int roomID);
    void download_bill(int roomID);  // undefined return value
    void download_list(int roomID);  //
    List list;
    Bill bill;


public slots:
    void slotDealReturn(QByteArray msg);


private:
    TCPClient *tm;

signals:
    void sig_get_bill();
    void sig_get_list();
    void sig_get_checkin(int);
    void sig_get_checkout(int);

};

#endif // RECEPTIONISTCONTROLLER_H
