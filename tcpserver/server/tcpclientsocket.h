#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
class tcpclientsocket : public QTcpSocket     //监听到的套接字，使用此套接字进行发送和接收
{
    Q_OBJECT
public:
    tcpclientsocket(QObject *parent = nullptr);
    int socket;//保存描述符
signals:
    void disconnected(int);//发送断开连接后的描述符
protected slots:
    void virtual dataReceived();//用于之后数据交互，子类可以重写此方法，接收后处理接收的数据，根据格式，内容，再写入，还需增加处理功能
    void slotDisconnected();//断开连接之后，发送描述符，便于在server中的列表进行连接删除
};

#endif // TCPCLIENTSOCKET_H
