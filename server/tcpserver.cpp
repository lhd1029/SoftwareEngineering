 #include "tcpserver.h"
#include "ui_tcpserver.h"
#pragma execution_character_set("utf-8")
TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer)
{
    port = 8010;
    ui->setupUi(this);
    server = new Server(this,port);
    connect(server,SIGNAL(sigDisconnected(QByteArray)),this,SLOT(slotUpdateServer(QByteArray)));
    connect(server,SIGNAL(sigConnected(QByteArray)),this,SLOT(slotUpdateServer(QByteArray)));
    connect(server,SIGNAL(sigUpdateServer(QByteArray)),this,SLOT(slotUpdateServer(QByteArray)));
    qDebug()<<"连接槽成功"<<endl;
}

TcpServer::~TcpServer()
{
    delete ui;
}
void TcpServer::slotUpdateServer(QByteArray msg)
{
    ui->contentListWidget->addItem(msg);
    QJsonParseError e;
    QJsonDocument jsonDocNew = QJsonDocument::fromJson(msg, &e);

    if(e.error == QJsonParseError::NoError && !jsonDocNew.isNull())
    {
        QJsonObject getObj = jsonDocNew.object();
        ui->contentListWidget->addItem(QString(QJsonDocument(getObj).toJson()));
    }

}
