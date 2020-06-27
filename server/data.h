#ifndef DATA_H
#define DATA_H
#include <QTime>
#include "databasetimelyreport.h"
#include "databasesteplyreport.h"
#include "globaldata.h"
#include <iostream>
using namespace std;



class Data
{
public:
    Data();
    ~Data();


    static Bill getBill(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID);
    static List getList(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID);//获取一个房间的详单
    static ReportOne getReportOne(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID, QString date);
    //wait for owx
    static bool checkIn(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID, QString date);
    static bool checkOut(DatabaseTimelyReport dt, DatabaseSteplyReport ds, int roomID, QString date);
};


#endif // DATA_H
