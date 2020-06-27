#include "managercontroller.h"

ManagerController::ManagerController()
{
    tcpManager = new TcpManager();
    QJsonObject json;
    json.insert("Header", "init");
    json.insert("User", "manager");
    QJsonDocument document;
    document.setObject(json);
    QByteArray msg = document.toJson(QJsonDocument::Compact);
    tcpManager->write(msg);
    QString strJson(msg);
    qDebug() << strJson;
    connect(tcpManager, SIGNAL(sigDataReturn(QByteArray)), this, SLOT(slotDealReturn(QByteArray)));
}

void ManagerController::createReport(QDate start, QDate end)
{
    report = new Report(start, end);
    QJsonObject json;
    json.insert("Header", "request");
    json.insert("User", "manager");
    json.insert("StartDate", start.toString("yyyyMMdd"));
    json.insert("EndDate",end.toString("yyyyMMdd"));
    QJsonDocument document;
    document.setObject(json);
    QByteArray msg = document.toJson(QJsonDocument::Compact);
    tcpManager->write(msg);
    QString strJson(msg);
    qDebug() << strJson;
}

void ManagerController::slotDealReturn(QByteArray msg)
{
    QJsonParseError e;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(msg, &e);
    QJsonObject getObj;
    if(e.error == QJsonParseError::NoError && ! jsonDoc.isNull())
    {
        getObj = jsonDoc.object();
        //json消息解析
        if(getObj.contains("StartDate") && getObj.contains("EndDate")){
            qDebug()<<"receive json from server";
            QDate startDate = QDate::fromString(getObj.value("StartDate").toString( ),"yyyyMMdd");
            QDate endDate = QDate::fromString(getObj.value("EndDate").toString(),"yyyyMMdd");
            std::list<record> reportRecord;
            for(int i = 0; i < startDate.daysTo(endDate) + 1; i++){
                QJsonArray dateArray = getObj.value(startDate.addDays(i).toString("yyyyMMdd")).toArray();
                for(int j = 0; j < dateArray.size(); j++)
                {
                    struct record temp;
                    temp.date = startDate.addDays(i);
                    QJsonObject roomObj = dateArray[j].toObject();
                    temp.roomId = roomObj.value("roomId").toString();
                    temp.useACtime = roomObj.value("useACTimes").toString().toInt();
                    temp.changeDegreeTimes = roomObj.value("changeDegreeTimes").toString().toInt();
                    temp.changeWindTimes = roomObj.value("changeWindTimes").toString().toInt();
                    temp.dispathTimes = roomObj.value("dispatchTimes").toString().toInt();
                    temp.useACtime = roomObj.value("useACTimes").toString().toInt();
                    temp.detailRecordRows = roomObj.value("detailRecordRows").toString().toInt();

                    reportRecord.push_back(temp);
                }
            }
            report->setRecords(reportRecord);
            emit sigGetReport();
        }
        else{
            qDebug()<<"Json contains Error";
        }
    }
    else {
        qDebug() << "从服务器接收消息失败";
    }
}

void ManagerController::downLoad()
{
    std::list<record> tempRecords = report->getRecords();

    QList<QString> columnNames;
    QList<int> columnWidths;
    columnNames << "日期" << "房间号" << "空调使用次数" << "调温次数" << "调风次数" << "被调度次数" << "空调使用时长" << "详单记录数" << "总费用";
    columnWidths << 150 << 150 << 150 << 150 << 150 << 150 << 150 << 150 << 150;

    QXlsx::Document xlsx("/报表.xlsx");
    for (int i = 1; i <= columnNames.size(); i++)
    {
        xlsx.write(1, i, columnNames[i]);
    }
    auto it = tempRecords.begin();
    for (int i = 2; i <= tempRecords.size()+1; i++, it++)
    {
        xlsx.write(i, 1, it->date);
        xlsx.write(i, 2, it->roomId);
        xlsx.write(i, 3, it->useACTimes);
        xlsx.write(i, 4, it->changeDegreeTimes);
        xlsx.write(i, 5, it->changeWindTimes);
        xlsx.write(i, 6, it->dispathTimes);
        xlsx.write(i, 7, it->useACtime);
        xlsx.write(i, 8, it->detailRecordRows);
        xlsx.write(i, 9, it->totalmoney);
    }
    xlsx.save();
}


