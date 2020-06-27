#include "server.h"
#include "globaldata.h"

#pragma execution_character_set("utf-8")
Server::Server(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any, port);//监听任意
    if(!dbStep.connect() || !dbTime.connect()) {
        qDebug()<<"fail to connect to DB";
        return;
    }
    qDebug()<<"数据库连接成功"<<endl;
    managerSocket = nullptr;
    adminSocket = nullptr;
    receptionistSocket = nullptr;
    powerOnOrOff = POWEROFF;
    defaultWind = 2;
    defaultTemp = 25.0;
    minTempOnModeCold = 18.0;
    maxTempOnModeCold = 25.0;
    minTempOnModeHeat = 25.0;
    maxTempOnModeHeat = 30.0;
    rate = 1.0;
    serveNum = 3;
    masterAirconditioner = new MasterAirconditioner(serveNum);
}

Server::~Server()
{
    dbStep.disconnect();
    dbTime.disconnect();
}
void Server::incomingConnection(qintptr socketDescriptor)
{
    tcpclientsocket *tcpClientSocket = new tcpclientsocket(this);//一旦接收就创建一个与客户端通信的socket
    tcpClientSocket->setSocketDescriptor(socketDescriptor);//保存其句柄
    tcpClientSocketList.append(tcpClientSocket);
    QByteArray msg = "Connected successfully";
    qDebug()<<"连接成功"<<endl;
    emit sigConnected(msg);//发送信号给tcpServer界面
    connect(tcpClientSocket,SIGNAL(sigCommandReceived(QByteArray,int)),this,SLOT(slotUpdateServer(QByteArray,int)));
    connect(tcpClientSocket,SIGNAL(sigCommandReceived(QByteArray,int)),this,SLOT(slotDealCommand(QByteArray,int)));
    connect(tcpClientSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));//如果客户端断开，要和服务器说明白,将其内部套接字列表中对应套接字删除
}
void Server::slotUpdateServer(QByteArray msg,int descriptor)
{
    emit sigUpdateServer(msg);
}
void Server::slotDisconnected()//断开连接，要将中央空调控制的队列中对应内容要删除
{
    tcpclientsocket *item;
    for(int i=0;i<tcpClientSocketList.size();i++){
        item = tcpClientSocketList[i];
        if(item->socketDescriptor()==-1){
            QByteArray msg = "Disconnected successfully";
            emit sigDisconnected(msg);
            int roomId;
            roomId = masterAirconditioner->deleteFromAllClientQueue(item);
            //从running与waiting队列中删除掉
            masterAirconditioner->deleteFromQueue(roomId,masterAirconditioner->findFromRunningQueue(roomId),1);
            masterAirconditioner->deleteFromQueue(roomId,masterAirconditioner->findFromRunningQueue(roomId),0);
            tcpClientSocketList.removeAt(i);
            qDebug()<<"删除后列表大小："<<tcpClientSocketList.size()<<endl;
            return;
        }
    }
    return;
}

void Server::set_client_state(ClientState *&clientState, int roomId, QJsonObject obj, QDateTime time)
{
    int status = -1;
    if (obj.value("tarAC").toBool() == false)
        status = -1;
    else if (masterAirconditioner->isInQueue(roomId,1))  // running队列中
        status = 1;
    else if (masterAirconditioner->isInQueue(roomId,0) ||
             masterAirconditioner->isInQueue(roomId,2))  // 等待调度中
        status = 2;
    else // 开启但未运行
        status = 0;
    clientState =  masterAirconditioner->clientStateMap.find(roomId).value();
    clientState->set_time(time);
    clientState->set_status(status);
    clientState->set_is_open((int)obj.value("tarAC").toBool());
    qDebug()<<"******"<<clientState->get_is_open()<<"**********************"<<endl;
    clientState->set_payment(obj.value("payment").toDouble());
    clientState->set_cur_temp(obj.value("curTemp").toDouble());
    clientState->set_cur_speed(obj.value("curWind").toInt());
    clientState->set_target_temp(obj.value("tarTemp").toDouble());
    clientState->set_target_speed(obj.value("tarWind").toInt());
}

void Server::slotDealCommand(QByteArray msg,int descriptor)
{
    QJsonParseError e;
    QJsonDocument jsonDocNew = QJsonDocument::fromJson(msg, &e);
    QJsonObject getObj;
//    qDebug()<<msg<<endl;
    getObj = jsonDocNew.object();
    qDebug()<<"收到"<<getObj<<endl;
    if(getObj.value("Header")=="init"){
        if(getObj.value("User").toString()=="client"){
            int roomId = getObj.value("roomId").toInt();
            qDebug()<<"init房间号为"<<roomId<<endl;
            if(!masterAirconditioner->isInClientStateMap(roomId)){
                qDebug()<<"请求无效"<<endl;
                return;
            }
            qDebug()<<"连接的总大小"<<tcpClientSocketList.size();
            for(auto i = tcpClientSocketList.begin();i!=tcpClientSocketList.end();i++){
                if((*i)->socketDescriptor()==descriptor){
                    if(masterAirconditioner->isInAllClientQueue(roomId)==0){
                        masterAirconditioner->insertIntoAllClientQueue(roomId,*i);
                        break;
                    }
//                    else{
//                        qDebug()<<"客户端连接时出现错误";
//                        break;
//                    }
                    masterAirconditioner->insertIntoAllClientQueue(roomId,*i);
                    break;
                }
            }
            qDebug()<<"初始化成功的房间号="<<masterAirconditioner->allClientQueue.begin()->first;
            sendParamsMessage();
        }
        else if(getObj.value("User").toString()=="manager"){
            qDebug()<<"accept to manager";
            if(managerSocket == nullptr){  //找到对应的socket赋给managerSocket
                for(auto i = tcpClientSocketList.begin(); i != tcpClientSocketList.end(); i++){
                    if((*i)->socketDescriptor()==descriptor){
                        managerSocket = *i;
                        break;
                    }
                }
            }
            //qDebug()<<managerSocket->socketDescriptor();
        }
        else if(getObj.value("User").toString()=="receptionist"){
            qDebug() << "Connecting to Receptionist......";
            if (receptionistSocket == nullptr)
            {
                for (auto i = tcpClientSocketList.begin(); i != tcpClientSocketList.end(); i++)
                {
                    if ((*i)->socketDescriptor()==descriptor)
                    {
                        receptionistSocket = *i;
                        break;
                    }
                }
            }
            qDebug() << receptionistSocket->socketDescriptor();
        }
        else if(getObj.value("User").toString()=="admin"){
            qDebug() << "Connecting to admin......";
            if(adminSocket == nullptr)
            {
                for(auto i = tcpClientSocketList.begin(); i != tcpClientSocketList.end(); i++)
                {
                    if ((*i)->socketDescriptor()==descriptor)
                    {
                        adminSocket = *i;
                        break;
                    }
                }
            }
            QJsonObject jsonObj;
            jsonObj.insert("config","return");
            jsonObj.insert("powerOnOrOff", powerOnOrOff);
            if(powerOnOrOff == POWERON){
                jsonObj.insert("defaultTemp", defaultTemp);
                jsonObj.insert("defaultWind",defaultWind);
                jsonObj.insert("coldLimitLow", minTempOnModeCold);
                jsonObj.insert("coldLimitHigh", maxTempOnModeCold);
                jsonObj.insert("hotLimitLow", minTempOnModeHeat);
                jsonObj.insert("hotLimitHigh", maxTempOnModeHeat);
                jsonObj.insert("feeRate",rate);
                jsonObj.insert("serveNum",serveNum);
            }
            QJsonDocument document;
            document.setObject(jsonObj);
            QByteArray jsonArray = document.toJson(QJsonDocument::Compact);
            adminSocket->write(jsonArray);//发json
        }
    }

    else if(getObj.value("Header")=="setParam"){
        powerOnOrOff = getObj.value("powerOnOrOff").toInt();
        defaultWind = getObj.value("defaultWind").toInt();
        defaultTemp = getObj.value("defaultTemp").toDouble();
        minTempOnModeCold = getObj.value("minTempOnModeCold").toDouble();
        maxTempOnModeCold = getObj.value("maxTempOnModeCold").toDouble();
        minTempOnModeHeat = getObj.value("minTempOnModeHeat").toDouble();
        maxTempOnModeHeat = getObj.value("maxTempOnModeHeat").toDouble();
        rate = getObj.value("feeRate").toDouble();
        serveNum = getObj.value("serveNum").toInt();
        masterAirconditioner->serviceObjectNum = serveNum;
    }
    else if(getObj.value("Header")=="request"){
        qDebug()<<"收到请求"<<endl;
        if(getObj.value("User").toString()=="client"){
            QJsonObject obj = getObj.value("Context").toObject();
            int roomId = getObj.value("roomId").toInt();
            qDebug()<<"request的房间号为:"<<roomId;
            masterAirconditioner->changeClientState(roomId,obj);//根据发送来的请求，更新状态信息
            int IsOperation = isOperation(getObj.value("isOperation").toInt());
            QDateTime time = QDateTime::fromString(obj.value("time").toString(), "yyyy-MM-dd hh:mm:ss");
            qDebug()<<"isOperation="<<IsOperation<<endl;
            //如果是人工的开机操作，对应参数+1
            //如果是人工的加减风操作，对应参数+1
            //如果是人工的加减温度，对应参数+1
            if(IsOperation==isOperation::none){//按时来
//                qDebug()<<"**************************"<<endl;
//                qDebug()<<obj<<endl;
                //obj格式
                // "curTemp":30,"curWind":0,"operationType":0,"payment":0,"tarAC":false,
                //"tarMode":0,"tarTemp":25,"tarWind":0,"time":"2020-06-26 10:15:22"},
                //"Header":"request","User":"client","isOperation":0,"roomId":101
//                qDebug()<<"**************************"<<endl;

                ClientState *clientState = nullptr;
                                set_client_state(clientState, roomId, obj, time);

                bool ret = dbTime.update(clientState, rate);
                qDebug()<<"写入timely数据库: "<<ret<<endl;

                return;
            }
            else if(IsOperation==isOperation::manual){//人工点击
                qDebug()<<"准备处理人工请求"<<endl;
                int tarWind = obj.value("tarWind").toInt();
                int tarAC = (int)obj.value("tarAC").toBool();
                dispatch(roomId,tarWind,tarAC);
                //写入steply数据库
                //context.insert("operationType", type);//  isWind/isTemp/isSwitch/isMode
                bool ret = false;
                if (obj.value("operationType") == isWind)
                    ret = dbStep.add_wind_report(roomId, time, obj.value("tarWind").toInt());
                else if (obj.value("operationType") == isTemp)
                    ret = dbStep.add_temp_report(roomId, time, obj.value("tarTemp").toDouble());
                else if (obj.value("operationType") == isMode)
                    ret = dbStep.add_switch_report(roomId, time, obj.value("tarTemp").toDouble(),
                                 obj.value("tarWind").toInt(), obj.value("tarMode").toInt());
                if (obj.value("operationType") == isSwitch) {
                    if(obj.value("tarAC").toBool() == true) {  // 打开空调
                        ret = dbStep.add_switch_report(roomId, time, obj.value("tarTemp").toDouble(),
                                     obj.value("tarWind").toInt(), obj.value("tarMode").toInt());
                    }
                    else {  // 关闭空调
                        ret = dbStep.add_switch_report(roomId, time, -1.0, -1, -1);
                    }
                }
                ClientState *clientState = nullptr;
                set_client_state(clientState, roomId, obj, time);
                qDebug()<<"写入steply数据库: "<<ret<<endl;

            }
            else if(IsOperation==isOperation::automatic){//该请求是客户端根据温度情况发送的是否开启风
                qDebug()<<"准备处理客户端自动请求"<<endl;
                int tarWind = obj.value("tarWind").toInt();
                int tarAC = (int)obj.value("tarAC").toBool();
                dispatch(roomId,tarWind,tarAC);
            }
        }
        /*
         *格式
         * "Request":"ok",
         * "StartDate":"YYYYMMDD"
         * "EndDate":"YYYYMMDD",
         * "yyyyMMdd":
         *      [
         *      {
         *          "roomId":..
         *          "useACTimes":..
         *          "changeDegreeTimes":..
         *          "changeWindTimes":..
         *          "dispatchTimes":..
         *          "useACTime":..
         *          "detailRecordRows":.. 还没写入
         *      }，
         *      {
         *      ....下一个房间
         *      }
         * ]，
         * "yyyyMMdd":[下一天的数据
         * ]
        */
        else if(getObj.value("User").toString()=="manager"){
            QDate start = QDate::fromString(getObj.value("StartDate").toString(),"yyyyMMdd");
            QDate end = QDate::fromString(getObj.value("EndDate").toString(),"yyyyMMdd");
            int days = start.daysTo(end) + 1; //要查询的天数
            std::list<QJsonObject> objDate;
            QJsonObject rootObj;
            std::list<QJsonArray> roomList, dateError;
            rootObj.insert("Request","ok");
            rootObj.insert("StartDate",start.toString("yyyyMMdd"));
            rootObj.insert("EndDate",end.toString("yyyyMMdd"));
            for(int i = 0; i < days; i++){
                QJsonArray tempArray;
                int length = roomIdVec.size();
                for(int j = 0; j < length; j++){ //遍历房间数组，读取每个房间的信息
                    int roomId = roomIdVec[j];
                    QString date = start.addDays(i).toString("yyyyMMdd");
                    QJsonObject objItem;
                    ReportOne ro = Data::getReportOne(dbTime, dbStep, roomId, date);
                    objItem.insert("roomId", roomId);
                    objItem.insert("useACTimes", QString::number(ro.ACUseTimes));
                    objItem.insert("changeDegreeTimes", QString::number(ro.ChangeTempTimes));
                    objItem.insert("changeWindTimes", QString::number(ro.ChangeWindTimes));
                    objItem.insert("dispathTimes", QString::number(ro.ACdispatchedTimes));
                    objItem.insert("useACTime", QString::number(ro.ACUseTime));
                    objItem.insert("detailRecordRows", QString::number(ro.detailedNum));

                    tempArray.append(objItem);
                }
                rootObj.insert(start.addDays(i).toString("yyyyMMdd"), tempArray);//把该天的所有房间消息加入根Obj
            }
            qDebug()<<"finish query";
            QJsonDocument document;
            document.setObject(rootObj);
            QByteArray jsonArray = document.toJson(QJsonDocument::Compact);
            managerSocket->write(jsonArray);//发json
            //qDebug()<<jsonArray;
        }
        else if(getObj.value("User").toString()=="receptionist"){
            // from receptionist
            qDebug() << "From receptionist";
            qDebug() << getObj;
            // get bill
            if (getObj.value("Type").toString() == "bill")
            {
                int roomID = getObj.value("roomID").toString().toInt();
                Bill bill = Data::getBill(dbTime, dbStep, roomID);
                QJsonObject objItem;
                objItem.insert("roomID", bill.roomID);
                objItem.insert("checkintime", bill.checkInTime.toString());
                objItem.insert("checkouttime", bill.checkOutTime.toString());
                objItem.insert("payment", bill.payment);
                objItem.insert("bill", "");
                qDebug() << "Finish insert bill"<<objItem<<"******************************";

                QJsonDocument doc;
                doc.setObject(objItem);
                QByteArray jsArr = doc.toJson(QJsonDocument::Compact);
                receptionistSocket->write(jsArr);
                qDebug()<<jsArr;
            }

            //详单
            //改，查receptionistsocket
            else if (getObj.value("Type").toString() == "list")
            {
                int roomID = getObj.value("roomID").toString().toInt();
                List list = Data::getList(dbTime, dbStep, roomID);

                QJsonObject rootobj;
                QJsonArray jsArr;

                rootobj.insert("roomID", roomID);
                for (size_t i = 0; i < list.startTime.size(); i++)
                {
                    QJsonObject objItem;

                    objItem.insert("starttime", list.startTime[i].toString());
                    objItem.insert("endtime", list.endTime[i].toString());
                    objItem.insert("duration", QString::number((list.duration[i])));
                    objItem.insert("windspeed", QString::number(list.windSpeed[i]));
                    objItem.insert("rate", QString::number(list.rate[i]));
                    objItem.insert("fee", QString::number(list.fee[i]));

                    jsArr.append(objItem);
                }
                rootobj.insert("list", jsArr);
                qDebug()<<"Finish inserting";
                QJsonDocument doc;
                doc.setObject(rootobj);
                QByteArray resArr = doc.toJson(QJsonDocument::Compact);
                receptionistSocket->write(resArr);
                qDebug()<<resArr;

            }
            //入住
            else if (getObj.value("Type").toString() == "checkin")
            {
                qDebug() << "checking in";
                int i, roomID;
                int length = roomIdVec.size();

                for(i = 0; i < length; i++){
                    if (masterAirconditioner->roomStateMap[roomIdVec[i]]->occupied == 0)//如果该房间未被使用
                    {
                        masterAirconditioner->roomStateMap[roomIdVec[i]]->occupied = 1;
                        Data::checkIn(dbTime, dbStep, roomIdVec[i],
                                      QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
                        roomID = roomIdVec[i];
                        break;
                    }
                }
                if (i == length)
                {
                    int roomID = 0;
                }

                QJsonObject obj;
                obj.insert("checkin", "");
                obj.insert("roomID", roomID);
                QJsonDocument doc;
                doc.setObject(obj);
                QByteArray jsArr = doc.toJson(QJsonDocument::Compact);
                receptionistSocket->write(jsArr);
                qDebug()<<jsArr;
            }


            //退房
            else if (getObj.value("Type").toString() == "checkout")
            {
                qDebug() << "checking out";
                int roomID = getObj.value("roomID").toString().toInt();

                qDebug() << roomID;
                masterAirconditioner->roomStateMap[roomID]->occupied = 0;
                qDebug() << "get checkout request";
                Data::checkOut(dbTime, dbStep, roomID,
                               QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
                qDebug() << "already check out";
                QJsonObject obj;
                obj.insert("checkout", "");
                obj.insert("roomID", roomID);
                QJsonDocument doc;
                doc.setObject(obj);
                QByteArray jsArr = doc.toJson(QJsonDocument::Compact);
                receptionistSocket->write(jsArr);
                qDebug()<<jsArr;
            }
        }
    }
    else if(getObj.value("Header")=="roomState"){//返回房间状态
        QJsonObject jsonObj;
        jsonObj.insert("Request","ok");
        QJsonArray roomArray;
        for(int i = 0; i < roomIdVec.size(); i++)
        {
            QJsonObject roomObj;
            ClientState *clientState =  masterAirconditioner->clientStateMap.find(roomIdVec[i]).value();
            roomObj.insert("roomId", roomIdVec[i]);
            if(clientState->get_is_open())
                           roomObj.insert("powerOnOff", POWERON);
                       else
                           roomObj.insert("powerOnOff", POWEROFF);
            roomObj.insert("serveOrHangUp",clientState->get_status());
            roomObj.insert("currentTemp",clientState->get_cur_temp());
            roomObj.insert("targetTemp",clientState->get_target_temp());
            roomObj.insert("wind",clientState->get_cur_speed());
            roomObj.insert("feeRate",rate);
            roomObj.insert("fee", clientState->get_payment());
            roomObj.insert("serveTime",dbTime.getACUseTime(roomIdVec[i], QDate::currentDate().toString("yyyyMMdd")));

            roomArray.append(roomObj);
        }
        jsonObj.insert("roomState",roomArray);
        QJsonDocument document;
        document.setObject(jsonObj);
        QByteArray jsonArray = document.toJson(QJsonDocument::Compact);
        adminSocket->write(jsonArray);//发json
        qDebug()<<jsonArray;
    }
}
void Server::dispatch(int roomId,int tarWind,int tarAC)
{
    qDebug()<<"给请求"<<"roomId="<<roomId<<",tarWind="<<tarWind<<",tarAC="<<tarAC<<"进行调度";
    qDebug()<<"调度前的情况"<<endl;
    qDebug()<<"waiting[1]队列大小"<<masterAirconditioner->waitingQueue[1].size();
    qDebug()<<"waiting[2]队列大小"<<masterAirconditioner->waitingQueue[2].size();
    qDebug()<<"waiting[3]队列大小"<<masterAirconditioner->waitingQueue[3].size();
    qDebug()<<"running[1]队列大小"<<masterAirconditioner->runningQueue[1].size();
    qDebug()<<"running[2]队列大小"<<masterAirconditioner->runningQueue[2].size();
    qDebug()<<"running[3]队列大小"<<masterAirconditioner->runningQueue[3].size();
    qDebug()<<"hungry[1]队列大小"<<masterAirconditioner->hungryQueue[1].size();
    qDebug()<<"hungry[2]队列大小"<<masterAirconditioner->hungryQueue[2].size();
    if(tarAC==1&&tarWind!=0){//如果开关打开，且目标风速不为0，表明要表达请求
        int total = masterAirconditioner->runningQueue[1].size()+masterAirconditioner->runningQueue[2].size()+masterAirconditioner->runningQueue[3].size();
        if(!masterAirconditioner->isInQueue(roomId,0)&&!masterAirconditioner->isInQueue(roomId,1)&&!masterAirconditioner->isInQueue(roomId,2)){//如果当前roomId的请求，不在就绪准备饥饿队列中
            qDebug()<<"running队列中服务数="<<total;
            qDebug()<<"allClientQueueMap的大小="<<masterAirconditioner->allClientQueueMap.size();
            if(total<serveNum){//总数小于服务上限直接插入到running队列中
                masterAirconditioner->insertIntoQueue(roomId,tarWind,1);
                qDebug()<<"成功插入";
                //发送ok消息
                for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                    if((*i).first==roomId){
                        (*i).second->write(sendWindMessage("ok",tarWind));
                        (*i).second->flush();
                        break;
                    }

                }
            }
            else{//总数等于服务上限
                int i;
                for(i=1;i<tarWind;i++){//在小于目标风速的running队列中寻找
                    if(masterAirconditioner->runningQueue[i].size()!=0){//如果该running队列中有服务对象,就将其调到waiting队列，把新请求拿到running队列
                        int deleteRoomId = masterAirconditioner->runningQueue[i].back().first;
                        masterAirconditioner->insertIntoQueue(deleteRoomId,i,0);//把该从running队列中删除的先放到，waiting队列
                        masterAirconditioner->deleteFromQueue(deleteRoomId,i,1);//从running队列中删除
                        //发送停风消息并开启时钟
                        for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                            if((*i).first==deleteRoomId){
                                (*i).second->write(sendWindMessage("ok",0));
                                (*i).second->flush();
                                break;
                            }

                        }
                        //masterAirconditioner->allClientQueueMap[deleteRoomId]->second->write(sendWindMessage("error",0));
                        myStartTimer(deleteRoomId);
                        //插入到running队列
                        masterAirconditioner->insertIntoQueue(roomId,tarWind,1);
                        //发送送风消息并停止时钟
                        for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                            if((*i).first==roomId){
                                (*i).second->write(sendWindMessage("ok",tarWind));
                                (*i).second->flush();
                                break;
                            }

                        }
                        //masterAirconditioner->allClientQueueMap[roomId]->second->write(sendWindMessage("ok",tarWind));
                        myStopTimer(roomId);
                        break;
                    }
                }
                if(i==tarWind){//如果符合条件，表明，running队列中没有优先级比新请求低的
                    masterAirconditioner->insertIntoQueue(roomId,tarWind,0);//插入到等待队列中
                    myStartTimer(roomId);
                    for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                        if((*i).first==roomId){
                            (*i).second->write(sendWindMessage("error",0));
                            (*i).second->flush();
                            break;
                        }

                    }
                   // masterAirconditioner->allClientQueueMap[roomId]->second->write(sendWindMessage("error",0));
                }
            }
        }
        else if(masterAirconditioner->isInQueue(roomId,0)){//如果在waiting队列
            int oldWind = masterAirconditioner->findFromWaitingQueue(roomId);
            qDebug()<<roomId <<" " <<oldWind<<" "<<tarWind;
            if(tarWind>oldWind){//如果新的请求的使得waiting中某一个变高，就将其从waiting中删去，然后将这个请求作为新请求调用dispatch，但是这样会使得两个时钟重新开始计时，就是说，虽然得到了更高的优先级，但是在时间片与饥饿调度上会落后
                qDebug()<<"从waiting队列调高风";
                myStopTimer(roomId);
                masterAirconditioner->deleteFromQueue(roomId,oldWind,0);
                qDebug()<<"waiting升风后的队列"<<endl;
                showDispatchResult();
                dispatch(roomId,tarWind,tarAC);
            }
            else if(tarWind<oldWind){//如果降低，就直接降低
                qDebug()<<"从waiting队列调高风";
                masterAirconditioner->insertIntoQueue(roomId,tarWind,0);//将现在的插入
                masterAirconditioner->deleteFromQueue(roomId,oldWind,0);//将原来的删除，完成交换队列
            }
        }
        else if(masterAirconditioner->isInQueue(roomId,1)){//如果在running队列
            int oldWind = masterAirconditioner->findFromRunningQueue(roomId);
            qDebug()<<"调高前";
            if(tarWind>oldWind){//如果新的请求的使得running中某一个变高，改变其位置即可
                masterAirconditioner->insertIntoQueue(roomId,tarWind,1);
                masterAirconditioner->deleteFromQueue(roomId,oldWind,1);
                qDebug()<<"将running中对应调整"<<endl;
                for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                    if((*i).first==roomId){
                        (*i).second->write(sendWindMessage("ok",tarWind));
                        (*i).second->flush();
                        break;
                    }

                }
                //masterAirconditioner->allClientQueueMap[roomId]->second->write(sendWindMessage("ok",tarWind));
            }
            else if(tarWind<oldWind){//如果降低，看比tarWind高一级的waiting队列中是否有成员，如果有将其换入
                qDebug()<<"running队列中降温";
                if(masterAirconditioner->waitingQueue[tarWind+1].size()!=0){//有成员
                    qDebug()<<"如果比tarWind优先级高的waiting队列中有成员";
                    int waitRoomId = masterAirconditioner->waitingQueue[tarWind+1].back().first;//等待调入running的房间号
                    //关闭时钟
                    masterAirconditioner->insertIntoQueue(waitRoomId,tarWind+1,1);
                    masterAirconditioner->deleteFromQueue(waitRoomId,tarWind+1,0);//完成waitRoomId房间从waiting到running的变换
                    //发送ok消息并关闭时钟
                    for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                        if((*i).first==waitRoomId){
                            (*i).second->write(sendWindMessage("ok",tarWind+1));
                            (*i).second->flush();
                            break;
                        }

                    }
                    //masterAirconditioner->allClientQueueMap[waitRoomId]->second->write(sendWindMessage("ok",tarWind+1));
                    myStopTimer(waitRoomId);
                    masterAirconditioner->insertIntoQueue(roomId,tarWind,0);
                    masterAirconditioner->deleteFromQueue(roomId,oldWind,1);//完成roomId房间从running到waiting的变换
                    //发送error开启调入等待队列的时钟
                    for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                        if((*i).first==roomId){
                            (*i).second->write(sendWindMessage("error",0));
                            (*i).second->flush();
                            break;
                        }

                    }
                    //masterAirconditioner->allClientQueueMap[roomId]->second->write(sendWindMessage("error",0));
                    myStartTimer(roomId);
                    qDebug()<<"running降风后的队列"<<endl;
                    showDispatchResult();
                }
                else{
                    masterAirconditioner->insertIntoQueue(roomId,tarWind,1);
                    masterAirconditioner->deleteFromQueue(roomId,oldWind,1);
                    for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                        if((*i).first==roomId){
                            (*i).second->write(sendWindMessage("ok",tarWind));
                            (*i).second->flush();
                            break;
                        }

                    }
                    //masterAirconditioner->allClientQueueMap[roomId]->second->write(sendWindMessage("ok",tarWind));
                }

            }
        }
        else if(masterAirconditioner->isInQueue(roomId,2)){//如果在饥饿队列
            int oldWind = masterAirconditioner->findFromHungryQueue(roomId);
            if(tarWind>oldWind){//如果新的请求的使得running中某一个变高，改变其位置即可
                if(tarWind==3){
                    masterAirconditioner->insertIntoQueue(roomId,tarWind,0);
                    masterAirconditioner->deleteFromQueue(roomId,oldWind,2);
                    qDebug()<<"将hungry中对应调整"<<endl;
                    myStartTimer(roomId);
                }
                else{
                    masterAirconditioner->insertIntoQueue(roomId,tarWind,2);
                    masterAirconditioner->deleteFromQueue(roomId,oldWind,2);
                }
                //masterAirconditioner->allClientQueueMap[roomId]->second->write(sendWindMessage("ok",tarWind));
            }
            else if(tarWind < oldWind){
                masterAirconditioner->insertIntoQueue(roomId,tarWind,2);
                masterAirconditioner->deleteFromQueue(roomId,oldWind,2);
                qDebug()<<"将hungry中对应调整"<<endl;
            }
        }
    }
    else if(tarAC==0||tarWind==0){//如果开关关闭，或者风速为0，表明要
        qDebug()<<"处理停风"<<endl;
        masterAirconditioner->deleteFromQueue(roomId);//停风，从waiting,running,hungry队列中剔除
        //发送停风并关闭时钟
        qDebug()<<"成功删除 "<<roomId<<endl;
        //qDebug()<<*masterAirconditioner->allClientQueueMap[roomId];
        for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
            if((*i).first==roomId){
                (*i).second->write(sendWindMessage("error",0));
                (*i).second->flush();
                break;
            }
        }
       //masterAirconditioner->allClientQueueMap[roomId]->second->write(sendWindMessage("error",0));
        qDebug()<<"成功发送返回消息"<<endl;
        myStopTimer(roomId);
        int total = masterAirconditioner->runningQueue[1].size()+masterAirconditioner->runningQueue[2].size()+masterAirconditioner->runningQueue[3].size();
        int hungryTotal = masterAirconditioner->hungryQueue[1].size()+masterAirconditioner->hungryQueue[2].size();
        int waitingTotal = masterAirconditioner->waitingQueue[1].size()+masterAirconditioner->waitingQueue[2].size()+masterAirconditioner->waitingQueue[3].size();
        if(total<serveNum){
            if(hungryTotal!=0){//如果饥饿队列不为空，且running队列中服务数量小于服务上限
                int insertRoomId=0;
                int hungWind = 0;
                for(int i=2;i>=1;i--){
                    if(masterAirconditioner->hungryQueue[i].size()>0){
                        insertRoomId = masterAirconditioner->hungryQueue[i].back().first;
                        hungWind = i;
                        break;
                    }
                }
                masterAirconditioner->insertIntoQueue(insertRoomId,hungWind,1);//将hungry队列的尾部放到对应running中
                masterAirconditioner->deleteFromQueue(insertRoomId,hungWind,2);//将hungry队列尾部删去
                for(auto i=masterAirconditioner->allClientQueue.begin();i!=masterAirconditioner->allClientQueue.end();i++){
                    if((*i).first==insertRoomId){
                        (*i).second->write(sendWindMessage("ok",hungWind));
                        (*i).second->flush();
                        break;
                    }

                }
                //masterAirconditioner->allClientQueueMap[insertRoomId]->second->write(sendWindMessage("ok",masterAirconditioner->clientStateMap[insertRoomId]->get_target_speed()));
            }
            else if(hungryTotal==0){//如果饥饿队列为空，且running队列中服务数量小于服务上限,看waiting队列的情况
                if(waitingTotal!=0){//如果waiting队列
                    for(int i = 3;i>= 1;i--){
                        if(masterAirconditioner->waitingQueue[i].size()>0){
                            int insertRoomId = masterAirconditioner->waitingQueue[i].back().first;//等待队列尾部请求的房间号
                            masterAirconditioner->insertIntoQueue(insertRoomId,i,1);//将waiting队列的尾部放到对应running中
                            masterAirconditioner->deleteFromQueue(insertRoomId,i,0);//将waiting队列尾部删去
                            myStopTimer(insertRoomId);
                            for(auto j=masterAirconditioner->allClientQueue.begin();j!=masterAirconditioner->allClientQueue.end();j++){
                                if((*j).first==insertRoomId){
                                    (*j).second->write(sendWindMessage("ok",i));
                                    (*j).second->flush();
                                    break;
                                }
                            }
                            //masterAirconditioner->allClientQueueMap[insertRoomId]->second->write(sendWindMessage("ok",i));
                            break;
                        }
                    }
                }
            }
        }
    }
    qDebug()<<"调度后的情况"<<endl;
    showDispatchResult();
}
QByteArray Server::sendWindMessage(QString State,int Wind)
{
    QJsonObject obj;
    obj.insert("Header","returnWind");
    obj.insert("Wind",Wind);
    QJsonDocument doc(obj);
    QByteArray msg = doc.toJson();
    return msg;
}

QByteArray Server::sendParamsMessage()
{
    QJsonObject obj;
    obj.insert("Header","returnParams");
    obj.insert("defaultTemp", defaultTemp);
    obj.insert("defaultWind", defaultWind);
    obj.insert("maxTempOnModeCold", maxTempOnModeCold);
    obj.insert("maxTempOnModeHeat", maxTempOnModeHeat);
    obj.insert("minTempOnModeCold", minTempOnModeCold);
    obj.insert("minTempOnModeHeat", minTempOnModeHeat);
    obj.insert("rate", rate);
    QJsonDocument doc(obj);
    QByteArray msg = doc.toJson();
    return msg;
}

void Server::slotTimeSlot(int roomId,int wind)//时间片调度，如果同风的running队列中有对象存在，就换出，并把请求换入，如果没对象，就不用管了
{
    qDebug()<<"准备调入running队列的房间号为"<<roomId<<",目标风速为"<<wind;
    qDebug()<<"running["<<wind<<"]"<<"队列的大小为"<<masterAirconditioner->runningQueue[wind].size()<<",可进行调度";
    if(masterAirconditioner->runningQueue[wind].size()!=0){
        qDebug()<<"准备进行时间片调度";
        int deleteRoomId = masterAirconditioner->runningQueue[wind].back().first;
        masterAirconditioner->insertIntoQueue(deleteRoomId,wind,0);//将对应风速的running队列中的最后一个插入到waitingQ队列
        masterAirconditioner->deleteFromQueue(deleteRoomId,wind,1);//将还没从running队列中删去的对象删去
        for(auto j=masterAirconditioner->allClientQueue.begin();j!=masterAirconditioner->allClientQueue.end();j++){
            if((*j).first==deleteRoomId){
                (*j).second->write(sendWindMessage("error",0));
                (*j).second->flush();
                break;
            }

        }
        for(auto j=masterAirconditioner->allClientQueue.begin();j!=masterAirconditioner->allClientQueue.end();j++){
            if((*j).first==roomId){
                (*j).second->write(sendWindMessage("ok",wind));
                (*j).second->flush();
                break;
            }

        }
        masterAirconditioner->insertIntoQueue(roomId,wind,1);//把该请求放到running中
        masterAirconditioner->deleteFromQueue(roomId,wind,0);//把该请求从waiting队列中删除
        //将进入running队列的时钟停掉
        myStopTimer(roomId);
        //进入等待队列的需要打开时钟
        myStartTimer(deleteRoomId);
        //将新进入等待队列的请求打开两个时钟，连接槽函数
        //加入到running队列的请求关闭两个时钟
        qDebug()<<"时间片调度后的情况"<<endl;
        showDispatchResult();
    }
}
void Server::slotHungryInsert(int roomId,int wind)
{
    masterAirconditioner->insertIntoQueue(roomId,wind,2);//把该请求放到hungry中
    masterAirconditioner->deleteFromQueue(roomId,wind,0);//把该请求从waiting队列中删除
    myStopTimer(roomId);
    qDebug()<<"到了饥饿时间后的情况"<<endl;
    showDispatchResult();
}
void Server::myStartTimer(int roomId)
{
    QTimer *timer1 = masterAirconditioner->clientStateMap[roomId]->timer1;
    QTimer *timer2 = masterAirconditioner->clientStateMap[roomId]->timer2;
    timer1->start(TIME_SLOT);
    timer2->start(TIME_HUNGRY);
    qDebug()<<roomId<<"时钟开启";
    connect(timer1,SIGNAL(timeout()),masterAirconditioner->clientStateMap[roomId],SLOT(slotSendRunningClient()));
    connect(masterAirconditioner->clientStateMap[roomId],SIGNAL(sigSendRunningClient(int,int)),this,SLOT(slotTimeSlot(int,int)));
    connect(timer2,SIGNAL(timeout()),masterAirconditioner->clientStateMap[roomId],SLOT(slotSendHungryClient()));
    connect(masterAirconditioner->clientStateMap[roomId],SIGNAL(sigSendHungryClient(int,int)),this,SLOT(slotHungryInsert(int,int)));
}
void Server::myStopTimer(int roomId)
{
    QTimer *timer1 = masterAirconditioner->clientStateMap[roomId]->timer1;
    QTimer *timer2 = masterAirconditioner->clientStateMap[roomId]->timer2;
    disconnect(timer1,SIGNAL(timeout()),masterAirconditioner->clientStateMap[roomId],SLOT(slotSendRunningClient()));
    disconnect(masterAirconditioner->clientStateMap[roomId],SIGNAL(sigSendRunningClient(int,int)),this,SLOT(slotTimeSlot(int,int)));
    disconnect(timer2,SIGNAL(timeout()),masterAirconditioner->clientStateMap[roomId],SLOT(slotSendHungryClient()));
    disconnect(masterAirconditioner->clientStateMap[roomId],SIGNAL(sigSendHungryClient(int,int)),this,SLOT(slotHungryInsert(int,int)));
    masterAirconditioner->clientStateMap[roomId]->timer1->stop();
    masterAirconditioner->clientStateMap[roomId]->timer2->stop();
}
void Server::showDispatchResult()
{
    for(int i=1;i<=3;i++){
        qDebug()<<"waiting["<<i<<"]队列大小"<<masterAirconditioner->waitingQueue[i].size();
        qDebug()<<"running["<<i<<"]队列大小"<<masterAirconditioner->runningQueue[i].size();
    }
    qDebug()<<"hungry[1]队列大小"<<masterAirconditioner->hungryQueue[1].size();
    qDebug()<<"hungry[2]队列大小"<<masterAirconditioner->hungryQueue[2].size();

    for(int i=1;i<=3;i++){
        qDebug()<<"在waiting["<<i<<"]中";
        for(auto j=masterAirconditioner->waitingQueue[i].begin();j!=masterAirconditioner->waitingQueue[i].end();j++){
            qDebug()<<j->first;
        }
        qDebug()<<"在running["<<i<<"]中";
        for(auto j=masterAirconditioner->runningQueue[i].begin();j!=masterAirconditioner->runningQueue[i].end();j++){
            qDebug()<<j->first;
        }
        if(i<=2){
            qDebug()<<"在hungry["<<i<<"]中";
            for(auto j=masterAirconditioner->hungryQueue[i].begin();j!=masterAirconditioner->hungryQueue[i].end();j++){
                qDebug()<<j->first;
            }
        }

    }
}
