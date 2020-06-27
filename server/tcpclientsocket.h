#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>   //新增
#include <QJsonDocument>//新增
#include <QJsonObject>//新增
class tcpclientsocket : public QTcpSocket     //监听到的套接字，使用此套接字进行发送和接收
{
    Q_OBJECT
public:
    tcpclientsocket(QObject *parent = nullptr);
signals:
    void sigDisconnected();
    void sigCommandReceived(QByteArray msg,int descriptor);//发送处理指令需要发送对应的描述符，这样才能确定是由哪一个发送的
protected slots:
    void slotDataReceived();//套接字接收消息后，发出sigCommandReceived信号，由server接收
    void slotDisconnected();//断开连接之后，发出sigDisconnected信号，由server接收
};

#endif // TCPCLIENTSOCKET_H
