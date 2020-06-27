#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include <QObject>
#include "globaldata.h"
#include "tcpadmin.h"

class AdminController : public QObject
{
    Q_OBJECT
public:
    AdminController();
    //查看空调状态
    void checkConfig();
    //创建房间状态表
    void createStateList();
    //设置启动参数
    void setParam(int curdefaultWind, double curdefaultTemp, double curColdLimitLow,
                  double curColdLimitHigh, double curHotLimitLow, double curHotLimitHigh,
                  double curfeeRate, int curserveNum);
    void setParam(int powerOnOrOff);

    //set get方法
    std::list<roomState> getStateList() const;
    void setStateList(const std::list<roomState> &value);

    int getDefaultWind() const;
    void setDefaultWind(int value);

    double getFeeRate() const;
    void setFeeRate(double value);

    int getServeNum() const;
    void setServeNum(int value);

    int getPowerOnOrOff() const;
    void setPowerOnOrOff(int value);

    double getDefaulttemp() const;
    void setDefaulttemp(double value);

    double getColdLimitLow() const;
    void setColdLimitLow(double value);

    double getColdLimitHigh() const;
    void setColdLimitHigh(double value);

    double getHotLimitLow() const;
    void setHotLimitLow(double value);

    double getHotLimitHigh() const;
    void setHotLimitHigh(double value);

private:
    std::list<roomState> stateList; //状态表
    TcpAdmin *tcpAdmin;
    int powerOnOrOff;
    int defaultWind;
    double defaultTemp;
    double coldLimitLow;
    double coldLimitHigh;
    double hotLimitLow;
    double hotLimitHigh;
    double feeRate;
    int serveNum;

signals:
    void sigGetRoomState();
    void sigGetConfig();

public slots:
    void slotDataReturn(QByteArray msg);
};

#endif // ADMINCONTROLLER_H
