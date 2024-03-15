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

UART_STATUS receive(Frame *cmd, int connection, Frame c)
{
    int j = 0;
    int *array = new int[10];
    delay(5);
    //printf("Recive: ");
    while (serialDataAvail(connection))
    {
        array[j] = serialGetchar(connection);
        //printf("%02x ", array[j]);
        j++;
    }
    //printf("\n");

    if (j < 3 || j > 10)
    {
        long log = start_log(LOG_PATH);
        printf("[ERROR_UART_DATA] Wrong frame lenght(%d).\n", j);
        stop_log(log);
        return UART_FRAME_SIZE_ERROR;
    }
    if (array[0] == 0xf0)
    {
        *cmd = Frame(array, j);
        //printf("Odebrana wartość: %d \n", cmd->data);
    }
    else if (array[0] == 0xff)
    {
        long log = start_log(LOG_PATH);
        printf("[ERROR_UART_DATA] %s FRAME:", GetErrorMessage((STEVAL_ERROR)array[2]));

        printf("%02x ", (c.motorId << 5) + (int)c.frameCode);
        printf("%02x ", (int)c.payload);
        printf("%02x ", (int)c.reg);
        if (c.data != NO_DATA)
        {
            for (int i = 0; i < (int)c.payload - 1; i++)
            {
                printf("%02X ", (c.data >> i * 8) & 0xFF);
            }
        }
        printf("%02x ", c.CRC);
        printf("\n");
        stop_log(log);
        return UART_STEVAL_ERROR;
    }
    else
    {
        long log = start_log(LOG_PATH);
        printf("[ERROR_UART_DATA] unknown error(%d). FRAME: ", j);
        for (int i = 0; i < j; i++)
        {
            printf("%02x ", array[i]);
        }
        printf("\n");
        stop_log(log);
        return UART_FRAME_ERROR;
    }

    return UART_OK;
}
UART_STATUS sendData(int con, long long data, int l)
{
    for (int i = 0; i < l; i++)
    {
        serialPutchar(con, int((data >> i * 8) & 0xFF));
        //printf("%02X ", int((data >> i * 8) & 0xFF));
    }
    //printf("\n");
    return UART_OK;
}
UART_STATUS send(Frame cmd, UART uart, Frame *f)
{
    int connection = serialOpen(uart.device, uart.baud);
    if (connection == -1)
    {
        long fd12 = start_log(LOG_PATH);
        printf("[ERROR_UART] %s", "Uart connection error.\n");
        stop_log(fd12);
        return UART_CONNECTION_ERROR;
    }
    serialPutchar(connection, (cmd.motorId << 5) + (int)cmd.frameCode);
    serialPutchar(connection, (int)cmd.payload);
    if (cmd.reg != (int)STEVAL_REGISTERS::NO_REG)
        serialPutchar(connection, (int)cmd.reg);

    //printf("Send: ");
    //std::cout << std::hex << (cmd.motorId << 5) + (int)cmd.frameCode << " ";
    //std::cout << std::hex << (int)cmd.payload << " ";
    //if (cmd.reg != (int)STEVAL_REGISTERS::NO_REG)
        //std::cout << std::hex << (int)cmd.reg << " ";

    if ((int)cmd.data != NO_DATA)
    {
        int l=cmd.payload;
        if(cmd.reg!=(int)STEVAL_REGISTERS::NO_REG)
            l-=1;
        sendData(connection, cmd.data, l);
    }
    serialPutchar(connection, cmd.CRC);

    //std::cout << std::hex << cmd.CRC << " ";
    //printf("\n");

    Frame recCommand = Frame();
    UART_STATUS status = receive(&recCommand, connection, cmd);
    *f = recCommand;
    serialClose(connection);
    return status;
}
UART_STATUS StartMotor(int motorId, UART uart, Frame *f)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::START_MOTOR, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, f);
}
UART_STATUS StopMotor(int motorId, UART uart, Frame *f)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::STOP_MOTOR, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, f);
}
UART_STATUS FaultAck(int motorId, UART uart, Frame *f)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::FAULT_ACT, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, f);
}
UART_STATUS SetMotorRefSpeed(int ref, int motorId, UART uart, Frame *f)
{
    Frame cmd = Frame(1, FRAME_CODES::SET, (int)STEVAL_REGISTERS::RAMP_FIN_SPEED, (int)STEVAL_REGISTERS_LEN::RAMP_FIN_SPEED, ref);
    return send(cmd, uart, f);
}
UART_STATUS SetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int motorId, UART uart, int data, Frame *f)
{
    Frame cmd = Frame(1, FRAME_CODES::GET, (int8_t)reg, (int)regL, data);
    return send(cmd, uart, f);
}
UART_STATUS GetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int motorId, UART uart, Frame *f)
{
    Frame cmd = Frame(1, FRAME_CODES::GET, (int)reg, (int)regL, NO_DATA);
    return send(cmd, uart, f);
}
UART_STATUS StopRamp(int motorId, UART uart,Frame *f)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::STOP_RAMP, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, f);
}
UART_STATUS ExeRampSpeed(int motorId, UART uart, int duration, int finalSpeed, Frame *f)
{
    long long data = 0;
    for(int i=0;i<4;i++)
    {
         data=(data<<8) + (int)(((finalSpeed >> 8*i) & 0xff));
    }
    data=(data<<8) + int(duration &0xff);
    data=(data<<8) + int((duration>>8) &0xff);
    long long n = 0;
    for (int i = 0; i < 6; i++)
    {
        n = (n<<8) + int((data >> i * 8) & 0xFF);
    }
    std::string s=std::to_string(data);
    //std::cout<<"longMade"+s<<std::endl;
    Frame cmd = Frame(1, FRAME_CODES::EXE_RAMP, (int)STEVAL_REGISTERS::NO_REG, (int)STEVAL_REGISTERS_LEN::RAMP_EXE, n);
    return send(cmd, uart, f);
}