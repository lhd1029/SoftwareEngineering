#include "clientcontroller.h"

ClientController::ClientController(QObject *parent) : QObject(parent)
{
    ACstate = false;


}

void ClientController::windUpdated()
{
    emit SIGNAL(SignalWindUpdated());
}

int ClientController::changeTemp(int roomId, double curTemp, double tarTemp, double &payment)
{
    payment =250.0;
    return 1;
}

int ClientController::changeWind(int roomId, int wind, double &payment)
{
    if (wind == 0)
        payment = 0.0;
    else
        payment = 8888.01;
    return 1;
}

void ClientController::switchAC(int roomId, bool &state)
{//测试
    this->ACstate = !(this->ACstate);
    state = this->ACstate;
}
