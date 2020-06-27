#ifndef DATABASESTEPLYREPORT_H
#define DATABASESTEPLYREPORT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QTime>
#include <QDebug>

class DatabaseSteplyReport//空调报表数据库
{
private:
    QSqlDatabase db;
public:
    DatabaseSteplyReport();
    bool connect();//连接数据库
    void disconnect();//连接数据库
    bool set_time(int roomID, QString time);//设定空调状态修改的时间
    bool set_target_speed(int roomID, int speed);//设定空调风速
    bool set_target_temp(int roomID, double temperature);//设定空调温度
    bool set_cost(int roomID, double cost);//设定空调某种状态的花费
    //花费cost的计算是通过SQL触发器写死还是在QT中先查询再计算没有想好，目前先搁置，留下此接口
    bool add_switch_report(int roomID, QDateTime time, double temp, int speed, int mode);
    bool add_wind_report(int roomID, QDateTime time, int speed);//增加设置风速记录
    bool add_temp_report(int roomID, QDateTime time, double temp);//增加设置温度记录
    bool add_mode_report(int roomID, QDateTime time, int mode);//增加设置模式记录
    QString check_time(int roomID);//查看空调状态修改的时间
    int check_target_speed(int roomID);//查看空调风速
    double check_target_temperture(int roomID);//查看空调温度
    double check_cost(int roomID);//查看空调某种状态的花费
    int getChangeTempTimes(int roomID, QString date);//空调调温次数
    int getChangeWindTimes(int roomID, QString date);//空调调风次数
    int getACUseTimes(int roomID, QString date);//空调使用次数

    QDateTime getCheckInTime(int roomID);
    QDateTime getCheckOutTime(int roomID);
    bool setCheckIn(int roomID, QString date);//更改房间使用状态（不是空调）为已使用
    bool setCheckOut(int roomID, QString date);//更改房间使用状态（不是空调）为未使用

};

#endif // DATABASEREPORT_H
