#include <ctype.h>
#include <stdio.h>
#include <wiringPi.h>
#include <iostream>
#include "uartSteval.h"
#include <unistd.h>


int main(int argc, char *argv[])
{
    UART uart;
    uart.baud = 38400;

    int speed;
	Frame f;

    StartMotor(1,uart,&f);

    while(1){
        
        std::cin>>speed;
        SetMotorRefSpeed(speed,1,uart,&f);
      
    }
}

// g++ motor.cpp uartSteval.cpp uartSteval.h registers.h -lwiringPi