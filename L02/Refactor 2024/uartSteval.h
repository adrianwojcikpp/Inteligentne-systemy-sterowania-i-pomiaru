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
#include "tools.h"

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
    Frame() {}
    /**
     * @brief Construct a new Frame object for sending
     * 
     * @param motorid Motor id
     * @param framecode Frame code from FRAME_CODES enum
     * @param registerId Motor control register id
     * @param payload_len Motor control register payload length
     * @param data Data to send, if no data put NO_DATA
     */
    Frame(int motorid, FRAME_CODES framecode, int registerId, int payload_len, long long data)
    {
        motorId = motorid;
        frameCode = framecode;
        reg = registerId;
        payload = payload_len;
        this->data = data;
        if ((int)data == NO_DATA)
            if (reg == -1)
                CRC = ((motorId << 5) + (int)frameCode) + payload;
            else
                CRC = ((motorId << 5) + (int)frameCode) + (int)reg + payload;
        else
        {
            if (reg == -1)
                CRC = ((motorId << 5) + (int)frameCode) + payload;
            else
                CRC = ((motorId << 5) + (int)frameCode) + (int)reg + payload;
            for (int i = 0; i < payload; i++)
            {
                CRC += int(data >> i * 8) & 0xFF;
            }
        }
        CRC = ((CRC >> 8) & 0xff) + (CRC & 0xff);
    }
    /**
     * @brief Construct a new received Frame object
     * 
     * @param array Array of received bytes
     * @param lenght Lenght of array
     */
    Frame(int *array, int lenght)
    {
        if (lenght < 3)
        {
            long log = start_log(LOG_PATH);
            printf("[ERROR_UART_DATA] %s\n", "Error in Frame constructor.");
            stop_log(log);
            throw;
        }
        data = 0;
        payload = array[1];
        CRC = array[lenght - 1];
        //printf("PL:%d CRC:%d\n",payload,CRC);
        if (payload > 0 && array[0] != 0xff)
        {
            int sig = 0;
            int nonzero = 0;
            bool set = false;
            for (int i = 2 + payload - 1; i >= 2; i--)
            {
                data = ((int)data << (8 * (payload - 1 - i))) + array[i];
                if (array[i] != 0 && set == false)
                {
                    sig = array[i] >> 7;
                    set = true;
                    nonzero = i - 1;
                }
            }
            // int bytes = 0;
            // for (int i = 0; i < payload - nonzero; i++)
            // {
            //     bytes = (bytes << (i * 8)) + 0xff;
            // }
            if (sig)
                data = -((~data) & (0xffff)) - 1;
            frameCode = FRAME_CODES::RECEIVE;
            motorId = -1;
            //printf("D:%d\n",(int)data);
        }
        else if (payload == 1 && array[0] != 0xf0)
        {
            data = array[2];
            frameCode = FRAME_CODES::ERROR;
            motorId = -1;
        }
        else if (array[0] != 0xf0)
        {
            long log = start_log(LOG_PATH);
            printf("[ERROR_UART_DATA] %s FRAME:", "Error in Frame constructor.");
            for (int i = 0; i < lenght; i++)
            {
                printf("%02x ", array[i]);
            }
            printf("\n");
            stop_log(log);
            throw;
        }
    }

    int motorId;           /*< Motor id */
    FRAME_CODES frameCode; /*< Frame code from FRAME_CODES enum */
    int reg;               /*< Motor control register id from STEVAL_REGISTERS enum */
    int payload;           /*< Motor control register payload length */
    long long data;        /*< Data in frame */
    int CRC;               /*< Cyclic redundancy check */
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
 * @return UART_STATUS Sending resoult
 */
UART_STATUS send(Frame cmd, UART uart, Frame *f);
/**
 * @brief Execute start motor command
 * 
 * @param motorId Motor id
 * @param uart Uart object
 * @return UART_STATUS Starting motor resoult
 */
UART_STATUS StartMotor(int motorId, UART uart, Frame *f);
UART_STATUS StopRamp(int motorId, UART uart, Frame *f);
/**
 * @brief Execute stop motor command
 * 
 * @param motorId Motor id
 * @param uart Uart object
 * @return UART_STATUS  Stoping motor resoult
 */
UART_STATUS StopMotor(int motorId, UART uart, Frame *f);
/**
 * 
 * @brief Set the motor ramp final speed registry
 * 
 * @param ref Value to set
 * @param motorId Motor id
 * @param uart Uart object
 * @return UART_STATUS Setting resoult 
 */
UART_STATUS SetMotorRefSpeed(int ref, int motorId, UART uart, Frame *f);
/**
 * @brief Set the registry value
 * 
 * @param reg Motor control register id
 * @param regL Montrol register payload length
 * @param motorId Motor id
 * @param uart Uart object
 * @param data Value to set
 * @return UART_STATUS Setting resoult
 */
UART_STATUS SetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int motorId, UART uart, int data, Frame *f);
/**
 * @brief Get the registry value
 * 
 * @param reg Motor control register id
 * @param regL Montrol register payload length
 * @param motorId Motor id
 * @param uart Uart object
 * @return UART_STATUS Getting resoult
 */
UART_STATUS GetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int motorId, UART uart, Frame *f);
UART_STATUS FaultAck(int motorId, UART uart, Frame *f);
UART_STATUS ExeRampSpeed(int motorId, UART uart, int duration, int finalSpeed, Frame *f);
#endif /* INC_UARTSTEVAL_H_ */