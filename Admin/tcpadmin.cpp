#include "tcpadmin.h"

TcpAdmin::TcpAdmin(QObject *parent)
{
    port = 8010;
    serverIP = new QHostAddress();
    QString ip = "127.0.0.1";
    serverIP->setAddress(ip);
    connectToHost(*serverIP, port);
    connect(this, SIGNAL(readyRead()),this, SLOT(slotReceivedData()));
}

void TcpAdmin::slotReceivedData()
{
    while(bytesAvailable()>0){
        QByteArray msg;
        msg = read(10000);
        qDebug()<<msg<<endl;
        emit sigDataReturn(msg);
    }
}
