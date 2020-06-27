#include "databasetimelyreport.h"
#include "globaldata.h"
#include <iostream>
#include <QTextStream>
using namespace std;
DatabaseTimelyReport::DatabaseTimelyReport()
{

}
bool DatabaseTimelyReport::connect()//连接数据库
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL SERVER};SERVER=.;DATABASE=Airconditioner");
    return db.open();
}

void DatabaseTimelyReport::disconnect()//连接数据库
{
    db.close();
}

QDateTime DatabaseTimelyReport::get_time(int roomID, int speed) //3是高，2是中，1是低
{
    QDateTime ret;
    QString sql = "select count(time) from airconditioner_timely_report \
where time >= \
(select max(time) from airconditioner_steply_report \
where roomID = '" + QString::number(roomID) + "' and occupied = 1) \
and cur_speed = '" + QString::number(speed) + "'";
    QSqlQuery query;
    query.clear();
    bool result = query.exec(sql);
    int total = 0;
    if (result)
    {
        query.next();
        total = query.value(0).toInt();
    }
    int second = total % 60;
    total = (int)((total-second)/60);
    int minute = total % 60;
    total = (int)((total-minute)/60);
    int hour = total % 60;
    total = (int)((total-hour)/24);
    int day = total % 24;
    QString time_;
    QTextStream(&time_) << day << " "<< hour << ":" << minute << ":" << second;
    ret = QDateTime::fromString(time_,"dd hh:mm:ss");
//    cout << time_high.toStdString();
    return ret;
}

bool DatabaseTimelyReport::update(ClientState *cs, double rate)//更新数据库
{
    if (cs == nullptr)
        qDebug()<<"kong"<<endl;
    qDebug()<<"bool DatabaseTimelyReport::update(ClientState *cs)//更新数据库"<<endl;
    qDebug()<<cs->get_roomId()<<cs->get_time().toString("yyyyMMddhhmmss")<<cs->get_is_open()<<endl;
    bool result = true;
    QSqlQuery query;
    query.clear();
    QString sql = "insert into airconditioner_timely_report "
         "values ('" + QString::number(cs->get_roomId()) + "', "
          + cs->get_time().toString("yyyyMMddhhmmss") + ", "
          + QString::number(cs->get_is_open()) + ", "
          + QString::number(rate) + ", "
          + QString::number(cs->get_cur_temp()) + ", "
          + QString::number(cs->get_cur_speed()) + ", "
          + QString::number(cs->get_target_temp()) + ", "
          + QString::number(cs->get_target_speed()) + ", "
          + QString::number(cs->get_payment()) + ", "
          + QString::number(cs->get_status()) + ")";
        qDebug()<<"sql"<<sql<<endl;
        query.clear();
        qDebug()<<"sql"<<sql<<endl;
        result = result && query.exec(sql);

    return result;
}

double DatabaseTimelyReport::get_rate(int roomID)//获取空调适用费率
{
    QString sql = "select rate from airconditioner_timely_report\
where roomID = '" + QString::number(roomID) + " and time = \
(select max(time) from airconditioner_timely_report\
where roomID = '" + QString::number(roomID) + "')";
    QSqlQuery query;
    query.clear();
    bool result1 = query.exec(sql);
    if (result1)
    {
        return query.value(0).toDouble();
    }
    else
    {
        return result1;
    }
}

double DatabaseTimelyReport::get_payment(int roomID)//获取空调应付金额
{
    QString sql = "select payment from airconditioner_timely_report\
        where roomID = '" + QString::number(roomID) + "' and time = \
        (select max(time) from airconditioner_timely_report\
        where roomID = '" + QString::number(roomID) + "')";
//    qDebug()<<"sqlget_payment"<<sql<<endl;
    QSqlQuery query;
    query.clear();
    bool result1 = query.exec(sql);
    query.next();
    if (result1)
    {
        return query.value(0).toDouble();
    }
    else
    {
        return result1;
    }
}

//获取房间使用空调时间
double DatabaseTimelyReport::getACUseTime(int roomID, QString date)
{
    QString sql = "select count(*) from airconditioner_timely_report where roomID = '" + QString::number(roomID)
                + "' and time like " + "'" + date + "%' " + "and status = " + QString::number(RUNNING);
    QSqlQuery query;
    if(!query.exec(sql)){
        return 0;
        qDebug()<<"Query get AC use time failed";
    }
    else{
        if(query.next() == NULL){
            return 0;
        }
        else {
            return query.value(0).toDouble();
        }
    }
}

//获取空调被调度次数
int DatabaseTimelyReport::getACdispatchedTimes(int roomID, QString date)
{
    QString sql = "select status, time from airconditioner_timely_report where roomID = '" + QString::number(roomID)
                + "' and time like " + "'" + date + "%' " + "order by time asc";
    QSqlQuery query;
    if(!query.exec(sql))
    {
        qDebug()<<"Query get patched times failed";
        return 0;
    }

    int times=0, flag=0;
    while(query.next()){
        if(query.value(0) == RUNNING)
            if(!flag){//之前没被调度，现在处于正在运行，说明被调度
                times++;
                flag = 1;
            }
            else {}
        else
            flag = 0;//没被调度
    }
    return times;
}

bool DatabaseTimelyReport::getList(int roomID, List* ret)
{
    QString sql = "select time, cur_speed, rate, payment from airconditioner_timely_report "
            "where time >= ("
           "select max(time) from airconditioner_steply_report "
            "where occupied = 1)"
            "and roomID = '" + QString::number(roomID) + "'";
    QSqlQuery query;
    query.clear();
    bool result1 = query.exec(sql);
    if (result1)
    {
        if(query.next() == NULL){
            qDebug() << "query failed!" << endl;
            return false;
        }
        double startFee = 0.0, endFee = 0.0;
        int lastWind = query.value(1).toInt();
        QDateTime lastTime = QDateTime::fromString(query.value(0).toString(), "yyyyMMddhhmmss");
        if (lastWind != 0)
        {
            startFee = query.value(3).toDouble();
            ret->startTime.push_back(lastTime);
        }
        int currentWind = lastWind;
        QDateTime currentTime = lastTime;
        double currentRate;
        while(query.next()){
            currentRate = query.value(2).toInt();
            currentWind = query.value(1).toInt();
            currentTime = QDateTime::fromString(query.value(0).toString(), "yyyyMMddhhmmss");
            endFee = query.value(3).toDouble();
            if(lastWind != currentWind){
                if (lastWind != 0)//表示送风结束
                {
                    ret->fee.push_back(endFee-startFee);
                    ret->endTime.push_back(lastTime);
                }
                if (currentWind != 0)//表示送风开始
                {
                    startFee = query.value(3).toDouble();
                    ret->startTime.push_back(currentTime);
                    ret->windSpeed.push_back(currentWind);
                    ret->rate.push_back(currentRate);
                }
            }
            lastWind = currentWind;
            lastTime = currentTime;
        }
        if (currentWind != 0)
        {
            ret->fee.push_back(endFee-startFee);
            ret->endTime.push_back(currentTime);
        }

        long long length = ret->startTime.size();
        for (long long i = 0; i < length; i++) {
            int duration = ret->startTime[i].secsTo(ret->endTime[i])+1;
            ret->duration.push_back(duration);
        }
    }
}

int DatabaseTimelyReport::getListNum(int roomID, QString date)//date是天数
{
    int ret = 0;
    QString sql = "select time, cur_speed from airconditioner_timely_report "
            "where time like '" + date + "%'"
            "and roomID = '" + QString::number(roomID) + "'";
    QSqlQuery query;
    query.clear();
    bool result1 = query.exec(sql);
    if (result1)
    {
        if(query.next() == NULL){
            return 0;
        }
        int lastWind = query.value(1).toInt();
        if (lastWind != 0)
        {
            ret++;
        }
        int currentWind = 0;
        while(query.next()){
            currentWind = query.value(1).toInt();
            if(lastWind != currentWind){
                ret++;
            }
            lastWind = currentWind;
        }
        if (currentWind != 0)
        {
            ret++;
        }
    }
    return ret;
}
