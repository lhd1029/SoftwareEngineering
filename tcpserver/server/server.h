#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcpclientsocket.h"
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr,int port = 0);
    QList<tcpclientsocket*> tcpClientSocketList;
signals:
    void updateServer(QString,int);     //更新服务器显示内容信号
    void sigDisconnected(QString);      //断开连接信号
    void sigConnected(QString);         //连接信号
public slots:
    void slotDisconnected(int);
    void slotUpdateServer(QString,int);
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
