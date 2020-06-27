#ifndef DATABASETIMELYREPORT_H
#define DATABASETIMELYREPORT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QTime>
#include <QDebug>
#include <vector>
#include <clientstate.h>
#include "globaldata.h"


class DatabaseTimelyReport
{
private:
    QSqlDatabase db;
public:
    DatabaseTimelyReport();
    bool connect();//连接数据库
    void disconnect();//连接数据库
    QDateTime get_time(int roomID, int speed);//获取某种风速的使用时长
    double get_rate(int roomID);//获取空调适用费率
    double get_payment(int roomID);//获取空调应付金额
    bool update(ClientState *cs, double rate);
    //report（统计报表）部分
    double getACUseTime(int roomID, QString date);
    int getACdispatchedTimes(int roomID, QString date);
    //list（详单）部分
    bool getList(int roonID, List* ret);
    int getListNum(int roomID, QString date);
};

#endif // DATABASETIMELYREPORT_H
