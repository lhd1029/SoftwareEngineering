#ifndef DATABASESTATUS_H
#define DATABASESTATUS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class DatabaseStatus//空调状态数据库
{
private:
    QSqlDatabase db;
public:
    DatabaseStatus();
    bool connect();//连接数据库
    bool switch_state(QString roomID);//开关空调
    bool set_temperature(QString roomID, double temperature);//设定温度
    bool set_speed(QString roomID, int speed);//设定风速
    int check_state(QString roomID);//查看当前空调状态（开/关）
    double check_target_temperture(QString roomID);//查看目标温度
    int check_target_speed(QString roomID);//查看目标风速
    double check_current_temperture(QString roomID);//查看当前温度
    int check_current_speed(QString roomID);//查看当前风速
    double check_payment(QString roomID);
};

#endif // DATABASESTATUS_H
