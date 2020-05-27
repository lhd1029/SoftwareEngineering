#ifndef MANAGER_H
#define MANAGER_H
#include "report.h"
#include <QDate>
#include <QString>
#include <QMainWindow>

namespace Ui {
class Manager;
}

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr);
    ~Manager();

private:
    Ui::Manager *ui;
    Report *report;
    void initUI();
    void initConnect();
    void displayReport();

private slots:
    void clickCheckReport();//点击查看报表按钮
    void clickDwonload();
    void clickQuit();
};

#endif // MANAGER_H
