#ifndef SERVER_H
#define SERVER_H
#define TIME_SLOT 120000  // 时间片调度时间
#define TIME_HUNGRY 240000  // 饥饿时间
#include <QObject>
#include <QDateTime>
#include <QTcpServer>
#include "tcpclientsocket.h"
#include "masterairconditioner.h"
#include "databasesteplyreport.h"
#include "databasetimelyreport.h"
#include <QPair>
#include "data.h"

enum isOperation{none, automatic, manual};
enum operationType{no, isWind, isTemp, isSwitch, isMode};
enum errorType {tempNotAllowed,tcpFailed};  // 错误类型

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr,int port = 0);
    ~Server();
    QList<tcpclientsocket*> tcpClientSocketList;
    tcpclientsocket* managerSocket;
    tcpclientsocket* adminSocket;
    tcpclientsocket* receptionistSocket;
    void dispatch(int roomId,int tarWind,int tarAC);
    QByteArray sendWindMessage(QString State,int Wind);//发送风速的信息
    QByteArray sendParamsMessage();//发送参数信息
    QByteArray sendOnOffMessage(int onOrOff);//发送开关信息，0为开（可以开），1为关
    void showDispatchResult();
    void myStartTimer(int roomId);
    void myStopTimer(int roomId);
    double get_rate(){return rate;}
    void set_rate(double newRate){rate = newRate;}
    void set_client_state(ClientState *&clientState, int roomId, QJsonObject obj, QDateTime time);

private:
    int powerOnOrOff;
    int defaultWind;
    double defaultTemp;
    double minTempOnModeCold;  // 制冷模式最低温度
    double maxTempOnModeCold;  // 制冷模式最高温度
    double minTempOnModeHeat;  // 制热模式最低温度
    double maxTempOnModeHeat;  // 制热模式最高温度
    double rate;
    int serveNum;
    MasterAirconditioner *masterAirconditioner;
    DatabaseSteplyReport dbStep;
    DatabaseTimelyReport dbTime;

signals:
    void sigDisconnected(QByteArray);         //断开连接信号
    void sigConnected(QByteArray);            //连接信号
    void sigUpdateServer(QByteArray);      //更新服务器显示信号，由tcpserver(界面)接收
public slots:
    void slotHungryInsert(int roomId,int wind);
    void slotTimeSlot(int roomId,int wind);//时间片调度，如果同风的running队列中有对象存在，就换出，并把请求换入
    void slotDisconnected();
    void slotUpdateServer(QByteArray,int descriptor);//新增
    void slotDealCommand(QByteArray, int descriptor);
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
