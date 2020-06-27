#include "admincontroller.h"

AdminController::AdminController(){}

void AdminController::checkConfig()
{
    tcpAdmin = new TcpAdmin();
    QJsonObject json;
    json.insert("Header", "init");
    json.insert("User", "admin");
    QJsonDocument document;
    document.setObject(json);
    QByteArray msg = document.toJson(QJsonDocument::Compact);
    tcpAdmin->write(msg);
    QString strJson(msg);
    qDebug() << strJson;
    connect(tcpAdmin, SIGNAL(sigDataReturn(QByteArray)), this, SLOT(slotDataReturn(QByteArray)));
}

//获取房间状态表
void AdminController::createStateList()
{
    QJsonObject json;
    qDebug()<<"create state list";
    json.insert("Header", "roomState");
    json.insert("User", "admin");
    QJsonDocument document;
    document.setObject(json);
    QByteArray msg = document.toJson(QJsonDocument::Compact);
    tcpAdmin->write(msg);
    QString strJson(msg);
    qDebug() << strJson;
}

//开启中央空调，设置启动参数
void AdminController::setParam(int curdefaultWind, double curdefaultTemp, double curColdLimitLow,
                               double curColdLimitHigh, double curHotLimitLow, double curHotLimitHigh,
                               double curfeeRate, int curserveNum)
{
    defaultWind = curdefaultWind;
    defaultTemp = curdefaultTemp;
    coldLimitLow = curColdLimitLow;
    coldLimitHigh = curColdLimitHigh;
    hotLimitLow = curHotLimitLow;
    hotLimitHigh = curHotLimitHigh;
    serveNum = curserveNum;
    feeRate = curfeeRate;
    powerOnOrOff = POWERON;
    powerOnOrOff = 1;
    QJsonObject json;
    json.insert("Header", "setParam");
    json.insert("User", "admin");
    json.insert("powerOnOrOff", POWERON);
    json.insert("defaultWind", defaultWind + 1);
    json.insert("defaultTemp", defaultTemp);
    json.insert("coldLimitLow", coldLimitLow);
    json.insert("coldLimitHigh", coldLimitHigh);
    json.insert("hotLimitLow", hotLimitLow);
    json.insert("hotLimitHigh", hotLimitHigh);
    json.insert("feeRate", feeRate);
    json.insert("serveNum", serveNum);
    QJsonDocument document;
    document.setObject(json);
    QByteArray msg = document.toJson(QJsonDocument::Compact);
    tcpAdmin->write(msg);
    QString strJson(msg);
    qDebug() << strJson;
}

//关闭中央空调
void AdminController::setParam(int powerState)
{
    powerOnOrOff = powerState;
    QJsonObject json;
    json.insert("Header", "setParam");
    json.insert("User","admin");
    json.insert("powerOnOrOff", POWEROFF);
    QJsonDocument document;
    document.setObject(json);
    QByteArray msg = document.toJson(QJsonDocument::Compact);
    tcpAdmin->write(msg);
    QString strJson(msg);
    qDebug() << strJson;
}

//显示各房间状态
/*格式
 * "Request":"ok"
 * "roomState":
 *  [
 *  {
 *      "roomId":..
 *      "powerOnOff":..
 *      "severOrHangUp":..
 *      "currentTemp":...
 *      "targetTemp":...
 *      "wind":...
 *      "feeRate":...
 *      "fee":...
 *      "serveTime":...
 *  },
 *  {
 *  ....下一个房间
 *  }
 *  ]
*/
void AdminController::slotDataReturn(QByteArray msg)
{
    QJsonParseError e;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(msg, &e);
    QJsonObject getObj;
    if(e.error == QJsonParseError::NoError && !jsonDoc.isNull())
    {
        getObj = jsonDoc.object();
        if(getObj.contains("powerOnOrOff"))
        {
            if(getObj.value("powerOnOrOff").toString().toInt() == POWERON){
                powerOnOrOff = POWEROFF;
                defaultTemp = getObj.value("defaultTemp").toString().toInt();
                defaultWind = getObj.value("defaultWind").toString().toInt();
                hotLimitLow = getObj.value("hotLimitLow").toString().toDouble();
                hotLimitHigh = getObj.value("hotLimitHigh").toString().toDouble();
                coldLimitHigh = getObj.value("coldLimitHigh").toString().toDouble();
                coldLimitLow = getObj.value("coldLimitLow").toString().toDouble();
                feeRate = getObj.value("feeRate").toString().toDouble();
                serveNum = getObj.value("serveNum").toString().toInt();
            }
            else
            {
                powerOnOrOff = POWEROFF;
                defaultTemp = initDefaultTemp;
                defaultWind = initDefaultWind;
                hotLimitLow = initHotLowLimit;
                hotLimitHigh = initHotHighLimit;
                coldLimitHigh = initColdHighLimit;
                coldLimitLow = initColdLowLimit;
                feeRate = initFeeRate;
                serveNum = initServeNum;
            }
            emit sigGetConfig();
        }
        else if(getObj.contains("roomState"))
        {
            qDebug()<<"Admin receive room state";
            std::list<roomState> roomStateList;
            QJsonArray roomArray = getObj.value("roomState").toArray();
            for(int i = 0 ;i < roomArray.size(); i++)
            {
                struct roomState temp;
                QJsonObject roomObj = roomArray[i].toObject();
                temp.fee = roomObj.value("fee").toDouble();
                temp.wind = roomObj.value("wind").toInt();
                temp.roomId = roomObj.value("roomId").toInt();
                temp.feeRate = roomObj.value("feeRate").toDouble();
                temp.serveTime = roomObj.value("serveTime").toInt();
                temp.powerOnOff = roomObj.value("powerOnOff").toInt();
                temp.targetTemp = roomObj.value("targetTemp").toDouble();
                temp.currentTemp = roomObj.value("currentTemp").toDouble();
                temp.serveOrHangUp = roomObj.value("serveOrHangUp").toInt();
                qDebug()<<"receive room wind:"<<temp.wind;
                qDebug()<<"receive room power:"<<temp.powerOnOff;

                roomStateList.push_back(temp);
            }
            setStateList(roomStateList);
            emit sigGetRoomState();
        }
        else
            qDebug()<<"Room State Json content wrong";
    }
    else{
        qDebug()<<"Json contains error";
    }
}

std::list<roomState> AdminController::getStateList() const
{
    return this->stateList;
}

void AdminController::setStateList(const std::list<roomState> &value)
{
    this->stateList = value;
}

int AdminController::getDefaultWind() const
{
    return this->defaultWind;
}

void AdminController::setDefaultWind(int value)
{
    this->defaultWind = value;
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
    return this->defaultTemp;
}

void AdminController::setDefaulttemp(double value)
{
    this->defaultTemp = value;
}

double AdminController::getColdLimitLow() const
{
    return coldLimitLow;
}

void AdminController::setColdLimitLow(double value)
{
    coldLimitLow = value;
}

double AdminController::getColdLimitHigh() const
{
    return coldLimitHigh;
}

void AdminController::setColdLimitHigh(double value)
{
    coldLimitHigh = value;
}

double AdminController::getHotLimitLow() const
{
    return hotLimitLow;
}

void AdminController::setHotLimitLow(double value)
{
    hotLimitLow = value;
}

double AdminController::getHotLimitHigh() const
{
    return hotLimitHigh;
}

void AdminController::setHotLimitHigh(double value)
{
    hotLimitHigh = value;
}
