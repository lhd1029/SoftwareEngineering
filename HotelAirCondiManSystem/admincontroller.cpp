#include "admincontroller.h"

AdminController::AdminController(){}

void AdminController::checkConfig()
{

}

//创建房间状态表
void AdminController::createStateList()
{

}

//设置启动参数
void AdminController::setParam(int tempPattern, double defaultTemp, double tempLimitLow, double tempLimitHigh, double feeRate, int serveNum)
{

}

std::list<roomState> AdminController::getStateList() const
{
    return this->stateList;
}

void AdminController::setStateList(const std::list<roomState> &value)
{
    this->stateList = value;
}

int AdminController::getTempPattern() const
{
    return this->tempPattern;
}

void AdminController::setTempPattern(int value)
{
    this->tempPattern = value;
}

double AdminController::getTempLimitLow() const
{
    return this->tempLimitLow;
}

void AdminController::setTempLimitLow(double value)
{
    this->tempLimitLow = value;
}

double AdminController::getTempLimitHigh() const
{
    return this->tempLimitHigh;
}

void AdminController::setTempLimitHigh(double value)
{
    this->tempLimitHigh = value;
}

double AdminController::getFeeRate() const
{
    return this->feeRate;
}

void AdminController::setFeeRate(double value)
{
    this->feeRate = value;
}

int AdminController::getServeNum() const
{
    return this->serveNum;
}

void AdminController::setServeNum(int value)
{
    this->serveNum = value;
}

int AdminController::getPowerOnOrOff() const
{
    return this->powerOnOrOff;
}

void AdminController::setPowerOnOrOff(int value)
{
    this->powerOnOrOff = value;
}

double AdminController::getDefaulttemp() const
{
    return this->defaulttemp;
}

void AdminController::setDefaulttemp(double value)
{
    this->defaulttemp = value;
}
