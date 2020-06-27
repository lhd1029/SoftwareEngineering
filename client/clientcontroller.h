#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H


#define RATIO_LOW_WIND 0.8
#define RATIO_HIGH_WIND 1.2
#define DELTA_TEMP_AC_ON 0.5
#define DELTA_TEMP_AC_OFF 0.5


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
enum errorType {tempNotAllowed,tcpFailed};  // 错误类型
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

private slots:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
//    void onTimerOut();  // 定时器到时,计算当前温度并更新
    void slotDealReturn(QByteArray msg);  // 处理服务器返回信息,待补充
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
