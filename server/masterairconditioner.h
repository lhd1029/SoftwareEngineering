#ifndef MASTERAIRCONDITIONER_H
#define MASTERAIRCONDITIONER_H

#define DISPATCH_TIME 1000

#include<QList>
#include<QMap>
#include<map>
#include<QPair>
#include<tcpclientsocket.h>
#include "globaldata.h"
#include<QTime>
#include<QTimer>
#include <QObject>
#include <QVector>

#include<clientstate.h>
using namespace std;
class MasterAirconditioner : public QObject
{
    Q_OBJECT
private:
public:
    typedef QList<QPair<int,tcpclientsocket*>> DispatchQueue;
    typedef map<int,QList<QPair<int,tcpclientsocket*>>::iterator> DispatchQueueMap;
    QMap<int,ClientState*> clientStateMap;     //假设房间从101到310
    QMap<int, roomState*> roomStateMap;
    int serviceObjectNum;
    int runningNum;
    ~MasterAirconditioner();
    explicit MasterAirconditioner(int n=3,QObject *parent = nullptr);
    void changeTargetTemp(int roomId,int tarTemp);
    void changeCurTemp(int roomId,int curTemp);
    void changeCurWind(int roomId,int curWind);
    void changeTarWind(int roomId,int tarWind);
    double getFee(int wind,int curTemp,int tarTemp);
    void changeWind(int roomId,int wind);
    void changeAC(int roomId, int AC);
    void changeMode(int roomId,int mode);
    int findFromRunningQueue(int roomId);
    int findFromWaitingQueue(int roomId);
    int findFromHungryQueue(int roomId);
    void deleteFromQueue(int roomId);
    void deleteFromQueue(int roomId,int wind,int state);//房间号，风速，state=0表示waiting队列，state=1表示running队列，2表示hungry队列
    int deleteFromAllClientQueue(tcpclientsocket*tcpClientSocket);//返回roomId,该函数只用于断开连接时，跟其他delete有区别
    void insertIntoAllClientQueue(int roomId,tcpclientsocket *i);//插入总的客户队列中，与其他插入不同
    void insertIntoQueue(int roomId,int wind,int state);//state=0表示插入waiting队列，state=1表示插入running队列,2表示hungry队列
    int isInClientStateMap(int roomId);
    int isInQueue(int roomId, int state);//查询是否在所有送风队列中
    int isInAllClientQueue(int roomId);
    void changeClientState(int roomId, QJsonObject context);
    void fromRunningToWaiting(int roomId);


    DispatchQueue allClientQueue;       //所有连接的client端
    DispatchQueueMap allClientQueueMap;
    QVector<DispatchQueue> waitingQueue;
    QVector<DispatchQueueMap> waitingQueueMap;
    QVector<DispatchQueue> runningQueue;
    QVector<DispatchQueueMap> runningQueueMap;
    QVector<DispatchQueueMap> hungryQueueMap;//饥饿的队列只看时间，不然总会出现饥饿
    QVector<DispatchQueue> hungryQueue;
    QTimer *timer;

};

#endif // MASTERAIRCONDITIONER_H
