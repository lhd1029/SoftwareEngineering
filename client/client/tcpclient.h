#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
class TcpClient:public QTcpSocket   //TcpClient以QTcpSocket作为基类，在默认构造函数中连接服务器
{
    Q_OBJECT
private:
    int port;
    QHostAddress *serverIP;
public:
    void virtual dataSend(QString msg);
public slots:
    void virtual dataReceived();//根据具体情况进行重写
public:
    explicit TcpClient();
    virtual ~TcpClient();

};

#endif // TCPCLIENT_H
