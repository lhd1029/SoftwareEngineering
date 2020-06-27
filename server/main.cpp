#include "tcpserver.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer w;
    qDebug()<<"连接成功";

    w.show();

    return a.exec();
}
