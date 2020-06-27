#ifndef TCPMANAGER_H
#define TCPMANAGER_H
#include "QJsonArray"
#include "QJsonParseError"
#include "QJsonObject"
#include "QJsonDocument"
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QHostInfo>
#include <QDate>
#include <QObject>

class TcpManager : public QTcpSocket
{
    Q_OBJECT

public:
    TcpManager();
private:
    int port;
    QHostAddress *serverIP;

signals:
    void sigDataReturn(QByteArray);

public slots:
    void slotReceivedData();
};

#endif // TCPMANAGER_H
