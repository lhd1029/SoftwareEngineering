#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include<iostream>

#include <QDebug>

#include "clientcontroller.h"


namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QString roomId = "101", QString userName = "abc", double initialTemp = 30.0,  QWidget *parent = nullptr);
    ~Client();

    void showCurWind(windSpeed wind);
    void showTarWind(windSpeed wind);
    void showState();
    void showMode();  //  展现模式



private slots:
    void onInfoUpdated();  // 定时更新界面所有信息
    void onErrorOccoured(errorType error);  // 错误发生提示
    void on_pushButton_temperature_up_2_clicked();  // 升温
    void on_pushButton_temperature_down_2_clicked();  // 降温
    void on_pushButton_switch_2_clicked();  // 开关按钮
    void on_pushButton_speed_up_2_clicked();  // 增加风速
    void on_pushButton_speed_down_2_clicked();  // 减小风速
    void on_radioButton_set_mode_cold_clicked();  // 制冷模式
    void on_radioButton_set_mode_heat_clicked();  // 制热模式

private:
    Ui::Client *ui;  // UI
    ClientController *cc;  // 控制器
    SlaveMachine *sm;  // 从控端


};

#endif // CLIENT_H
