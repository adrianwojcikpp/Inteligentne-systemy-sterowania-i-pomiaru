/** 
 * @file uartSteval.h
 *
 *  Created on: Nov 27, 2020
 *      Author: walko
 */

#ifndef INC_UARTSTEVAL_H_
#define INC_UARTSTEVAL_H_

#include <climits>
#include "registers.h"
#include <cstdio>

#define NO_DATA INT_MAX

/**
 * @brief Uart connection object
 * 
 */
struct UART
{
    int baud;
    const char *device;
};
/**
 * @brief Uart frame obejct
 * 
 */
struct Frame
{
    /**
     * @brief Default construct a new Frame object
     * 
     */
    Frame(){}
    /**
     * @brief Construct a new Frame object
     * 
     * @param motorid Motor id
     * @param framecode Frame code from FRAME_CODES enum
     * @param registerId Motor control register id
     * @param payload_len Motor control register payload length
     * @param data Data to send, if no data put NO_DATA
     */
    Frame(int motorid, FRAME_CODES framecode, STEVAL_REGISTERS registerId, int payload_len, int data)
    {
        motorId = motorid;
        frameCode = framecode;
        reg = registerId;
        payload = payload_len;
        this->data = data;
        if (data == NO_DATA)
            CRC = ((motorId << 5) + (int)frameCode) + (int)reg + payload;
        else
        {
            CRC = ((motorId << 5) + (int)frameCode) + (int)reg + payload;
            for (int i = 0; i < payload; i++)
            {
                CRC += (data >> i * 8) & 0xFF;

            }
        }
        CRC=((CRC>>8) & 0xff)+(CRC & 0xff);
		
    }
    Frame(int* array,int lenght)
    {
        motorId = array[0]>>5;
        frameCode = (FRAME_CODES)(array[0]&0x1F);
        payload = array[1];
        CRC = array[lenght-1];

        if(lenght>3)
        {
            for(int i =2+payload;i>=2;i--)
            {
                data = (data<<(8*(payload-1-i)))+array[i];
            }
        }
        
    }
    int motorId;                    /*< Motor id */
    FRAME_CODES frameCode;          /*< Frame code from FRAME_CODES enum */
    STEVAL_REGISTERS reg;           /*< Motor control register id from STEVAL_REGISTERS enum */
    int payload;                    /*< Motor control register payload length */
    int data;                       /*< Data in frame */
    int CRC;                        /*< Cyclic redundancy check */
    /**
     * @brief Get the Commad object as int 
     * 
     * @return int Command as single int
     */
    int getCommad()
    {
        //TODO: add data
        return ((((motorId << 5) + (int)frameCode << 8) + (int)reg << 8) + payload << 8) + CRC;
    }
    /**
     * @brief Bitwise inversion of a number
     * 
     * @param b int number to reverse
     * @param l Bitwise lenght of number
     * @return int inverst number
     */
    int reverse(int b, int l)
    {
        int newb = 0;
        for (int i = 0; i < l; i++)
        {
            if (i == l - 1)
                newb = (newb + ((b >> i * 8) & 0xFF));
            else
                newb = (newb + ((b >> i * 8) & 0xFF)) << 8;
        }
        return newb;
    }
};

extern Frame f;

/**
 * @brief Receive uart frame
 * 
 * @param cmd Received frame
 * @param connection Uart connection id
 * @return UART_STATUS Receiving status
 */
UART_STATUS receive(Frame *cmd, int connection);
/**
 * @brief Send data in frame
 * 
 * @param con Uart conneciton id
 * @param data Data to send
 * @param l Control register payload length
 * @param cmd_show Optional param, if true show sending fame in console
 * @return UART_STATUS Sending resoult
 */
UART_STATUS send(Frame cmd, UART uart, bool cmd_show=false);
/**
 * @brief Execute start motor command
 * 
 * @return UART_STATUS Starting motor resoult
 */
UART_STATUS StartMotor(void);
/**
 * @brief Execute stop motor command
 * 
 * @param motorId Motor id
 * @param uart Uart object
 * @return UART_STATUS  Stoping motor resoult
 */
UART_STATUS StopMotor(void);
/**
 * @brief Set the motor ramp final speed registry
 * 
 * @param ref Value to set
 * @return UART_STATUS Setting resoult 
 */
UART_STATUS SetMotorRefSpeed(int ref);
/**
 * @brief Set the registry value
 * 
 * @param reg Motor control register id
 * @param regL Montrol register payload length
 * @param data Value to set
 * @return UART_STATUS Setting resoult
 */
UART_STATUS SetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int data);
/**
 * @brief Get the registry value
 * 
 * @param reg Motor control register id
 * @param regL Montrol register payload length
 * @return UART_STATUS Getting resoult
 */
UART_STATUS GetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL);

UART_STATUS FaultAck(void);

#endif /* INC_UARTSTEVAL_H_ */