#include "mainwindow.h"
#include "client.h"
#include "admin.h"
#include "manager.h"
#include "receptionist.h"
#include "login.h"
#include "databasestatus.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Login l;

    l.show();
    //大家先按照这个设置好自己的槽函数，登录逻辑之后再实现
    return a.exec();
}
