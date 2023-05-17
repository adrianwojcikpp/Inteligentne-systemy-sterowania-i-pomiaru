/**
 * @file uartSteval.cpp
 *
 *  Created on: Nov 27, 2020
 *      Author: Jakub Walkowski
 */
#include <ctype.h>
#include <stdio.h>
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <wiringSerial.h>
#include "uartSteval.h"

#define UART_BAUD  38400
#define UART_DEVICE "/dev/ttyACM0"

Frame f;
UART uart = { UART_BAUD, UART_DEVICE };

UART_STATUS receive(Frame *cmd, int connection)
{
    int j=0;
    int* array = new int[10];

    while (serialDataAvail(connection))
    {
        array[j] = serialGetchar(connection);

        j++;
    }

    if(array[0]!=0xff)
    {
        *cmd = Frame(array,j);
    }        

    return UART_OK;
}
UART_STATUS sendData(int con, int data, int l, bool cmd_show=true)
{
    for(int i = 0;i<l;i++){
      serialPutchar(con,(data >> i*8) & 0xFF);
      if(cmd_show)
        printf("%02X ", (data >> i*8) & 0xFF); 
    }
    if(cmd_show)
        printf("\n");

    return UART_OK;
}
UART_STATUS send(Frame cmd, UART uart, bool cmd_show)
{
    int connection = serialOpen("/dev/ttyACM0",uart.baud);
    if(connection==-1)
    {
        return UART_CONNECTION_ERROR;
    }

    serialPutchar(connection,(cmd.motorId<<5)+(int)cmd.frameCode);
    serialPutchar(connection,(int)cmd.payload);
    serialPutchar(connection,(int)cmd.reg);

    if (cmd_show)
    {
        std::cout << "Send: " << std::endl;
        std::cout << std::hex << (cmd.motorId<<5)+(int)cmd.frameCode<<" ";
        std::cout <<  (int)cmd.payload<<" ";
        std::cout <<  (int)cmd.reg <<" ";
    }
    
    if(cmd.data!=NO_DATA)
    {
        UART_STATUS resD = sendData(connection,cmd.data,(int)cmd.payload-1);
        if(resD != UART_OK)
            return resD;
    }

    serialPutchar(connection,cmd.CRC);
    
    if (cmd_show)
    {
        std::cout << cmd.CRC<< " " << std::dec;
    }

    Frame recCommand= Frame();
    //delay(3);
    receive(&recCommand,connection);
    f = recCommand;
    serialClose(connection);
    return UART_OK;
}
UART_STATUS StartMotor(void)
{
    Frame  cmd = Frame(1,FRAME_CODES::EXE,STEVAL_REGISTERS::START_MOTOR,(int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart);
}
UART_STATUS StopMotor(void)
{
    Frame  cmd = Frame(1,FRAME_CODES::EXE,STEVAL_REGISTERS::STOP_MOTOR,(int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart);
}
UART_STATUS SetMotorRefSpeed(int ref)
{
    Frame  cmd = Frame(1,FRAME_CODES::SET,STEVAL_REGISTERS::RAMP_FIN_SPEED,(int)STEVAL_REGISTERS_LEN::RAMP_FIN_SPEED, ref);
    return send(cmd,uart);
}
UART_STATUS FaultAck(void)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE,STEVAL_REGISTERS::FAULT_ACT, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart);
}
UART_STATUS SetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int data)
{
    Frame cmd = Frame(1,FRAME_CODES::GET,reg,(int)regL,data);
    return send(cmd,uart);
}
UART_STATUS GetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL)
{
    Frame cmd = Frame(1,FRAME_CODES::GET,reg,(int)regL,NO_DATA);
    return send(cmd,uart);
}
