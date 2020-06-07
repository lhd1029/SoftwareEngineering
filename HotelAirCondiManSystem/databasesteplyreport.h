#ifndef DATABASESTEPLYREPORT_H
#define DATABASESTEPLYREPORT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class DatabaseSteplyReport//空调报表数据库
{
private:
    QSqlDatabase db;
public:
    DatabaseSteplyReport();
    bool connect();//连接数据库
    void disconnect();//连接数据库
    bool set_time(QString roomID, QString time);//设定空调状态修改的时间
    bool set_target_speed(QString roomID, int speed);//设定空调风速
    bool set_target_temp(QString roomID, double temperature);//设定空调温度
    bool set_cost(QString roomID, double cost);//设定空调某种状态的花费
    //花费cost的计算是通过SQL触发器写死还是在QT中先查询再计算没有想好，目前先搁置，留下此接口
    QString check_time(QString roomID);//查看空调状态修改的时间
    int check_target_speed(QString roomID);//查看空调风速
    double check_target_temperture(QString roomID);//查看空调温度
    double check_cost(QString roomID);//查看空调某种状态的花费
};

#endif // DATABASEREPORT_H
