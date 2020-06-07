#ifndef ADMIN_H
#define ADMIN_H
#include <admincontroller.h>
#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include "globaldata.h"

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private:
    Ui::Admin *ui;
    AdminController *adminController;
    QTimer *timer;
    int checkStateclicked; //判断管理员是否点击过查看状态按钮
    void initConnect();
    //初始化界面
    void initUI();
    //恢复空调系统配置
    void restorConfig();
    //配置可编辑
    void paraEditable(bool editable);

private slots:
    //检查状态
    void checkState();
    //更新状态
    void updateState();
    //改变空调状态
    void changeAirconState();
    //改变参数编辑状态
    void changeParaEditable();
    //关闭退出
    void quit();

signals:
    void quitSignal();
};

#endif // ADMIN_H
