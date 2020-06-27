#include "clientcontroller.h"
#pragma execution_character_set("utf-8")
#include <QDebug>
ClientController::ClientController(SlaveMachine *sm, QObject *parent) : QObject(parent)
{
    this->sm = sm;
    qDebug()<<sm<<endl;
    waitFlag = false;
    // 以下需询问管理员设置
    sm->setTarTemp(sm->getDefaultTemp());
    sm->setPayment(0.0);
    sm->setMode(cold);
    rate = 1.0;
    tcpClient = new TcpClient();  // 负责与服务器通信
    sendClientInfo();  //初始化接口

    minuteTimer = startTimer(4000);  // 分钟定时器

    connect(tcpClient, SIGNAL(sigDataReturn(QByteArray)),
            this, SLOT(slotDealReturn(QByteArray)));  // 用于让controller处理tcpClient收到的消息

}

ClientController::~ClientController()
{
    delete sm;
}

void ClientController::timerEvent(QTimerEvent *event)
{
    if(event->timerId()  == minuteTimer) {  // 每分钟计算当前温度并更新
        qDebug()<<"minuteTimer触发"<<endl;
        updateTemp();  // 计算温度
        updatePayment();  // 计算费用
        sendMaster(none, no);  // 定时向中央空调发送自己状态/
        emit SignalTimeOutUpdated();  // 更新界面上的温度和费用
    }
    else if(event->timerId() == secondTimer) {  // 秒定时器, 发送1s内最后一次操作给服务器
        qDebug()<<"secondTimer触发"<<endl;
        sendMaster(manual,isTemp);
        waitFlag = false;
        killTimer(secondTimer);
    }
}

void ClientController::updateTemp()
{
    qDebug()<<"计算当前温度updateTemp()"<<endl;
    windSpeed curWind = sm->getCurWind();
    double curTemp = sm->getCurTemp();
    double tarTemp = sm->getTarTemp();
    double initialTemp = sm->getInitialTemp();
    // 每分钟当前房间温度变化大小delta
    double ratio = 1.0, delta = 0.0, oldTemp = curTemp;
    // 设置不同风速下温度的改变率
    if (curWind == lowWind)
        ratio = RATIO_LOW_WIND;
    else if (curWind == highWind)
        ratio = RATIO_HIGH_WIND;
    curWind != noWind ? delta = ratio * DELTA_TEMP_AC_ON : delta = ratio * DELTA_TEMP_AC_OFF;

    if(curWind != noWind){   // 空调在送风,温度朝着目标温度变化
        if (sm->getMode() == heat)
            sm->setCurTemp(curTemp + delta);
        else if (sm->getMode() == cold )
            sm->setCurTemp(curTemp - delta);
        // 检查温度达到目标值,停止送风
        if ((tarTemp - oldTemp) * (tarTemp - sm->getCurTemp()) <= 0||fabs(tarTemp-sm->getCurTemp())<0.00001){
//            sm->setTarWind(noWind);
            sendMaster(automatic, isWind);
        }
    }
    else{  // 空调不送风,温度朝着原始房间温度变化
        if (initialTemp - curTemp > 0.001)
            sm->setCurTemp(curTemp + delta);
        else if (curTemp - initialTemp > 0.001 )
            sm->setCurTemp(curTemp - delta);
        // 温度变换已经达到初始温度, 则房间温度不会再变
        if ((initialTemp - oldTemp) * (initialTemp - sm->getCurTemp()) <= 0)
            sm->setCurTemp(initialTemp);
        // 温差大于1度,则重新开始送风
        qDebug()<<"目标风速"<<sm->getTarWind()<<"nowind"<<noWind<<endl;

        if(fabs(sm->getCurTemp() - tarTemp) >= 0.9999 && sm->getState() && sm->getCurWind() == noWind){
//            sm->setTarWind(sm->getPreWind());
            qDebug()<<"温差大于1度,则重新开始送风"<<endl;
            sendMaster(automatic, isWind);
        }
    }
    qDebug()<<"温度变化: "<<curTemp<<"->"<<sm->getCurTemp()<<endl;
}

void ClientController::updatePayment()
{
    qDebug()<<"计算当前费用updatePayment()"<<endl;
    windSpeed wind = sm->getCurWind();
    double payment = sm->getPayment();
    if (wind == lowWind) {
        sm->setPayment(payment + rate / 3.0);
    }
    else if (wind == midWind) {
        sm->setPayment(payment + rate * 0.5);
    }
    else if (wind == highWind) {
        sm->setPayment(payment + rate);
    }

    qDebug()<<"费用变化: "<<payment<<"->"<<sm->getPayment()<<endl;
}


void ClientController::changeTemp(double tarTemp)
{
    qDebug()<<"changeTemp函数"<<endl;
    bool ok = false;
    if (sm->getMode() == cold) {
        if (tarTemp >= sm->getMinTempOnModeCold() - 0.0001 && tarTemp <= sm->getMaxTempOnModeCold() + 0.0001) {
            sm->setTarTemp(tarTemp);
            ok = true;
        }
        else
            emit SignalErrorOccoured(tempNotAllowed);
    }
    else if (sm->getMode() == heat) {
        if (tarTemp >= sm->getMinTempOnModeHeat() - 0.0001 && tarTemp <= sm->getMaxTempOnModeHeat() + 0.0001) {
            sm->setTarTemp(tarTemp);
            ok = true;
        }
        else
            emit SignalErrorOccoured(tempNotAllowed);
    }
    if (waitFlag == false && ok == true) {
        qDebug()<<"secondTimer开启"<<endl;
        secondTimer = startTimer(1000);//开启定时器,1秒钟
        waitFlag = true;
    }

}


void ClientController::changeWind()
{
    sendMaster(manual,isWind);
}

void ClientController::switchAC()
{
    sm->setState(!sm->getState());
    sendMaster(manual, isSwitch);

}

void ClientController::changeMode()
{
    sendMaster(manual, isMode);

}


void ClientController::slotDealReturn(QByteArray msg)//处理服务器返回消息
{
    qDebug()<<"服务器返回消息"<<msg<<endl;
    QJsonParseError e;
    QJsonDocument jsonDocNew = QJsonDocument::fromJson(msg, &e);
    QJsonObject getObj;
    if(e.error == QJsonParseError::NoError && !jsonDocNew.isNull()) {
        getObj = jsonDocNew.object();
    }
    auto header = getObj.value("Header");
    if (header == "returnWind") {  // 返回调度风速
        sm->setCurWind(windSpeed(getObj.value("Wind").toInt()));
        emit SignalInfoUpdated();
    }
    else if (header == "returnParams") {  // 返回初始参数
        sm->setDefaultTemp(getObj.value("defaultTemp").toDouble());
        sm->setDefaultWind((windSpeed)getObj.value("defaultWind").toInt());
        sm->setMaxTempOnModeCold(getObj.value("maxTempOnModeCold").toDouble());
        sm->setMaxTempOnModeHeat(getObj.value("maxTempOnModeHeat").toDouble());
        sm->setMinTempOnModeCold(getObj.value("minTempOnModeCold").toDouble());
        sm->setMinTempOnModeHeat(getObj.value("minTempOnModeHeat").toDouble());
        setRate(getObj.value("rate").toDouble());  // 返回电费单价
        if (sm->getState() == false) {  // 空调关闭状态下设置显示缺省温度、风速
            sm->setTarTemp(sm->getDefaultTemp());
            sm->setDefaultWind(sm->getDefaultWind());
            emit SignalInfoUpdated();
        }
    }
}


void ClientController::sendClientInfo()
{
    QJsonObject obj;
    obj.insert("Header","init");
    obj.insert("User","client");
    obj.insert("roomId",sm->getRoomId().toInt());
    QJsonDocument doc(obj);
    QByteArray msg = doc.toJson();
    auto ret = tcpClient->write(msg);
    if (ret == -1) {  // tcp失败
        emit SignalErrorOccoured(tcpFailed);
        return ;
    }
    qDebug()<<"client发送身份消息:"<<msg<<endl;
}
//none/automatic/manual
void ClientController::sendMaster(isOperation who, operationType type)
{
    QJsonObject obj;
    obj.insert("Header","request");
    obj.insert("User","client");
    obj.insert("roomId",sm->getRoomId().toInt());
    obj.insert("isOperation", who);
    QJsonObject context;//
    context.insert("operationType", type);//  isWind/isTemp/isSwitch/isMode
    context.insert("tarTemp",sm->getTarTemp());
    context.insert("curTemp",sm->getCurTemp());
    windSpeed wind = sm->getTarWind();
    if (who == automatic && sm->getCurWind() != noWind)
        wind = noWind;
    context.insert("tarWind",wind);
    context.insert("curWind",sm->getCurWind());
    context.insert("tarMode",sm->getMode());
    QString strDateTime = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    context.insert("time",strDateTime);
    context.insert("tarAC",sm->getState());
    context.insert("payment",sm->getPayment());
    obj.insert("Context",context);
    QJsonDocument doc(obj);
    qDebug()<<"客户端发往服务器消息"<<context<<endl;
    QByteArray msg = doc.toJson();
    auto ret = tcpClient->write(msg);
    tcpClient->flush();
    if (ret == -1) {  // tcp失败
        emit SignalErrorOccoured(tcpFailed);
    }
}


