#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "QJsonArray"
#include "QJsonParseError"
#include "QJsonObject"
#include "QJsonDocument"
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QHostInfo>
#include <QDate>

class TCPClient : public QTcpSocket
{
    Q_OBJECT
public:
    TCPClient();
    //int sendMessage(int roodID, QDateTime start, QDateTime end);
private:
    int port;
    QHostAddress *serverIP;

signals:
    void sig_data_return(QByteArray);

public slots:
    void sltReceivedData();
};


#endif // TCPCLIENT_H
