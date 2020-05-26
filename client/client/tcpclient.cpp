#include "tcpclient.h"
#include <QMessageBox>
#include <QHostInfo>
#pragma execution_character_set("utf-8")
TcpClient::TcpClient()
{
    port = 8010;
    serverIP = new QHostAddress();
    QString ip = "127.0.0.1";
    serverIP->setAddress(ip);
    connectToHost(*serverIP,port);                  //进行连接
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));//接收到数据时
}
void TcpClient::dataSend(QString msg)
{
    write(msg.toLatin1());
    qDebug()<<"发送给服务器的内容为："<<msg<<endl;
}

void TcpClient::dataReceived()
{
    while(bytesAvailable()>0){
        QByteArray datagram;
        datagram.resize(bytesAvailable());
        read(datagram.data(),datagram.size());
        QString msg = datagram.data();
        qDebug()<<"received data:"<<msg<<endl;
    }
}
TcpClient::~TcpClient()
{
    qDebug()<<"调用了析构函数"<<endl;
}
