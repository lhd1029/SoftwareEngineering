#ifndef TCPADMIN_H
#define TCPADMIN_H

#include <QObject>
#include "QJsonArray"
#include "QJsonParseError"
#include "QJsonObject"
#include "QJsonDocument"
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QHostInfo>
#include <QDate>

class TcpAdmin : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpAdmin(QObject *parent = nullptr);

private:
    int port;
    QHostAddress *serverIP;

signals:
    void sigDataReturn(QByteArray);

public slots:
    void slotReceivedData();
};

#endif // TCPADMIN_H
