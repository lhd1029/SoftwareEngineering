#include "masterairconditioner.h"
#pragma execution_character_set("utf-8")
MasterAirconditioner::MasterAirconditioner(int n, QObject *parent) : QObject(parent),serviceObjectNum(n)
{
    timer = new QTimer();
    timer->setInterval(DISPATCH_TIME);
    runningNum = 0;
    timer->start();
    waitingQueue.resize(4);
    runningQueue.resize(4);
    waitingQueueMap.resize(4);
    runningQueueMap.resize(4);
    hungryQueue.resize(3);
    hungryQueueMap.resize(3);
    //QVector<int> roomIdVec{101,102,103,104,105,106,107,108,109,110,201,202,203,204,205,206,207,208,209,210,301,302,303,304,305,306,307,308,309,310};
    for(int i=0;i<roomIdVec.size();i++){
        clientStateMap[roomIdVec[i]] = new ClientState(roomIdVec[i]);
        roomStateMap[roomIdVec[i]] = new roomState;
        roomStateMap[roomIdVec[i]]->occupied = 0;
    }
    //wait for owx
}
int MasterAirconditioner::isInClientStateMap(int roomId)
{
    return clientStateMap.count(roomId);
}
void MasterAirconditioner::changeAC(int roomId,int AC)
{
    clientStateMap[roomId]->set_is_open(AC);
}
double MasterAirconditioner::getFee(int wind,int curTemp,int tarTemp)
{
    return 0;
}
void MasterAirconditioner::changeTargetTemp(int roomId,int tarTemp)
{
    clientStateMap[roomId]->set_target_temp(tarTemp);
}
void MasterAirconditioner::changeCurTemp(int roomId, int curTemp)
{
    clientStateMap[roomId]->set_cur_temp(curTemp);
}
void MasterAirconditioner::changeCurWind(int roomId,int curWind)
{
    clientStateMap[roomId]->set_cur_speed(curWind);
}
void MasterAirconditioner::changeTarWind(int roomId, int tarWind)
{
    clientStateMap[roomId]->set_target_speed(tarWind);
}
void MasterAirconditioner::changeMode(int roomId,int mode)
{

}
void MasterAirconditioner::deleteFromQueue(int roomId,int wind,int state)
{
    qDebug()<<"开始删除";
    if(state==0){
        for(auto i=waitingQueue[wind].begin();i!=waitingQueue[wind].end();i++){
            if(roomId == i->first){
                waitingQueue[wind].erase(i);
                break;
            }
        }

        //waitingQueue[wind].erase(waitingQueueMap[wind][roomId]);
        //waitingQueueMap[wind].erase(roomId);
    }
    else if(state==1){
        for(auto i=runningQueue[wind].begin();i!=runningQueue[wind].end();i++){
            if(roomId == i->first){
                runningQueue[wind].erase(i);
                break;
            }
        }
        //runningQueue[wind].erase(runningQueueMap[wind][roomId]);
        qDebug()<<"第一步删除成功";
        //runningQueueMap[wind].erase(roomId);
        //qDebug()<<"第二步删除成功";
    }
    else if(state==2){
        for(auto i=hungryQueue[wind].begin();i!=hungryQueue[wind].end();i++){
            if(roomId == i->first){
                hungryQueue[wind].erase(i);
                break;
            }
        }

        //hungryQueue.erase(hungryQueueMap[roomId]);
        //hungryQueueMap.erase(roomId);
    }
    qDebug()<<"删除成功";
}

int MasterAirconditioner::deleteFromAllClientQueue(tcpclientsocket *tcpClientSocket)
{
    for(auto i=allClientQueue.begin();i!=allClientQueue.end();i++){
        if((*i).second==tcpClientSocket){
            int roomId = (*i).first;
            allClientQueue.erase(allClientQueueMap[roomId]);
            allClientQueueMap.erase(roomId);
            return roomId;
        }
    }
}

void MasterAirconditioner::insertIntoAllClientQueue(int roomId,tcpclientsocket* i)
{
    QPair<int,tcpclientsocket*> a(roomId,i);
    allClientQueue.push_front(a);
    allClientQueueMap[roomId]=allClientQueue.begin();
}

void MasterAirconditioner::insertIntoQueue(int roomId, int wind, int state)
{

    tcpclientsocket* tcp;
    for(auto i=allClientQueue.begin();i!=allClientQueue.end();i++){
        if((*i).first==roomId){
            tcp = (*i).second;
            break;
        }
    }
    QPair<int,tcpclientsocket*> a(roomId,tcp);
    qDebug()<<"成功";
    if(state==0){
        waitingQueue[wind].push_front(a);
        waitingQueueMap[wind][roomId] = waitingQueue[wind].begin();
    }
    else if(state==1){
        runningQueue[wind].push_front(a);
        runningQueueMap[wind][roomId] = runningQueue[wind].begin();
    }
    else if(state==2){
        hungryQueue[wind].push_front(a);
        hungryQueueMap[wind][roomId] = hungryQueue[wind].begin();
    }
    qDebug()<<"插入成功";
}
void MasterAirconditioner::deleteFromQueue(int roomId)
{
    qDebug()<<"进入删除函数";
    QVector<int> position;
    position.push_back(findFromWaitingQueue(roomId));
    position.push_back(findFromRunningQueue(roomId));
    position.push_back(findFromHungryQueue(roomId));
    if(position[0]!=0){
        deleteFromQueue(roomId,position[0],0);
    }
    else if(position[1]!=0){
        deleteFromQueue(roomId,position[1],1);
    }
    else if(position[2]!=0){
        deleteFromQueue(roomId,position[2],2);
    }
    qDebug()<<"成功删除";
}


int MasterAirconditioner::isInQueue(int roomId,int state)
{
    if(state==0){
        for(int i=1;i<=3;i++){
            for(auto j=waitingQueue[i].begin();j!=waitingQueue[i].end();j++){
                if(j->first==roomId)
                    return 1;
            }
        }
    }
    else if(state==1){
        for(int i=1;i<=3;i++){
            for(auto j=runningQueue[i].begin();j!=runningQueue[i].end();j++){
                if(j->first==roomId)
                    return 1;
            }
        }
    }
    else if(state==2){
        for(int i=1;i<=2;i++){
            for(auto j=hungryQueue[i].begin();j!=hungryQueue[i].end();j++){
                if(j->first==roomId)
                    return 1;
            }
        }
    }
    return 0;
}

int MasterAirconditioner::isInAllClientQueue(int roomId)
{
    for(auto j=allClientQueue.begin();j!=allClientQueue.end();j++){
        if(j->first==roomId)
            return 1;
    }
}
int MasterAirconditioner::findFromRunningQueue(int roomId)
{
    for(int i=1;i<=3;i++){
        for(auto j=runningQueue[i].begin();j!=runningQueue[i].end();j++){
            if(j->first==roomId)
                return i;
        }
    }
    return 0;
}
int MasterAirconditioner::findFromHungryQueue(int roomId)
{
    for(int i=1;i<=2;i++){
        for(auto j=waitingQueue[i].begin();j!=waitingQueue[i].end();j++){
            if(j->first==roomId)
                return i;
        }
    }
    return 0;
}
int MasterAirconditioner::findFromWaitingQueue(int roomId)
{
    for(int i=1;i<=3;i++){
        for(auto j=waitingQueue[i].begin();j!=waitingQueue[i].end();j++){
            if(j->first==roomId)
                return i;
        }
    }
    return 0;
}

void MasterAirconditioner::changeClientState(int roomId,QJsonObject context)
{

    QJsonObject obj = context;
    qDebug()<<"用于改变从机状态的QJson:"<<context;
    clientStateMap[roomId]->set_is_open(obj.value("tarAC").toInt());
    clientStateMap[roomId]->set_time(QDateTime::fromString(obj.value("time").toString(),"yyyy-MM-dd hh:mm:ss"));
    clientStateMap[roomId]->set_cur_temp(obj.value("curTemp").toDouble());
    clientStateMap[roomId]->set_cur_speed(obj.value("curWind").toInt());
    clientStateMap[roomId]->set_target_temp(obj.value("tarTemp").toDouble());
    clientStateMap[roomId]->set_target_speed(obj.value("tarWind").toInt());
    qDebug()<<"用于状态改变的tarWind"<<obj.value("tarWind").toInt();
    qDebug()<<"房间"<<roomId<<"的tarWind为"<<clientStateMap[roomId]->get_target_speed();

}


MasterAirconditioner::~MasterAirconditioner()
{
    //先懒得写了
}
