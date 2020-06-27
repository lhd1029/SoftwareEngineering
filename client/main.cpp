#include "client.h"
#include<iostream>
#include<vector>
//#include "pch.h"
#include<thread>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QString roomId, name, initialTemp;
//    QTextStream in(stdin);
//    in>>roomId>>name>>initialTemp;
//    Client *myClient = new Client("roomId", name, initialTemp.toDouble());
//    myClient->show();
     Client *myClient1 = new Client("101", "111", 32.0);
     myClient1->show();
//    Client *myClient2 = new Client("102", "222", 28.0);
//    myClient2->show();
//    Client *myClient3 = new Client("103", "333", 30.0);
//    myClient3->show();
//    Client *myClient4 = new Client("104", "444", 29.0);
//    myClient4->show();
//    Client *myClient5 = new Client("105", "555", 35.0);
//    myClient5->show();


    qDebug()<<"一个client创建完毕"<<endl;


    return a.exec();
}
