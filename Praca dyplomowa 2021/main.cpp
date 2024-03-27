#include <ctype.h>
#include <stdio.h>
#include <wiringPi.h>
#include <iostream>
#include "uartSteval.h"
#include <unistd.h>


int main(int argc, char *argv[])
{
    UART uart;
    uart.baud = 9600;
    //uart.device ="/dev/ttyACM0";
    while(true){
        int a;
        int s;
        std::cin>>a;
        if(a==0)
            StopMotor(1,uart);
        else if(a==1)
            StartMotor(1,uart);
        else if(a==2)
        {
            std::cout << "Podaj ref predkosc:";
            std::cin>>s;
            SetMotorRefSpeed(s,1,uart);
        }   
        else if(a==3)
        {
            std::cout << "Predkosc:";
            while(1)
            {
                GetRegistry(STEVAL_REGISTERS::SPEED_MEAS,STEVAL_REGISTERS_LEN::GET,1,uart);    
            }
        } 
        else if(a==4)
        {
            std::cout << "Predkosc:";
            GetRegistry(STEVAL_REGISTERS::SPEED_REF,STEVAL_REGISTERS_LEN::GET,1,uart);
        }      
        else
            StopMotor(1,uart);
    }
}