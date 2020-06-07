#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H
#define SERVE 1
#define HANGE_UP 0
#include <list>
#include "globaldata.h"

class AdminController
{
public:
    AdminController();
    //查看空调状态
    void checkConfig();
    //创建房间状态表
    void createStateList();
    //设置启动参数
    void setParam(int tempPattern, double defaultTemp, double tempLimitLow, double tempLimitHigh, double feeRate, int serveNum);

    //set get方法
    std::list<roomState> getStateList() const;
    void setStateList(const std::list<roomState> &value);

    int getTempPattern() const;
    void setTempPattern(int value);

    double getTempLimitLow() const;
    void setTempLimitLow(double value);

    double getTempLimitHigh() const;
    void setTempLimitHigh(double value);

    double getFeeRate() const;
    void setFeeRate(double value);

    int getServeNum() const;
    void setServeNum(int value);

    int getPowerOnOrOff() const;
    void setPowerOnOrOff(int value);

    double getDefaulttemp() const;
    void setDefaulttemp(double value);

private:
    std::list<roomState> stateList; //状态表
    int powerOnOrOff;
    int tempPattern;
    double tempLimitLow;
    double tempLimitHigh;
    double feeRate;
    int serveNum;
    double defaulttemp;
};

#endif // ADMINCONTROLLER_H
