#include "client.h"
#include "ui_client.h"

#pragma execution_character_set("utf-8")

Client::Client(QString roomId, QString userName, double initialTemp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    sm = new SlaveMachine(roomId, userName, initialTemp);
    cc = new ClientController(sm);
    // 控制器收到中央空调送风请求
    connect(cc, SIGNAL(SignalInfoUpdated()), this, SLOT(onInfoUpdated()));
    // 控制器定时控制更新客户端界面状态,主要是当前温度和费用
    connect(cc, SIGNAL(SignalTimeOutUpdated()), this, SLOT(onInfoUpdated()));
    // 展示控制器返回的错误,例如温度设置错误、通信丢失
    connect(cc, SIGNAL(SignalErrorOccoured(errorType)), this, SLOT(onErrorOccoured(errorType)));
    connect(cc, SIGNAL(SignalCheckIn()), this, SLOT(onCheckIn()));
    ui->label_customer_name_3->setText(userName);
    ui->label_roomID->setText(roomId);
    ui->lcdNumber_current_temperature_2->display(sm->getCurTemp());
    showCurWind(noWind);
    showTarWind(noWind);
    ui->label_ACstate_3->setText("关闭");
    ui->label_payment_2->setNum(sm->getPayment());
    ui->radioButton_set_mode_cold->setEnabled(false);
    ui->radioButton_set_mode_heat->setEnabled(false);
    qDebug()<<"client构造函数"<<endl;
}

Client::~Client()
{
    qDebug()<<"client析构函数"<<endl;
    delete ui;
    delete sm;
    delete cc;
}

void Client::onInfoUpdated()
{
    ui->lcdNumber_current_temperature_2->display(sm->getCurTemp());
    ui->lcdNumber_target_temperature_2->display(sm->getTarTemp());
    showCurWind(sm->getCurWind());
    showTarWind(sm->getTarWind());
    ui->label_payment_2->setNum(sm->getPayment());
}

void Client::onErrorOccoured(errorType error)
{
    if (error == tempNotAllowed)
        QMessageBox::critical(this, "错误信息", "温度设置超出当前模式范围");
    else if (error == tcpFailed)
        QMessageBox::critical(this, "提示信息", "与中央空调通信失败,请联系管理员");
    else if (error == roomInvalid) {
        if (sm->getState() == true) {  // 如果房间开启, 立即关闭空调
            on_pushButton_switch_2_clicked();
        }
        sm->setIsValid(false);
        ui->pushButton_switch_2->setDisabled(true);
        QMessageBox::critical(this, "提示信息", "对不起, 你没有对此房间操作权限");

    }
}

void Client::onCheckIn()
{
    sm->setIsValid(true);
    ui->pushButton_switch_2->setEnabled(true);
}

void Client::showCurWind(windSpeed wind)
{
    if (wind == highWind)
        ui->label_current_speed_2->setText("高风");
    else if (wind == midWind)
        ui->label_current_speed_2->setText("中风");
    else if (wind == lowWind)
        ui->label_current_speed_2->setText("低风");
    else if (wind == noWind)
        ui->label_current_speed_2->setText("无风");
}

void Client::showTarWind(windSpeed wind)
{
    if (wind == highWind)
        ui->label_target_speed_2->setText("高风");
    else if (wind == midWind)
        ui->label_target_speed_2->setText("中风");
    else if (wind == lowWind)
        ui->label_target_speed_2->setText("低风");
    else if (wind == noWind)
        ui->label_target_speed_2->setText("无风");
}

void Client::showState()
{
    if (sm->getState() == true)
        ui->label_ACstate_3->setText("开启");
    else
        ui->label_ACstate_3->setText("关闭");
}

void Client::showMode()
{
    if (sm->getMode() == heat)
        ui->radioButton_set_mode_heat->setChecked(true);
    else if (sm->getMode() == cold)
        ui->radioButton_set_mode_cold->setChecked(true);
}

void Client::on_pushButton_temperature_up_2_clicked()
{
    if(!sm->getState())  // 空调关闭状态下,无须响应
        return;
    cc->changeTemp(sm->getTarTemp() + 1);
    ui->lcdNumber_target_temperature_2->display(sm->getTarTemp());
}

void Client::on_pushButton_temperature_down_2_clicked()
{
    if(!sm->getState())  // 空调关闭状态下,无须响应
        return;
    cc->changeTemp(sm->getTarTemp() - 1);
    ui->lcdNumber_target_temperature_2->display(sm->getTarTemp());
}

void Client::on_pushButton_switch_2_clicked()
{
    double curTemp = sm->getCurTemp();
    double tarTemp = sm->getTarTemp();
    qDebug()<<"空调开启状态:"<<sm->getState()<<endl;
    if (!sm->getState()){  // 开启空调初始化界面参数
        ui->label_ACstate_3->setText("开启");
        ui->lcdNumber_target_temperature_2->display(tarTemp);
        ui->radioButton_set_mode_cold->setEnabled(true);
        ui->radioButton_set_mode_heat->setEnabled(true);
        showMode();
        if (fabs(curTemp - tarTemp) > 0.001){// 空调需要送风
            sm->setTarWind(midWind);
        }
    }
    else {  // 关闭空调,界面参数消失
        ui->radioButton_set_mode_cold->setEnabled(false);
        ui->radioButton_set_mode_heat->setEnabled(false);
        sm->setTarTemp(sm->getDefaultTemp());
        sm->setTarWind(noWind);
        sm->setCurWind(noWind);
        ui->label_ACstate_3->setText("关闭");
        ui->lcdNumber_target_temperature_2->display(tarTemp);
        ui->label_current_speed_2->setText("");
        ui->label_target_speed_2->setText("");
    }
    qDebug()<<sm->getTarWind()<<"开关完毕"<<endl;
    showCurWind(sm->getCurWind());
    showTarWind(sm->getTarWind());

    cc->switchAC();

}

void Client::on_pushButton_speed_up_2_clicked()
{
    if(!sm->getState())  // 空调关闭状态下,无须响应
        return;
    if (sm->getTarWind() == highWind){
        QMessageBox::critical(this,"提示信息", "当前目标风速已最高!");
        return;
    }
    sm->setTarWind((enum windSpeed)(sm->getTarWind() + 1));
    cc->changeWind();
    showTarWind(sm->getTarWind());
}

void Client::on_pushButton_speed_down_2_clicked()
{
    if(!sm->getState())  // 空调关闭状态下,无须响应
        return ;
    if (sm->getTarWind() == lowWind || sm->getTarWind() == noWind){
        QMessageBox::critical(this,"提示信息", "当前目标风速已最低!");
        return;
    }
    sm->setTarWind((enum windSpeed)(sm->getTarWind() - 1));
    cc->changeWind();
    showTarWind(sm->getTarWind());
}

void Client::on_radioButton_set_mode_cold_clicked()
{
    if (sm->getMode() == cold)  // 无需响应
        return ;
    sm->setMode(cold);
    sm->setTarTemp(sm->getDefaultTemp());
    cc->changeMode();
    ui->lcdNumber_target_temperature_2->display(sm->getTarTemp());
}

void Client::on_radioButton_set_mode_heat_clicked()
{
    if (sm->getMode() == heat)  // 无需响应
        return ;
    sm->setMode(heat);
    sm->setTarTemp(sm->getDefaultTemp());
    cc->changeMode();
    ui->lcdNumber_target_temperature_2->display(sm->getTarTemp());

}
