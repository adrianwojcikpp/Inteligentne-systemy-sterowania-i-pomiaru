/**
  ******************************************************************************
  * @file    main.cpp
  * @author  Jakub Walkowski
  * @version 3.0.0
  * @date    19-Mar-2024
  * @brief   Aeropendulu control (APC) command line app example
  *
  ******************************************************************************
  */

#include <iostream>

#include "motor_steval.h"
#include "encoder_as5600.h"

int main(int argc, char** argv)
{
    // Motor control initialization
    MOTOR_Init();

    // Position measurement initialization
    ENCODER_Init();

    // Starting motor
    MOTOR_FaultAck();
    int speed = std::stoi(argv[1]);
    if(abs(speed) <= 3000)
    {
        MOTOR_SetRefSpeed(speed);
        std::cout << "Reference speed [rpm]: " <<  speed << std::endl;
    }
    MOTOR_Start();

    // Reading motor speed
    int payload;
    MOTOR_GetMeasSpeed(&payload, &speed);
    std::cout << "Measured speed [rpm]: (" << payload << ") " << speed << std::endl;
    
    // Reading position
    uint16_t positon_raw = ENCODER_getRawAngle();
    float position = ENCODER_convertRawAngleToDegrees(positon_raw);
    std::cout << "Position [deg]: " << position << std::endl;

    // Motor control deinitialization
    MOTOR_DeInit();

    return 0;
}
