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
    //qDebug()<<"Successfully initialize manager UI";
}

void Manager::initConnect()
{
    connect(ui->pushButton_checkreport, SIGNAL(clicked()), this, SLOT(clickCheckReport()));
    connect(ui->pushButton_download, SIGNAL(clicked()), this, SLOT(clickDwonload()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(clickQuit()));
}

void Manager::clickCheckReport()
{
    Report *report = new Report(ui->startTime->date(), ui->endTime->date());
    QString title = "日期\t房间号\t空调使用次数\t常用目标温度\t常用风速\t达到目标温度次数\t被调度次数\t详单记录数\t总费用\n";
    //显示报表内容
    ui->textBrowser->insertPlainText(title);
    for(int i = 0; i < ROOMNUM; i++){
        records r = report->getRecord(i);
        QString info = r.date.toString() + QString::number(r.roomId) + QString::number(r.comTarDegree) + QString::number(r.comWind)
                + QString::number(r.getTarDegreeTimes) + QString::number(r.dispathTimes) + QString::number(r.detailRecordRows) + QString::number(r.totalmoney);
        ui->textBrowser->insertPlainText(info);
    }
}

void Manager::clickDwonload()
{

}

void Manager::clickQuit()
{

}
