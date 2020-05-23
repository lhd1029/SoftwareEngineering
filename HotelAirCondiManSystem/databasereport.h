#ifndef DATABASEREPORT_H
#define DATABASEREPORT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class DatabaseReport//空调报表数据库
{
private:
    QSqlDatabase db;
public:
    DatabaseReport();
    bool connect();//连接数据库
    void disconnect();//连接数据库
    bool set_start_time(QString roomID, QString start_time);//设定空调某种状态的开始时间
    bool set_end_time(QString roomID, QString end_time);//设定空调某种状态的结束时间
    bool set_speed(QString roomID, int speed);//设定空调某种状态的风速
    bool set_temperature(QString roomID, double temperature);//设定空调某种状态的温度
    bool set_cost(QString roomID, double cost);//设定空调某种状态的花费
    //花费cost的计算是通过SQL触发器写死还是在QT中先查询再计算没有想好，目前先搁置，留下此接口
    QString check_start_time(QString roomID);//查看空调某种状态的开始时间
    QString check_end_time(QString roomID);//查看空调某种状态的结束时间
    int check_speed(QString roomID);//查看空调某种状态的风速
    double check_temperture(QString roomID);//查看空调某种状态的温度
    double check_cost(QString roomID);//查看空调某种状态的花费
};

#endif // DATABASEREPORT_H
