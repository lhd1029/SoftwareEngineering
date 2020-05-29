#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>

class ClientController : public QObject
{
    Q_OBJECT

public:
    explicit ClientController(QObject *parent = nullptr);
    int changeTemp(int roomId, double curTemp, double tarTemp, double &payment);
    int changeWind(int roomId, int wind, double &payment);
    void switchAC(int roomId, bool &state);
    int getCurWind(){return curWind;}
    double getPayment(){return payment;}
    void windUpdated();

signals:
    void SignalWindUpdated();

private:
    bool ACstate;//测试用
    int curWind;
    double payment;

};

#endif // CLIENTCONTROLLER_H
