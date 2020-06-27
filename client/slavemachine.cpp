#include "slavemachine.h"

SlaveMachine::SlaveMachine(QString roomId, QString userName, double initialTemp)
{
    this->roomId = roomId;
    this->userName = userName;
    this->initialTemp = initialTemp;
    curTemp = initialTemp;
    ACState = false;

    minTempOnModeCold = 18.0;
    maxTempOnModeCold = 25.0;
    minTempOnModeHeat = 25.0;
    maxTempOnModeHeat = 30.0;
    defaultTemp = 25.0;

    curWind = noWind;
    tarWind = noWind;
}
