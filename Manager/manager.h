#ifndef MANAGER_H
#define MANAGER_H
#include "report.h"
#include "managercontroller.h"
#include <QDate>
#include <QString>
#include <QMainWindow>
#include <QDebug>
#pragma execution_character_set("utf-8")

namespace Ui {
class Manager;
}

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr);
    ManagerController *managerController;
    ~Manager();

private:
    Ui::Manager *ui;
    //初始化UI界面
    void initUI();
    //连接信号槽函数
    void initConnect();

private slots:
    //查看报表
    void checkReport();
    //展示报表
    void showReport();
    //下载报表————考虑实现
    void download();
    //退出系统
    void quit();

signals:
    void quitSignal();
};

#endif // MANAGER_H
