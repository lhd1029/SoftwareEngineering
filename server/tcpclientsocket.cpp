#include "tcpclientsocket.h"

tcpclientsocket::tcpclientsocket(QObject *)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(slotDataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
void tcpclientsocket::slotDataReceived()
{
    QByteArray msg = read(1000);
    emit sigCommandReceived(msg,this->socketDescriptor());
}
void tcpclientsocket::slotDisconnected()
{
    emit sigDisconnected();
}


