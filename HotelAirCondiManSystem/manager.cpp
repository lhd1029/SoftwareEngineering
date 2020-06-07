#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
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
    connect(ui->pushButton_checkreport, SIGNAL(clicked()), this, SLOT(clickCheckReport()));
    connect(ui->pushButton_download, SIGNAL(clicked()), this, SLOT(clickDwonload()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(clickQuit()));
}

void Manager::checkReport()
{
    managerController.createReport(ui->startTime->date(), ui->endTime->date());
    QString title = "日期   房间号  空调使用次数 常用目标温度 常用风速 达到目标温度次数 被调度次数 详单记录数 总费用\n";
    //显示报表内容
    ui->textBrowser->insertPlainText(title);
    std::list<record> tempRecords = managerController.report.getRecords();
    std::list<record>::iterator it;
    for(it = tempRecords.begin(); it != tempRecords.end(); ++it){
        QString info = it->date.toString() + "\t" + QString::number(it->roomId) + "\t" + QString::number(it->comTarDegree)
                + "\t" + QString::number(it->comWind) + "\t" + QString::number(it->getTarDegreeTimes) + "\t"
                + QString::number(it->dispathTimes) + "\t" + QString::number(it->detailRecordRows) + "\t"
                + QString::number(it->totalmoney) + "\n";
        ui->textBrowser->insertPlainText(info);
    }
}

void Manager::dwonload()
{
    managerController.downLoad();
}

void Manager::quit()
{
    qDebug()<<"Manager exit";
    emit quitSignal();
}
