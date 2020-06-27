#include "databasesteplyreport.h"
#include "globaldata.h"

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
bool DatabaseSteplyReport::set_time(int roomID, QString start_time)//设定空调某种状态的开始时间
{
    QString sql = "update airconditioner_steply_report set start_time = " + start_time + " where roomID = '" + QString::number(roomID) + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseSteplyReport::set_target_speed(int roomID, int speed)//设定空调某种状态的风速
{
    QString sql = "update airconditioner_steply_report set speed = " + QString::number(speed) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
bool DatabaseSteplyReport::set_target_temp(int roomID, double temperature)//设定空调某种状态的温度
{
    QString sql = "update airconditioner_steply_report set temperature = " + QString::number(temperature) + " where roomID = '" + roomID + "'";
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseSteplyReport::add_switch_report(int roomID, QDateTime time, double temp, int speed, int mode)
{
    qDebug()<<"bool DatabaseSteplyReport::add_switch_report"<<endl;
    QString sql = "insert into airconditioner_steply_report "
                  "values ('" + QString::number(roomID) + "', "
                    + time.toString("yyyyMMddhhmmss") + ", "
                    + "NULL, " + QString::number(temp) + ", "
                    + QString::number(speed) + ", "
                    + QString::number(mode) +")";
    qDebug()<<"sql: "<<sql<<endl;
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseSteplyReport::add_wind_report(int roomID, QDateTime time ,int speed)
{
    qDebug()<<"bool DatabaseSteplyReport::add_wind_report"<<endl;
    QString sql = "insert into airconditioner_steply_report (roomID,time,target_speed) "
                  "values ('" + QString::number(roomID) + "',"
                    + time.toString("yyyyMMddhhmmss") + ", "
                    + QString::number(speed) + ")";
//    qDebug()<<"sql: "<<sql<<endl;
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseSteplyReport::add_temp_report(int roomID, QDateTime time, double temp)
{
    qDebug()<<"bool DatabaseSteplyReport::add_temp_report"<<endl;
    QString sql = "insert into airconditioner_steply_report (roomID,time,target_temp) "
                  "values ('" + QString::number(roomID) + "',"
                    + time.toString("yyyyMMddhhmmss") + ", "
                    + QString::number(temp) + ")";
//    qDebug()<<"sql: "<<sql<<endl;
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}

bool DatabaseSteplyReport::add_mode_report(int roomID, QDateTime time, int mode)
{
    qDebug()<<"bool DatabaseSteplyReport::add_mode_report"<<endl;
    QString sql = "insert into airconditioner_steply_report (roomID,time,temp_mode) "
                  "values ('" + QString::number(roomID) + "',"
                    + time.toString("yyyyMMddhhmmss") + ", "
                    + QString::number(mode) + ")";
//    qDebug()<<"sql: "<<sql<<endl;
    QSqlQuery query;
    query.clear();
    return query.exec(sql);
}
//bool DatabaseSteplyReport::set_cost(int roomID, double cost)//设定空调某种状态的花费
//{
//    QString sql = "update airconditioner_report set cost = " + QString::number(cost) + " where roomID = '" + roomID + "'";
//    QSqlQuery query;
//    query.clear();
//    return query.exec(sql);
//}
//花费cost的计算是通过SQL触发器写死还是在QT中先查询再计算没有想好，目前先搁置，留下此接口
QString DatabaseSteplyReport::check_time(int roomID)//查看空调某种状态的开始时间
{
    QString sql = "select start_time from airconditioner_steply_report where roomID = '" + QString::number(roomID) + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toString();
    else
        return "-1";
}

int DatabaseSteplyReport::check_target_speed(int roomID)//查看空调某种状态的风速
{
    QString sql = "select speed from airconditioner_steply_report where roomID = '" + QString::number(roomID) + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toInt();
    else
        return -1;
}
double DatabaseSteplyReport::check_target_temperture(int roomID)//查看空调某种状态的温度
{
    QString sql = "select temperature from airconditioner_steply_report where roomID = '" + QString::number(roomID) + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toDouble();
    else
        return -1;
}
double DatabaseSteplyReport::check_cost(int roomID)//查看空调某种状态的花费
{
    QString sql = "select cost from airconditioner_steply_report where roomID = '" + QString::number(roomID) + "'";
    QSqlQuery query;
    query.clear();
    bool ret = query.exec(sql);
    query.next();
    if (ret != 0)
        return query.value(0).toDouble();
    else
        return -1;
}

QDateTime DatabaseSteplyReport::getCheckInTime(int roomID)
{
    QDateTime ret;
    QString sql = "select max(time) from airconditioner_steply_report "
                  "where roomID = '" + QString::number(roomID) + "' and occupied = 1";
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

QDateTime DatabaseSteplyReport::getCheckOutTime(int roomID)
{
    QDateTime ret;
    QString sql = "select max(time) from airconditioner_steply_report "
                  "where roomID = '" + QString::number(roomID) + "' and occupied = 0";
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

int DatabaseSteplyReport::getACUseTimes(int roomID, QString date)
{
    QString sql = "select count(*) from airconditioner_timely_report where roomID = '" + QString::number(roomID)
            + "' and time like " + "'" + date + "%' "+ " and target_temp = 0";
    QSqlQuery query;
    query.clear();
    if(query.exec(sql) && query.next() != NULL)
        return query.value(0).toInt();
    else {
        qDebug()<<"Get AC use times failed";
        return 0;
    }
}


//空调调温度次数
int DatabaseSteplyReport::getChangeTempTimes(int roomID, QString date)
{
    QString sql = "select count(*) from (select target_temp from airconditioner_timely_report where roomID = '" + QString::number(roomID)
            + "' and time like " + "'" + date + "%' ) as targetTemp";
    QSqlQuery query;
    if(!query.exec(sql)){
        qDebug()<<"Query change degree times failed";
        return 0;
    }
    if(query.next() == NULL){
        return 0;
    }
    return query.value(0).toInt();
}

//空调调风次数
int DatabaseSteplyReport::getChangeWindTimes(int roomID, QString date)
{
    QString sql = "select count(*) from ( select target_speed from airconditioner_timely_report where roomID = '"
            + QString::number(roomID) + "' and time like " + "'" + date + "%') as targetWind";
    QSqlQuery query;
    if(!query.exec(sql)){
        qDebug()<<"Query change wind times failed";
        return 0;
    }
    if(query.next() == NULL){
        return 0;
    }
    return query.value(0).toInt();
}

bool DatabaseSteplyReport::setCheckIn(int roomID, QString date)
{
    bool ret;
    QString sql = "insert into airconditioner_steply_report"
           " values(" + QString::number(roomID) + "," + date + ", 1, NULL, NULL, NULL)";
    QSqlQuery query;
    query.clear();
    ret = query.exec(sql);
    return ret;
}

bool DatabaseSteplyReport::setCheckOut(int roomID, QString date)
{
    bool ret;
    QString sql = "insert into airconditioner_steply_report"
           " values(" + QString::number(roomID) + "," + date + ", 0, NULL, NULL, NULL)";
    QSqlQuery query;
    query.clear();
    ret = query.exec(sql);
    return ret;
}

