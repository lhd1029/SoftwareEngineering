#include "tcpclient.h"

TCPClient::TCPClient()
{
    port = 8010;
    serverIP = new QHostAddress();
    QString ip = "127.0.0.1";
    serverIP->setAddress(ip);
    connectToHost(*serverIP, port);
    connect(this, SIGNAL(readyRead()),this, SLOT(sltReceivedData()));
}

void TCPClient::sltReceivedData()
{
    while(bytesAvailable()>0){
        QByteArray msg;
        msg = read(10000);
        emit sig_data_return(msg);
        qDebug() << "already emit sig data return";
        qDebug()<<msg<<endl;
    }
}



