#include "admin.h"
#include "ui_admin.h"
#define POWERON 1
#define POWEROFF 0
#define SERVE 1
#define HANGUP 0

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    checkStateclicked = 0;
    adminController = new AdminController();
    adminController->checkConfig();

    timer = new QTimer();
    //设置定时器每隔1分钟发送一个timeout()信号
    timer->setInterval(60000);

    ui->checkBox_aricon->setEnabled(false);
    paraEditable(false);

    initConnect();
}

Admin::~Admin()
{
    delete ui;
    delete adminController;
}

void Admin::initConnect()
{
    connect(ui->pushButton_checkState, SIGNAL(clicked()), this, SLOT(checkState()));
    connect(ui->pushButton_changeAircon, SIGNAL(clicked()), this, SLOT(changeAirconState()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->checkBox_aricon, SIGNAL(clicked()), this, SLOT(changeParaEditable()));
    connect(ui->checkBox_coldPattern, SIGNAL(clicked()), this, SLOT(changeColdPattern()));
    connect(ui->checkBox_hotPattern, SIGNAL(clicked()), this, SLOT(changeHotPattern()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    connect(adminController, SIGNAL(sigGetRoomState()), this, SLOT(showState()));
    connect(adminController, SIGNAL(sigGetConfig()), this, SLOT(restoreConfig()));
}

//恢复配置
void Admin::restoreConfig()
{
    QMessageBox::information(NULL, "提示", "配置恢复成功");
    ui->combobox_defaultWind->setCurrentIndex(adminController->getDefaultWind());
    ui->spinbox_feeRate->setValue(adminController->getFeeRate());
    ui->spinbox_defaultTemp->setValue(adminController->getDefaulttemp());
    ui->spinBox_serveNum->setValue(adminController->getServeNum());
    ui->checkBox_aricon->setEnabled(true);
    if(adminController->getPowerOnOrOff() == POWERON){
        ui->checkBox_aricon->setChecked(true);
        paraEditable(true);
        if(adminController->getColdLimitLow() != 0)
        {
            ui->checkBox_coldPattern->setChecked(true);
            ui->spinBox_coldLowLimit->setValue(adminController->getColdLimitLow());
            ui->spinBox_coldHighLimit->setValue(adminController->getColdLimitHigh());
        }
        else {
            ui->checkBox_coldPattern->setChecked(false);
            ui->spinBox_coldLowLimit->setValue(0);
            ui->spinBox_coldHighLimit->setValue(0);
        }
        if(adminController->getHotLimitLow() != 0)
        {
            ui->checkBox_hotPattern->setChecked(true);
            ui->spinBox_hotLowLimit->setValue(adminController->getHotLimitLow());
            ui->spinBox_hotHighLimit->setValue(adminController->getHotLimitHigh());
        }
        else {
            ui->checkBox_hotPattern->setChecked(false);
            ui->spinBox_hotLowLimit->setValue(0);
            ui->spinBox_hotHighLimit->setValue(0);
        }
    }
    else {
        ui->checkBox_aricon->setChecked(false);
        ui->checkBox_hotPattern->setChecked(false);
        ui->checkBox_coldPattern->setChecked(false);
        ui->spinBox_coldLowLimit->setValue(0);
        ui->spinBox_coldHighLimit->setValue(0);
        ui->spinBox_hotLowLimit->setValue(0);
        ui->spinBox_hotHighLimit->setValue(0);
    }
    qDebug()<<"Successfully restore aircondition system config";
}

//设置参数可否编辑
void Admin::paraEditable(bool editable)
{
    ui->combobox_defaultWind->setEditable(editable);
    ui->spinbox_feeRate->setEnabled(editable);
    ui->checkBox_hotPattern->setEnabled(editable);
    ui->checkBox_coldPattern->setEnabled(editable);
    //ui->spinBox_coldLowLimit->setEnabled(editable);
    //ui->spinBox_coldHighLimit->setEnabled(editable);
    //ui->spinBox_hotHighLimit->setEnabled(editable);
    //ui->spinBox_hotLowLimit->setEnabled(editable);
    ui->spinBox_serveNum->setEnabled(editable);
    ui->spinbox_defaultTemp->setEnabled(editable);
}

//改变参数编辑状态
void Admin::changeParaEditable()
{
    if(ui->checkBox_aricon->isChecked())
        paraEditable(true);
    else
        paraEditable(false);
}

void Admin::changeColdPattern()
{
    if(ui->checkBox_coldPattern->isChecked())
    {
        ui->spinBox_coldLowLimit->setValue(18);
        ui->spinBox_coldHighLimit->setValue(25);
        ui->spinBox_coldLowLimit->setEnabled(true);
        ui->spinBox_coldHighLimit->setEnabled(true);
    }
    else {
        ui->spinBox_coldLowLimit->setValue(0);
        ui->spinBox_coldHighLimit->setValue(0);
        ui->spinBox_coldLowLimit->setEnabled(false);
        ui->spinBox_coldHighLimit->setEnabled(false);
    }
}

void Admin::changeHotPattern()
{
    if(ui->checkBox_hotPattern->isChecked())
    {
        ui->spinBox_hotLowLimit->setValue(25);
        ui->spinBox_hotHighLimit->setValue(30);
        ui->spinBox_hotLowLimit->setEnabled(true);
        ui->spinBox_hotHighLimit->setEnabled(true);
    }
    else {
        ui->spinBox_hotLowLimit->setValue(0);
        ui->spinBox_hotHighLimit->setValue(0);
        ui->spinBox_hotLowLimit->setEnabled(false);
        ui->spinBox_hotHighLimit->setEnabled(false);
    }
}

//点击检查房间状态
void Admin::checkState()
{
    //启动定时器
    checkStateclicked = 1;
    timer->start();
    updateState();
    qDebug()<<"push checkState button";
}

//状态更新
void Admin::updateState()
{
    if(checkStateclicked)
    {
        adminController->createStateList();
    }
}

//显示房间状态
void Admin::showState()
{
    ui->textBrowser_state->clear();
    std::list<roomState> templist = adminController->getStateList();//遍历房间状态
    ui->textBrowser_state->insertPlainText("房间号\t状态\t当前温度\t目标温度\t风速\t费率\t持续时间\t费用\n");
    QString s, currentACState, currentWind; //输出字符串、当前空调状态字符串
    std::list<roomState>::iterator it;
    for(it = templist.begin(); it != templist.end(); ++it){
        if(it->powerOnOff == POWEROFF)
            currentACState="关闭";
        else {
            if(it->serveOrHangUp == RUNNING)
                currentACState="服务";
            else
                currentACState="挂起";
        }
        if(it->wind == NOWIND)
            currentWind = "无风";
        else if(it->wind == WINDLOW)
            currentWind = "低风";
        else if(it->wind == WINDMID)
            currentWind = "中风";
        else
            currentWind = "高风";
        qDebug()<< it->wind <<" output "<<currentWind;
        s=QString::number(it->roomId) + "\t" + currentACState + "\t  " + QString::number(it->currentTemp) + "\t  " +
                QString::number(it->targetTemp) + "\t" + currentWind + "\t  " + QString::number(it ->feeRate)
                 + "\t  " + QString::number(it->serveTime) + "\t  " + QString::number(it->fee) + "\n";
        ui->textBrowser_state->insertPlainText(s);
    }
}

//修改空调状态（开启/关闭）
void Admin::changeAirconState()
{
    if(ui->checkBox_aricon->isChecked() && adminController->getPowerOnOrOff() == POWEROFF)
    {
        QMessageBox messageBox(QMessageBox::NoIcon, "操作确认", "确认开启空调系统", QMessageBox::Yes|QMessageBox::No); ;
        int result=messageBox.exec();
        if(result == QMessageBox::Yes){
            qDebug()<<"Start aricondition system";
            adminController->setParam(ui->combobox_defaultWind->currentIndex(), ui->spinbox_defaultTemp->value(),
                                      ui->spinBox_coldLowLimit->value(), ui->spinBox_coldHighLimit->value(),
                                      ui->spinBox_hotLowLimit->value(), ui->spinBox_hotHighLimit->value(),
                                      ui->spinbox_feeRate->value(), ui->spinBox_serveNum->value());
            qDebug()<<"Successfully change AC state";
        }
        else{
            restoreConfig();
        }
    }
    else if(!ui->checkBox_aricon->isChecked() && adminController->getPowerOnOrOff() == POWERON)
    {
        QMessageBox messageBox(QMessageBox::NoIcon, "操作确认", "确认关闭空调系统", QMessageBox::Yes|QMessageBox::No);
        int result = messageBox.exec();
        if(result == QMessageBox::Yes){
            adminController->setParam(POWEROFF);
        }
        else {
            restoreConfig();
        }
    }
}

//退出系统
void Admin::quit()
{
    qDebug()<<"admin exit";
    emit quitSignal();
}
