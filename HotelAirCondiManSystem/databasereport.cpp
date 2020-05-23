#include "databasereport.h"

DatabaseReport::DatabaseReport()
{

}
bool DatabaseReport::connect()//连接数据库
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL SERVER};SERVER=.;DATABASE=Airconditioner");
    return db.open();
}
void DatabaseReport::disconnect()//连接数据库
{
    db.close();
}
bool DatabaseReport::set_start_time(QString roomID, QString start_time)//设定空调某种状态的开始时间
{
    QString sql = "update airconditioner_report set start_time = " + start_time + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
bool DatabaseReport::set_end_time(QString roomID, QString end_time)//设定空调某种状态的结束时间
{
    QString sql = "update airconditioner_report set end_time = " + end_time + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
bool DatabaseReport::set_speed(QString roomID, int speed)//设定空调某种状态的风速
{
    QString sql = "update airconditioner_report set speed = " + QString::number(speed) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
bool DatabaseReport::set_temperature(QString roomID, double temperature)//设定空调某种状态的温度
{
    QString sql = "update airconditioner_report set temperature = " + QString::number(temperature) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
//bool DatabaseReport::set_cost(QString roomID, double cost)//设定空调某种状态的花费
//{
//    QString sql = "update airconditioner_report set cost = " + QString::number(cost) + " where roomID = '" + roomID + "'";
//    QSqlQuery query;
//    query.clear();
//    return query.exec(sql);
//}
//花费cost的计算是通过SQL触发器写死还是在QT中先查询再计算没有想好，目前先搁置，留下此接口
QString DatabaseReport::check_start_time(QString roomID)//查看空调某种状态的开始时间
{
    QString sql = "select start_time from airconditioner_report where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toString();
    else
        return "-1";
}
QString DatabaseReport::check_end_time(QString roomID)//查看空调某种状态的结束时间
{
    QString sql = "select end_time from airconditioner_report where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toString();
    else
        return "-1";
}
int DatabaseReport::check_speed(QString roomID)//查看空调某种状态的风速
{
    QString sql = "select speed from airconditioner_report where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toInt();
    else
        return -1;
}
double DatabaseReport::check_temperture(QString roomID)//查看空调某种状态的温度
{
    QString sql = "select temperature from airconditioner_report where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toDouble();
    else
        return -1;
}
double DatabaseReport::check_cost(QString roomID)//查看空调某种状态的花费
{
    QString sql = "select cost from airconditioner_report where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toDouble();
    else
        return -1;
}
