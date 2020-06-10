#include "databasetimelyreport.h"
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

QDateTime DatabaseTimelyReport::get_time(QString roomID, int speed) //3是高，2是中，1是低
{
    QDateTime ret;
    QString sql = "select count(time) from airconditioner_timely_report \
where time >= \
(select max(time) from airconditioner_steply_report \
where roomID = '" + roomID + "' and occupied = 1) \
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

bool DatabaseTimelyReport::update()//更新数据库
{
    for (int i = 0; i < 100; i++)
    {
        QString sql = "select payment, rate from airconditioner_timely_report\
where roomID = '" + QString::fromStdString("a1") + " and time = \
(select max(time) from airconditioner_timely_report\
where roomID = '" + QString::fromStdString("a1") + "')";
        QSqlQuery query;
        query.clear();
        bool result1 = query.exec(sql);
        double payment = 0.0;
        double rate = 1.0;//默认1元/度
//        if (result1)
//        {
//            query.next();
//            payment = query.value(0).toDouble();
//            rate = query.value(1).toDouble();
//            payment += 1/(60*(4-curspeed)) * rate;//3是高，2是中，1是低
//        }
//        sql = "insert into airconditioner_timely_report"
//              "values ('" + QString::fromStdString("a1") + "', "
//                + QString::number(time_) + ", "
//                + QString::number(is_open) + ", "
//                + QString::number(cur_temp) + ", "
//                + QString::number(cur_speed) + ", "
//                + QString::number(target_temp) + ", "
//                + QString::number(target_speed) + ", "
//                + QString::number(payment) + ")";
        query.clear();
        bool result2 = query.exec(sql);
        return (result1 && result2);
    }

}
double DatabaseTimelyReport::get_rate(QString roomID)//获取空调适用费率
{
    QString sql = "select rate from airconditioner_timely_report\
where roomID = '" + QString::fromStdString("a1") + " and time = \
(select max(time) from airconditioner_timely_report\
where roomID = '" + QString::fromStdString("a1") + "')";
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

double DatabaseTimelyReport::get_payment(QString roomID)//获取空调应付金额
{
    QString sql = "select payment from airconditioner_timely_report\
where roomID = '" + roomID + " and time = \
(select max(time) from airconditioner_timely_report\
where roomID = '" + roomID + "')";
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

//获取房间使用空调时间
double DatabaseTimelyReport::getACUseTime(QString roomID, QString date)
{
    QString sql = "select count(*) from airconditioner_status where roomID = '" + roomID
                + "' and time like " + "'" + date + "% '" + "and status = " + QString::number(RUNNING);
    QSqlQuery query;
    if(!query.exec(sql))
        qDebug()<<"Query get AC use time failed";
    return query.value(0).toDouble();
}

int DatabaseTimelyReport::getACdispatchedTimes(QString roomID, QString date)
{
    QString sql = "select status, time from airconditioner_status where roomID = '" + roomID
                + "' and time like " + "'" + date + "% '" + "order by time asc";
    QSqlQuery query;
    if(!query.exec(sql))
        qDebug()<<"Query get patched times failed";
    int times=0, flag=0;
    int currentStatus;
    while(query.next()){
        if(query.value(0).toInt() == RUNNING)
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
