#include "client.h"
#include "ui_client.h"


Client::Client(int roomId, std::string userName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    cc = new ClientController();
    this->roomId = roomId;
    this->userName = userName;
    curTemp = 25.0;
    tarTemp = DEFAULT_TAR_TEMP;
    initialTemp = 25.0;
    ACState = false;
    curWind = NO_WIND;
    tarWind = DEFAULT_WIND;
    payment = 0.0;
    //新建一个QTimer对象
    timer = new QTimer();
    //设置定时器每隔1分钟发送一个timeout()信号
    timer->setInterval(10000);
    //启动定时器
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    connect(cc, SIGNAL(SignalWindUpdated()), this, SLOT(onWindUpdated()));
    ui->label_customer_name_3->setText(QString(QString::fromLocal8Bit(userName.c_str())));
    ui->label_roomID->setNum(roomId);
    ui->lcdNumber_current_temperature_2->display(curTemp);
    ui->label_ACstate_3->setText("关闭");
}

Client::~Client()
{
    delete ui;
    delete cc;
}

void Client::showCurWind(int wind)
{
    if (wind == 3)
        ui->label_current_speed_2->setText("高风");
    else if (wind == 2)
        ui->label_current_speed_2->setText("中风");
    else if (wind == 1)
        ui->label_current_speed_2->setText("低风");
    else if (wind == 0)
        ui->label_current_speed_2->setText("无风");

}

void Client::showTarWind(int wind)
{
    if (wind == 3)
        ui->label_target_speed_2->setText("高风");
    else if (wind == 2)
        ui->label_target_speed_2->setText("中风");
    else if (wind == 1)
        ui->label_target_speed_2->setText("低风");
    else if (wind == 0)
        ui->label_target_speed_2->setText("无风");
}

void Client::onTimerOut()
{
    // 每分钟当前房间温度变化大小delta
    double ratio = 1.0, delta = 0.0, oldTemp = curTemp;
    if (curWind == 1)
        ratio = RATIO_LOW_WIND;
    else if (curWind == 3)
        ratio = RATIO_HIGH_WIND;
    curWind ? delta = ratio * DELTA_TEMP_AC_ON : delta = ratio * DELTA_TEMP_AC_OFF;

    if(curWind){   // 空调在送风,温度朝着目标温度变化
        if (tarTemp - curTemp > 0.001)
            curTemp += delta;
        else if (curTemp - tarTemp > 0.001 )
            curTemp -= delta;
        // 检查达到目标值,停止送风
        if ((tarTemp-oldTemp)*(tarTemp-curTemp)<=0){
            int ok = cc->changeWind(roomId, NO_WIND, payment);
            if (ok){
                curWind = NO_WIND;
                showCurWind(curWind);
                ui->label_payment_2->setNum(payment);
            }
            else
                QMessageBox::critical(this, "提示信息", "空调绝对坏了无法停风");
        }
    }
    else{   // 空调不送风,温度朝着原始房间温度变化
        if (initialTemp - curTemp > 0.001)
            curTemp += delta;
        else if (curTemp - initialTemp > 0.001 )
            curTemp -= delta;
        // 温度变换已经达到初始温度, 则房间温度不会再变
        if ((initialTemp - oldTemp) * (initialTemp - curTemp) <= 0)
            curTemp = initialTemp;
        // 温差大于1度,则重新开始送风
        if(fabs(curTemp - tarTemp) >= 1.0){
            int ok = cc->changeWind(roomId, tarWind, payment);
            if (ok){
                curWind = tarWind;
                showCurWind(curWind);
                ui->label_payment_2->setNum(payment);
            }
            else
                QMessageBox::critical(this, "提示信息", "稍等或者空调已经坏了");
        }
    }
    // 更新显示当前温度
    ui->lcdNumber_current_temperature_2->display(curTemp);
}

void Client::onWindUpdated()
{
    curWind = cc->getCurWind();
    payment = cc->getPayment();
    showCurWind(curWind);
    ui->label_payment_2->setNum(payment);
}

void Client::on_pushButton_temperature_up_2_clicked()
{
    if(!ACState)
        return;
//     QMessageBox::information(this, "提示信息", "upupupu");
    if (tarTemp + 1 > MAX_TEMP){
        QMessageBox::critical(this,"提示信息", "温度不能再高了");
        return;
    }
    int ok = cc->changeTemp(roomId, curTemp, tarTemp+1, payment);
    if (ok){
        tarTemp++;
        ui->lcdNumber_target_temperature_2->display(tarTemp);
        ui->label_payment_2->setNum(payment);
    }
    else
        QMessageBox::critical(this,"提示信息", "重试或者空调已经坏了");
    //emit SIGNAL(timeout());

}

void Client::on_pushButton_temperature_down_2_clicked()
{
    if(!ACState)
        return;
    if (tarTemp - 1 < MIN_TEMP){
        QMessageBox::critical(this,"提示信息", "温度不能再低了");
        return;
    }
    int ok = cc->changeTemp(roomId, curTemp, tarTemp-1, payment);
    if (ok){
        tarTemp--;
        ui->lcdNumber_target_temperature_2->display(tarTemp);
        ui->label_payment_2->setNum(payment);
    }
    else
        QMessageBox::critical(this,"提示信息", "重试或者空调已经坏了");
    //emit SIGNAL(timeout());
}

void Client::on_pushButton_switch_2_clicked()
{
    cc->switchAC(roomId, ACState);
    if (ACState){  /*开启空调初始化界面参数*/
        ui->label_ACstate_3->setText("开启");
        ui->lcdNumber_target_temperature_2->display(tarTemp);
        if (fabs(curTemp - tarTemp) < 0.001){//无需空调出风
            showCurWind(curWind);
            showTarWind(tarWind);
        }
        else{

            curWind = DEFAULT_WIND;
            int ok = cc->changeTemp(roomId, curTemp, tarTemp, payment);
            if (ok){
                ui->lcdNumber_target_temperature_2->display(tarTemp);
                ui->label_payment_2->setNum(payment);
                showCurWind(curWind);
                showTarWind(curWind);
            }
            else
                QMessageBox::critical(this,"提示信息", "重试或者空调已经坏了");
//        QMessageBox::information(this,"提示信息", "开启");
        }
    }
    else {   /*关闭空调,界面参数消失*/
        curWind = NO_WIND;
        ui->label_ACstate_3->setText("关闭");
        ui->lcdNumber_target_temperature_2->display(0);
        ui->label_payment_2->setNum(0.0);
        ui->label_current_speed_2->setText("");
        ui->label_target_speed_2->setText("");
    }
}

void Client::on_pushButton_speed_up_2_clicked()
{
    if(!ACState)
        return;
    if (tarWind == 3){
        QMessageBox::critical(this,"提示信息", "当前目标风速已最高!");
        return;
    }
    int ok = cc->changeWind(roomId, tarWind+1, payment);
    if (ok == 1){  // 成功设置当前风速
        curWind++;
        tarWind++;
        showCurWind(curWind);
        showTarWind(tarWind);
        ui->label_payment_2->setNum(payment);
    }
    else if (ok == 2){  // 等待调度
        tarWind++;
        showTarWind(tarWind);
        QMessageBox::critical(this,"提示信息", "稍等");
    }
    else
        QMessageBox::critical(this,"提示信息", "空调已经坏了");
}

void Client::on_pushButton_speed_down_2_clicked()
{
    if(!ACState)
        return;
    if (tarWind == 1){
        QMessageBox::critical(this,"提示信息", "当前目标风速已最低!");
        return;
    }
    int ok = cc->changeWind(roomId, tarWind-1, payment);
    if (ok == 1){  // 成功设置目标风速
        curWind--;
        tarWind--;
        showCurWind(curWind);
        showTarWind(tarWind);
        ui->label_payment_2->setNum(payment);
    }
    else if (ok == 2){  // 等待调度
        tarWind--;
        showTarWind(tarWind);
        QMessageBox::critical(this,"提示信息", "稍等");
    }
    else
        QMessageBox::critical(this,"提示信息", "空调已经坏了");
}
