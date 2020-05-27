#ifndef CLIENT_H
#define CLIENT_H
#define MAX_TEMP 30
#define MIN_TEMP 18
#define MAX_WIND 3
#define MIN_WIND 1
#define NO_WIND 0
#define DEFAULT_WIND 0
#define DEFAULT_TAR_TEMP 25.0
#define RATIO_LOW_WIND 0.8
#define RATIO_HIGH_WIND 1.2
#define DELTA_TEMP_AC_ON 0.5
#define DELTA_TEMP_AC_OFF 0.5

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <math.h>
#include "clientcontroller.h"
namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(int roomId = 0, std::string userName = "", QWidget *parent = nullptr);
    ~Client();
    void showCurWind(int wind);
    void showTarWind(int wind);


private slots:
    /* 升温 */
    void on_pushButton_temperature_up_2_clicked();
    /* 降温 */
    void on_pushButton_temperature_down_2_clicked();
    /* 开关按钮 */
    void on_pushButton_switch_2_clicked();
    /* 增加风速 */
    void on_pushButton_speed_up_2_clicked();
    /* 减小风速 */
    void on_pushButton_speed_down_2_clicked();
    /* 定时器 */
    void onTimerOut();
    /* 基于优先级和时间片调度结果返回 */
    void onWindUpdated();

private:
    Ui::Client *ui;
    ClientController *cc;
    int roomId;
    std::string userName;
    bool ACState;
    double curTemp;
    double tarTemp;
    double initialTemp;
    int curWind;
    int tarWind;
    int mode;  // 模式:0制冷/1制热
    double payment;
    QTimer *timer;
};

#endif // CLIENT_H
