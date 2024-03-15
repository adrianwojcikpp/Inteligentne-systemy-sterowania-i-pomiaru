#include <iostream>

#include "AS5600.h"
#include "uartSteval.h"

int main(int argc, char** argv)
{
    UART steval;
    steval.baud = 38400;
    steval.device = "/dev/ttyACM0";

    Frame f;

    AS5600_Init();

    FaultAck(0, steval, &f);
    int speed = std::stoi(argv[1]);
    if(abs(speed) <= 4000)
    {
        SetMotorRefSpeed(speed, 0, steval, &f);
        printf("Reference speed [rpm]: %d\n", speed);
    }
    StartMotor(0, steval, &f);

    float position = convertRawAngleToDegrees(getRawAngle());
    printf("Position [deg]: %f\n", position);

    GetRegistry(STEVAL_REGISTERS::SPEED_MEAS, STEVAL_REGISTERS_LEN::GET, 0, steval, &f);
    printf("Measured speed [rpm]: (%d) %d\n", f.payload, f.data);

    return 0;
}
