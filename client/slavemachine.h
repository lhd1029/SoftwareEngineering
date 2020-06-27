#ifndef SLAVEMACHINE_H
#define SLAVEMACHINE_H
#include <QMainWindow>
enum windSpeed {noWind,lowWind,midWind,highWind};  // 风速类型
enum ACmode {cold,heat};  // 运行模式

class SlaveMachine
{
public:
    SlaveMachine(QString roomId = "111", QString userName = "liu", double initialTemp = 30.0);
    //get()
    QString getRoomId() {return roomId;}
    QString getUserName() {return userName;}
    windSpeed getCurWind() {return curWind;}
    windSpeed getTarWind() {return tarWind;}
//    windSpeed getPreWind() {return preWind;}
    windSpeed getDefaultWind() {return defaultWind;}
    double getInitialTemp() {return initialTemp;}
    double getDefaultTemp() {return defaultTemp;}
    double getMinTempOnModeCold() {return minTempOnModeCold;}
    double getMaxTempOnModeCold() {return maxTempOnModeCold;}
    double getMinTempOnModeHeat() {return minTempOnModeHeat;}
    double getMaxTempOnModeHeat() {return maxTempOnModeHeat;}
    double getCurTemp() {return curTemp;}
    double getTarTemp() {return tarTemp;}
    bool getState() {return ACState;}
    double getPayment() {return payment;}
    ACmode getMode() {return mode;}
    //set()
    void setRoomId(QString roomId) {this->roomId = roomId;}
    void setUserName(QString name) {this->userName = name;}
    void setCurWind(windSpeed curWind) {this->curWind = curWind;}
    void setTarWind(windSpeed tarWind) {this->tarWind = tarWind;}
//    void setPreWind(windSpeed preWind) {this->preWind = preWind;}
    void setDefaultWind(windSpeed wind) {defaultWind = wind;}
    void setInitialTemp(double initialTemp) {this->initialTemp = initialTemp;}
    void setDefaultTemp(double defaultTemp) {this->defaultTemp = defaultTemp;}
    void setMinTempOnModeCold(double minTempOnModeCold) {this->minTempOnModeCold = minTempOnModeCold;}
    void setMaxTempOnModeCold(double maxTempOnModeCold) {this->maxTempOnModeCold = maxTempOnModeCold;}
    void setMinTempOnModeHeat(double minTempOnModeHeat) {this->minTempOnModeHeat = minTempOnModeHeat;}
    void setMaxTempOnModeHeat(double maxTempOnModeHeat) {this->maxTempOnModeHeat = maxTempOnModeHeat;}
    void setCurTemp(double curTemp) {this->curTemp = curTemp;}
    void setTarTemp(double tarTemp) {this->tarTemp = tarTemp;}
    void setState(bool ACState) {this->ACState = ACState;}
    void setPayment(double payment) {this->payment = payment;}
    void setMode(ACmode mode) {this->mode = mode;}
private:
    QString roomId;  // 房间号
    QString userName;  // 客户名
    windSpeed curWind;  // 当前风速
    windSpeed tarWind;  // 目标风速

    windSpeed defaultWind;  // 缺省风速
    double initialTemp;  // 最初温度
    double defaultTemp;  // 默认缺省温度
    double minTempOnModeCold;  // 制冷模式最低温度
    double maxTempOnModeCold;  // 制冷模式最高温度
    double minTempOnModeHeat;  // 制热模式最低温度
    double maxTempOnModeHeat;  // 制热模式最高温度
    double curTemp;  // 当前温度
    double tarTemp;  // 目标温度
    bool ACState;  // 空调开启状态
    double payment;  // 费用
    ACmode mode;  // 模式
};

#endif // SLAVEMACHINE_H
