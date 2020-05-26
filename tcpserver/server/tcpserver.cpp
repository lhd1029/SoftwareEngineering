#include "tcpserver.h"
#include "ui_tcpserver.h"

TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer)
{
    port = 8010;
    ui->setupUi(this);
    server = new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));
    connect(server,SIGNAL(sigDisconnected(QString)),this,SLOT(slotUpdateServer(QString)));
    connect(server,SIGNAL(sigConnected(QString)),this,SLOT(slotUpdateServer(QString)));
    qDebug()<<"连接槽成功"<<endl;
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::updateServer(QString msg,int length)
{
    qDebug()<<"进入到更新服务器显示阶段，传入的msg为："<<msg<<endl;
    ui->contentListWidget->addItem(msg.left(length));
}
void TcpServer::slotUpdateServer(QString msg)
{
    qDebug()<<"进入到更新服务器显示阶段，传入的msg为："<<msg<<endl;
    ui->contentListWidget->addItem(msg);
}

