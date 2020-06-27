#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include<QDateTime>
#include<QTimer>

#define CUR_TEMP 25
#define TARGET_TEMP 0
#define TARGET_SPEED 1
class ClientState:public QObject
{
    Q_OBJECT
public:
    ClientState(int RoomId,QDateTime Time = QDateTime::currentDateTime(),int Is_open = 0,
                double Cur_temp = CUR_TEMP,int Cur_speed = 0,double Target_temp = TARGET_TEMP,
                int Target_speed = TARGET_SPEED,double Payment = 0):roomId(RoomId),time(Time),is_open(Is_open),cur_temp(Cur_temp),
        cur_speed(Cur_speed),target_temp(Target_temp),target_speed(Target_speed),payment(Payment),status(0)
    {
        timer1 = new QTimer();
        timer2 = new QTimer();
        timer1->setSingleShot(true);
        timer2->setSingleShot(true);
    } //构造函数，一定要指定roomId,其他均有默认值
    int get_status(){return status;}
    void set_status(int newStatus){status = newStatus;}
    int get_is_open(){return is_open;}
    int get_roomId(){return roomId;}
    void set_is_open(int state){is_open = state;}
    QDateTime get_time(){return time;}
    void set_time(QDateTime time){this->time = time;}
    double get_cur_temp(){return cur_temp;}
    void set_cur_temp(double cur_temp){this->cur_temp = cur_temp;}
    int get_cur_speed(){return cur_speed;}
    void set_cur_speed(int cur_speed){this->cur_speed = cur_speed;}
    double get_target_temp(){return target_temp;}
    void set_target_temp(double target_temp){this->target_temp=target_temp;}
    int get_target_speed(){return target_speed;}
    void set_target_speed(int target_speed){this->target_speed=target_speed;}
    double get_payment(){return payment;}
    void set_payment(double payment){this->payment = payment;}
    void init_shuwdown();
    void init_open();
    QTimer* timer1;
    QTimer* timer2;

signals:
    void sigSendRunningClient(int roomId,int target_speed);
    void sigSendHungryClient(int roomId,int target_speed);
public slots:
    void slotSendHungryClient();
    void slotSendRunningClient();
private:
    int roomId;
    QDateTime time;
    int status;
    int is_open;
    double cur_temp;
    int cur_speed;
    double target_temp;
    int target_speed;
    double payment;
    double waitTime;
    int switchOpenCount;
    int dispatchCount;
    int switchWindCount;
    int switchTempCount;
};

#endif // CLIENTSTATE_H
