#include "databasestatus.h"
#include <iostream>
DatabaseStatus::DatabaseStatus()
{
}
bool DatabaseStatus::connect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL SERVER};SERVER=.;DATABASE=Airconditioner");
    bool ret = db.open();
    return ret;
}
bool DatabaseStatus::switch_state(QString roomID)//开关空调
{
    QString sql = "update airconditioner_status set occupied = 1 - occupied where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseStatus::set_temperature(QString roomID, double temperature)//设定温度
{
    QString sql = "update airconditioner_status set target_temp = " + QString::number(temperature) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseStatus::set_speed(QString roomID, int speed)//设定风速
{
    QString sql = "update airconditioner_status set target_temp = " + QString::number(speed) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

int DatabaseStatus::check_state(QString roomID)//查看当前空调状态（开/关）
{
    QString sql = "select occupied from airconditioner_status where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toInt();
    else
        return -1;
}
double DatabaseStatus::check_target_temperture(QString roomID)//查看目标温度
{
    QString sql = "select target_temp from airconditioner_status where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toDouble();
    else
        return -1;
}
int DatabaseStatus::check_target_speed(QString roomID)//查看目标风速
{
    QString sql = "select target_speed from airconditioner_status where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toInt();
    else
        return -1;
}
double DatabaseStatus::check_current_temperture(QString roomID)//查看当前温度
{
    QString sql = "select current_temperature from airconditioner_status where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toDouble();
    else
        return -1;
}
int DatabaseStatus::check_current_speed(QString roomID)//查看当前风速
{
    QString sql = "select current_speed from airconditioner_status where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toInt();
    else
        return -1;
}
double DatabaseStatus::check_payment(QString roomID)
{
    QString sql = "select payment from airconditioner_status where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toDouble();
    else
        return -1;
}
