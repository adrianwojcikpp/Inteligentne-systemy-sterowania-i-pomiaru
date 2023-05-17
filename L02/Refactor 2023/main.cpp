#include <iostream>

#include "AS5600.h"
#include "uartSteval.h"

int main()
{
    AS5600_Init();

    FaultAck();
    SetMotorRefSpeed(1000);
    StartMotor();

    while (1)
    {
        float d = convertRawAngleToDegrees(getRawAngle());
        printf("Raw angle: %f \n",d);
    }
    
    return 0;
}
