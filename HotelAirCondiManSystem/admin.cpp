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

    //系统已经启动
    if(adminController->getPowerOnOrOff() == POWERON){
        restorConfig();
    }
    else {
        initUI();//初始化系统
    }

    timer = new QTimer();
    //设置定时器每隔1分钟发送一个timeout()信号
    timer->setInterval(10000);
    //启动定时器
    timer->start();
    initConnect();
}

Admin::~Admin()
{
    delete ui;
    delete adminController;
}

void Admin::initUI()
{
    ui->spinbox_defaultTemp->setValue(26);
    ui->spinBox_lowLimit->setValue(18);
    ui->spinBox_highLimit->setValue(30);
    ui->spinbox_feeRate->setValue(1);
    ui->spinBox_serveNum->setValue(3);
    qDebug()<<"Successfully init admin UI";

    paraEditable(false);
}

void Admin::initConnect()
{
    connect(ui->pushButton_checkState, SIGNAL(clicked()), this, SLOT(checkState()));
    connect(ui->pushButton_changeAircon, SIGNAL(clicked()), this, SLOT(changeAirconState()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->checkBox_aricon, SIGNAL(clicked()), this, SLOT(changeParaEditable()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
}

//恢复配置
void Admin::restorConfig()
{
    ui->checkBox_aricon->isChecked();
    ui->combobox_controlPattern->setCurrentIndex(adminController->getTempPattern());
    ui->spinbox_feeRate->setValue(adminController->getFeeRate());
    ui->spinbox_defaultTemp->setValue(adminController->getDefaulttemp());
    ui->spinBox_lowLimit->setValue(adminController->getTempLimitLow());
    ui->spinBox_serveNum->setValue(adminController->getServeNum());
    ui->spinBox_highLimit->setValue(adminController->getTempLimitHigh());
    paraEditable(true);
    qDebug()<<"Successfully restore aircondition system config";
}

//设置参数可否编辑
void Admin::paraEditable(bool editable)
{
    ui->combobox_controlPattern->setEditable(editable);
    ui->spinbox_feeRate->setEnabled(editable);
    ui->spinBox_lowLimit->setEnabled(editable);
    ui->spinBox_serveNum->setEnabled(editable);
    ui->spinBox_highLimit->setEnabled(editable);
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

void Admin::checkState()
{
    checkStateclicked = 1;
    updateState();
}

//状态更新
void Admin::updateState()
{
    if(checkStateclicked)
    {
        adminController->createStateList();
        std::list<roomState> templist = adminController->getStateList();//遍历房间状态
        ui->textBrowser_state->setText("房间号\t状态\t当前温度\t目标温度\t风速\t费率\t持续时间\t");
        QString s, currentACState; //输出字符串、当前空调状态字符串
        std::list<roomState>::iterator it;
        for(it = templist.begin(); it != templist.end(); ++it){
            if(it->powerOnOff == POWEROFF)
                currentACState="关闭";
            else {
                if(it->serveOrHangUp == SERVE)
                    currentACState="服务";
                else
                    currentACState="挂起";
            }
            s=QString::number(it->roomId) + "\t" + currentACState + "\t" + QString::number(it->currentTemp) + "\t" +
                    QString::number(it->targetTemp) + "\t" + QString::number(it->wind) + "\t" + QString::number(it ->feeRate)
                     + "\t" + QString::number(it->serveTime);
            ui->textBrowser_state->insertPlainText(s);
        }
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

            adminController->setParam(ui->combobox_controlPattern->currentIndex(), ui->spinbox_defaultTemp->value(),
                                      ui->spinBox_lowLimit->value(), ui->spinBox_highLimit->value(),
                                      ui->spinbox_feeRate->value(), ui->spinBox_serveNum->value());
            qDebug()<<"Successfully change AC state";
        }
    }
    else if(!ui->checkBox_aricon->isChecked() && adminController->getPowerOnOrOff() == POWERON)
    {
        QMessageBox messageBox(QMessageBox::NoIcon, "操作确认", "确认关闭空调系统", QMessageBox::Yes|QMessageBox::No); ;
    }
}

//退出系统
void Admin::quit()
{
    qDebug()<<"admin exit";
    emit quitSignal();
}
