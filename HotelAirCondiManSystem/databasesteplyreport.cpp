#include "databasesteplyreport.h"

DatabaseSteplyReport::DatabaseSteplyReport()
{

}
bool DatabaseSteplyReport::connect()//连接数据库
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL SERVER};SERVER=.;DATABASE=Airconditioner");
    return db.open();
}
void DatabaseSteplyReport::disconnect()//断开数据库
{
    db.close();
}
bool DatabaseSteplyReport::set_time(QString roomID, QString start_time)//设定空调某种状态的开始时间
{
    QString sql = "update airconditioner_report set start_time = " + start_time + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseSteplyReport::set_target_speed(QString roomID, int speed)//设定空调某种状态的风速
{
    QString sql = "update airconditioner_report set speed = " + QString::number(speed) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
bool DatabaseSteplyReport::set_target_temp(QString roomID, double temperature)//设定空调某种状态的温度
{
    QString sql = "update airconditioner_report set temperature = " + QString::number(temperature) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
//bool DatabaseSteplyReport::set_cost(QString roomID, double cost)//设定空调某种状态的花费
//{
//    QString sql = "update airconditioner_report set cost = " + QString::number(cost) + " where roomID = '" + roomID + "'";
//    QSqlQuery query;
//    query.clear();
//    return query.exec(sql);
//}
//花费cost的计算是通过SQL触发器写死还是在QT中先查询再计算没有想好，目前先搁置，留下此接口
QString DatabaseSteplyReport::check_time(QString roomID)//查看空调某种状态的开始时间
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

int DatabaseSteplyReport::check_target_speed(QString roomID)//查看空调某种状态的风速
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
double DatabaseSteplyReport::check_target_temperture(QString roomID)//查看空调某种状态的温度
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
double DatabaseSteplyReport::check_cost(QString roomID)//查看空调某种状态的花费
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

QDateTime DatabaseSteplyReport::getCheckInTime(QString roomID)
{
    QDateTime ret;
    QString sql = "select max(time) from airconditioner_steply_report "
                  "where roomID = '" + roomID + "' and occupied = 1";
    QSqlQuery query;
    query.clear();
    bool result = query.exec(sql);
    if (result != 0)
    {
        query.next();
        QString qtime = query.value(0).toString();
        ret = QDateTime::fromString(qtime,"yyyyMMddhhmmss");
    }
    return ret;
}

QDateTime DatabaseSteplyReport::getCheckOutTime(QString roomID)
{
    QDateTime ret;
    QString sql = "select max(time) from airconditioner_steply_report "
                  "where roomID = '" + roomID + "' and occupied = 2";
    QSqlQuery query;
    query.clear();
    bool result = query.exec(sql);
    if (result != 0)
    {
        query.next();
        QString qtime = query.value(0).toString();
        ret = QDateTime::fromString(qtime,"yyyyMMddhhmmss");
    }
    return ret;
}

//空调调温度次数
int DatabaseSteplyReport::getChangeTempTimes(QString roomID, QString date)
{
    QString sql = "select target_temp, time from airconditioner_timely_report where roomID = '" + roomID
            + "' and time like " + "'" + date + "% '"+ "order by time asc";
    QSqlQuery query;
    if(!query.exec(sql))
        qDebug()<<"Query change degree times failed";
    int times=1;//开启空调时，算一次调节温度
    double lastTemp = query.value(0).toDouble();
    double currentTemp;
    while(query.next()){
        currentTemp = query.value(0).toDouble();
        if(abs(currentTemp - lastTemp) > 0.01){
            times++;//调节温度了
            lastTemp = currentTemp;
        }
    }
    return times;
}

//空调调风次数
int DatabaseSteplyReport::getChangeWindTimes(QString roomID, QString date)
{
    QString sql = "select target_wind, time from airconditioner_timely_report where roomID = '" + roomID
            + "' and time like " + "'" + date + "% '"+ "order by time asc";
    QSqlQuery query;
    if(!query.exec(sql))
        qDebug()<<"Query change degree times failed";
    int times=1;//开启空调时，第一次调节风速
    int lastWind = query.value(0).toInt();
    int currentWind;
    while(query.next()){
        currentWind = query.value(0).toInt();
        if(currentWind != lastWind){
            times++;//调节温度了
            lastWind = currentWind;
        }
    }
    return times;
}
