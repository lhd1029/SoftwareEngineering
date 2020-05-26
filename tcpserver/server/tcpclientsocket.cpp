#include "tcpclientsocket.h"
#pragma execution_character_set("utf-8")
tcpclientsocket::tcpclientsocket(QObject *)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
void tcpclientsocket::dataReceived()
{
    qDebug()<<bytesAvailable()<<endl;
    while(bytesAvailable()>0){
        int length = int(bytesAvailable());
        char buf[1024];
        read(buf,length);
        QString msg = buf;
        qDebug()<<buf<<endl;
    }
}
void tcpclientsocket::slotDisconnected()
{
    qDebug()<<"句柄为："<<this->socketDescriptor()<<endl;
    emit disconnected(this->socketDescriptor());//socketDescriptor(),socket描述符
}
