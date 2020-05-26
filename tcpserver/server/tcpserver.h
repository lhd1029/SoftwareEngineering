#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include "server.h"
namespace Ui {
class TcpServer;
}

class TcpServer : public QDialog
{
    Q_OBJECT
private:
    int port;
    Server *server;
public slots:
    void updateServer(QString,int);
    void slotUpdateServer(QString);
public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private:
    Ui::TcpServer *ui;
};

#endif // TCPSERVER_H
