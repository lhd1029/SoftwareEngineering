#include "server.h"
#pragma execution_character_set("utf-8")
Server::Server(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any,port);//监听任意
    qDebug()<<"port:"<<port<<endl;
}
void Server::incomingConnection(qintptr socketDescriptor)
{
    tcpclientsocket *tcpClientSocket = new tcpclientsocket(this);//一旦接收就创建一个与客户端通信的socket
    tcpClientSocket->setSocketDescriptor(socketDescriptor);//保存其句柄
    tcpClientSocket->socket = socketDescriptor;
    tcpClientSocketList.append(tcpClientSocket);
    QString msg =QString::number(tcpClientSocket->socketDescriptor())+tr(" connected successfully");//建立成功连接消息
    emit sigConnected(msg);//发送信号给tcpServer界面
    qDebug()<<"句柄为:"<<tcpClientSocket->socketDescriptor()<<endl;
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));//如果客户端断开，要和服务器说明白,将其内部套接字列表中对应套接字删除
    qDebug()<<tcpClientSocketList.size()<<endl;

}
void Server::slotUpdateServer(QString msg,int length)
{
    emit updateServer(msg,length);
}
void Server::slotDisconnected(int descriptor)
{
    qDebug()<<"要被删除的句柄"<<descriptor<<endl;
    for(int i=0;i<tcpClientSocketList.size();i++){
        tcpclientsocket *item = tcpClientSocketList[i];
        if(item->socketDescriptor()==descriptor){
            qDebug()<<item->socket<<"断开连接"<<endl;
            QString msg = QString::number(item->socket)+" disconnected";
            emit sigDisconnected(msg);
            tcpClientSocketList.removeAt(i);            
            qDebug()<<"删除后列表大小："<<tcpClientSocketList.size()<<endl;
            return;
        }
    }
    return;
}
