#ifndef DATABASETIMELYREPORT_H
#define DATABASETIMELYREPORT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QTime>

class DatabaseTimelyReport
{
private:
    QSqlDatabase db;
public:
    DatabaseTimelyReport();
    bool connect();//连接数据库
    void disconnect();//连接数据库
    QDateTime get_time(QString roomID, int speed);//获取某种风速的使用时长
    double get_rate(QString roomID);//获取空调适用费率
    double get_payment(QString roomID);//获取空调应付金额
    bool update();
};

#endif // DATABASETIMELYREPORT_H
