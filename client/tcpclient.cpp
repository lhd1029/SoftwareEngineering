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
    connectToHost(*serverIP, port);                  //进行连接
    connect(this,SIGNAL(readyRead()),this,SLOT(slotDataReceived()));//接收到数据时
}

void TcpClient::slotDataReceived()
{
    while(bytesAvailable()>0){
        QByteArray msg;
        msg = read(10000);
        emit sigDataReturn(msg);
        qDebug()<<msg<<endl;
    }
}
TcpClient::~TcpClient()
{
    qDebug()<<"调用了析构函数"<<endl;
}
