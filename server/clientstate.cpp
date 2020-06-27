#include "clientstate.h"

void ClientState::init_shuwdown()
{
    is_open = 0;
    cur_speed = 0;
    target_temp = 0;
    target_speed = 0;
    time = QDateTime::currentDateTime();
}
void ClientState::init_open()
{
    is_open = 1;
    cur_speed = 0;
    target_temp = 25;
    target_speed = 1;
    time = QDateTime::currentDateTime();

}
void ClientState::slotSendRunningClient()
{
    emit sigSendRunningClient(roomId,target_speed);
}
void ClientState::slotSendHungryClient()
{
    emit sigSendHungryClient(roomId,target_speed);
}

