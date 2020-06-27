#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
    managerController = new ManagerController();
    initUI();
    initConnect();
}

Manager::~Manager()
{
    delete ui;
}

void Manager::initUI()
{
    ui->textBrowser->setText(nullptr);
    ui->startTime->setDate(QDate::currentDate());
    ui->endTime->setDate(QDate::currentDate());
    qDebug()<<"Successfully init manager UI";
}

void Manager::initConnect()
{
    connect(ui->pushButton_checkreport, SIGNAL(clicked()), this, SLOT(checkReport()));
    connect(ui->pushButton_download, SIGNAL(clicked()), this, SLOT(download()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(managerController, SIGNAL(sigGetReport()), this, SLOT(showReport()));
}

void Manager::checkReport()
{
    ui->textBrowser->clear();
    managerController->createReport(ui->startTime->date(), ui->endTime->date());
}

void Manager::showReport()
{
    QString title("  日期\t 房间号\t空调使用次数   调温次数  调风次数  被调度次数  空调使用时长  详单记录数  总费用\n");
    //显示报表内容
    ui->textBrowser->insertPlainText(title);
    std::list<record> tempRecords = managerController->report->getRecords();
    std::list<record>::iterator it;
    qDebug()<<tempRecords.size();
    for(it = tempRecords.begin(); it != tempRecords.end(); ++it){
        QString info = it->date.toString("yyyy-MM-dd") + "  " + it->roomId + "\t     " + QString::number(it->useACTimes)
                + "\t       " + QString::number(it->changeDegreeTimes) + "\t       " + QString::number(it->changeWindTimes) + "\t       "
                + QString::number(it->dispathTimes) + "\t          " + QString::number(it->useACtime) + "\t  "
                + QString::number(it->detailRecordRows) + "\t  " + QString::number(0) + "\n";
        ui->textBrowser->insertPlainText(info);
    }
}

void Manager::download()
{
    managerController->downLoad();
}

void Manager::quit()
{
    qDebug()<<"Manager exit";
    emit quitSignal();
}
