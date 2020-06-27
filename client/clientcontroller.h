#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H


#define RATIO_LOW_WIND 0.8  // 低风温度变化速率
#define RATIO_HIGH_WIND 1.2  // 高风温度变化速率
#define DELTA_TEMP_AC_ON 0.5  // 空调开启温度变化值
#define DELTA_TEMP_AC_OFF 0.5  // 空调关闭温度变化值
#define TIME_SLIDE 6000  // 更新温度费用时间

#include <QObject>
#include <QMessageBox>
#include <QTimerEvent>
#include <math.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

#include "slavemachine.h"
#include "tcpclient.h"

enum isOperation{none, automatic, manual};
enum operationType{no, isWind, isTemp, isSwitch, isMode};
enum errorType {tempNotAllowed, tcpFailed, roomInvalid};  // 错误类型

class ClientController : public QObject
{
    Q_OBJECT

public:
    explicit ClientController(SlaveMachine *sm, QObject *parent = nullptr);
    ~ClientController() override;
    void changeTemp(double tarTemp);
    void changeWind();
    void switchAC();
    void changeMode();
    void sendClientInfo();  // 表明客户端身份
    void sendMaster(isOperation who, operationType type);  // 发送请求或者更新状态
    void updateTemp();  // 计算温度
    void updatePayment();  // 计算费用
    void setRate(double newRate) {rate = newRate;}
    double getRate() {return rate;}
signals:
    void SignalInfoUpdated();  // 中央空调返回风速更新
    void SignalTimeOutUpdated();  // 定时状态更新
    void SignalErrorOccoured(errorType error);  // 出现错误
    void SignalCheckIn();
private slots:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    void slotDealReturn(QByteArray msg);  // 处理服务器返回信息
private:
    int minuteTimer;  // 一分钟计时器
    int secondTimer;  // 一秒钟定时器
    SlaveMachine *sm;  // 从控机
    TcpClient *tcpClient;  // 新增加的通信套接字
    QDateTime dateTime;
    bool waitFlag;   // 表明现在设置的温度是否需要等待上次设置1s后再发
    double rate;  // 一度电的电费
};

#endif // CLIENTCONTROLLER_H
