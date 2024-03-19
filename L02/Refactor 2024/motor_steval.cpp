/**
  ******************************************************************************
  * @file    motor_steval.cpp
  * @author  Jakub Walkowski
  * @author  AW		(adrian.wojcik@put.poznan.pl)
  * @version 3.0.0
  * @date    19-Mar-2024
  * @brief   Aeropendulum angular drive: STEVAL serial communication
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <ctype.h>
#include <stdio.h>
#include <iostream>

#include <unistd.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "motor_steval.h"

/* Define --------------------------------------------------------------------*/
#define UART_BAUD  38400
#define UART_DEVICE "/dev/ttyACM0"

/* Private variables ---------------------------------------------------------*/
Frame f;
UART uart = { UART_BAUD, UART_DEVICE };

/* Private function ----------------------------------------------------------*/

/**
 * @brief Get the Error Message for STEVAL_ERROR code
 * 
 * @param[in] errorCode : STEVAL_ERROR code
 * @return Error message
 */
char const* GetErrorMessage(STEVAL_ERROR errorCode)
{
    switch(errorCode)
    {
        case BAD_FRAME_ID:
            return "BAD Frame ID. The Frame ID has not been recognized by the firmware.";
        case WRITE_ON_RO:
            return "Write on read-only. The master wants to write on a read-only register.";
        case READ_NOT_ALLOWED:
            return "Read not allowed. The value cannot be read.";
        case BAD_TARGET:
            return "Bad target drive. The target motor is not supported by the firmware.";
        case OUT_OF_RANGE:
            return "Out of range. The value used in the frame is outside the range expected by the firmware.";
        case BAD_CMD_ID:
            return "Bad command ID. The command ID has not been recognized";
        case OVERRUN_ERROR:
            return "Overrun error. The frame has not been received correctly because the transmission speed is too fast.";
        case TIMEOUT:
            return "Timeout error. The frame has not been received correctly and a timeout occurs. This kind of error usually occurs when the frame is not correct or is not correctly recognized by the firmware.";
        case BAD_CRC:
            return "Bad CRC. The computed CRC is not equal to the received CRC byte.";
        case BAD_TARGET_2:
            return "Bad target drive. The target motor is not supported by the firmware.";
        default:
            return "Unknown error.";
    }
} 

/**
 * @brief TODO
 * 
 * @param[inout] cmd        : TODO
 * @param[in]    connection : TODO
 * @param[in]    c          : TODO
 * @return TODO
 */
UART_STATUS receive(Frame *cmd, int connection, Frame c)
{
    int j = 0;
    int *array = new int[10];

    while (serialDataAvail(connection)) // TODO: add timeout
    {
        array[j] = serialGetchar(connection);
        j++;
    }

    if (j < 3 || j > 10)
    {
        printf("[ERROR_UART_DATA] Wrong frame lenght(%d).\n", j);
        return UART_FRAME_SIZE_ERROR;
    }
    if (array[0] == 0xf0)
    {
        *cmd = Frame(array, j);
    }
    else if (array[0] == 0xff)
    {
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
        return UART_STEVAL_ERROR;
    }
    else
    {
        printf("[ERROR_UART_DATA] unknown error(%d). FRAME: ", j);
        for (int i = 0; i < j; i++)
        {
            printf("%02x ", array[i]);
        }
        printf("\n");
        return UART_FRAME_ERROR;
    }

    return UART_OK;
}

/**
 * @brief TODO
 * 
 * @param[in] con  : TODO
 * @param[in] data : TODO
 * @param[in] l    : TODO
 * @return TODO
 */
UART_STATUS sendData(int con, long long data, int l)
{
    for (int i = 0; i < l; i++)
    {
        serialPutchar(con, int((data >> i * 8) & 0xFF));
    }
    return UART_OK;
}

/**
 * @brief TODO
 * 
 * @param[in]    cmd  : TODO
 * @param[in]    uart : TODO
 * @param[inout] f    : TODO
 * @return TODO
 */
UART_STATUS send(Frame cmd, UART uart, Frame *f)
{
	/********************************************************/
    //uart.connection = serialOpen(uart.device, uart.baud);
    //if (uart.connection == -1)
    //{
    //    printf("[ERROR_UART] %s", "Uart connection error.\n");
    //    return UART_CONNECTION_ERROR;
    //}
	/********************************************************/
	
    serialPutchar(uart.connection, (cmd.motorId << 5) + (int)cmd.frameCode);
    serialPutchar(uart.connection, (int)cmd.payload);
	
    if (cmd.reg != (int)STEVAL_REGISTERS::NO_REG)
        serialPutchar(uart.connection, (int)cmd.reg);

    if ((int)cmd.data != NO_DATA)
    {
        int l = cmd.payload;
        if(cmd.reg!=(int)STEVAL_REGISTERS::NO_REG)
            l -= 1;
        sendData(uart.connection, cmd.data, l);
    }
    serialPutchar(uart.connection, cmd.CRC);

    delay(5); 

    Frame recCommand = Frame();
    UART_STATUS status = receive(&recCommand, uart.connection, cmd);
    *f = recCommand;
	
	/********************************************************/
    //serialClose(uart.connection);
	/********************************************************/
	
    return status;
}

/* Public function -----------------------------------------------------------*/

/**
 * @brief Set the registry value
 * 
 * @param[in] reg  : Motor control register id
 * @param[in] regL : Montrol register payload length
 * @param[in] data : Value to set
 * @return UART_STATUS Setting result
 */
UART_STATUS MOTOR_SetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int data)
{
    Frame cmd = Frame(1, FRAME_CODES::GET, (int8_t)reg, (int)regL, data);
    return send(cmd, uart, &f);
}

/**
 * @brief Get the registry value
 * 
 * @param[in] reg  : Motor control register id
 * @param[in] regL : Montrol register payload length
 * @return UART_STATUS Getting result
 */
UART_STATUS MOTOR_GetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, Frame *rec)
{
    Frame cmd = Frame(1, FRAME_CODES::GET, (int)reg, (int)regL, NO_DATA);
    return send(cmd, uart, rec);
}

/**
 * @brief TODO
 * 
 * @return TODO
 */
UART_STATUS MOTOR_Init(void)
{
    uart.connection = serialOpen(uart.device, uart.baud);
    if (uart.connection == -1)
    {
        printf("[ERROR_UART] %s", "Uart connection error.\n");
        return UART_CONNECTION_ERROR;
    }
    return UART_OK;
}

/**
 * @brief TODO
 * 
 */
void MOTOR_DeInit(void)
{
    serialClose(uart.connection);
}

/**
 * @brief Execute start motor command
 * 
 * @return UART_STATUS Starting motor result
 */
UART_STATUS MOTOR_Start(void)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::START_MOTOR, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, &f);
}

/**
 * @brief Execute stop motor command
 * 
 * @return UART_STATUS  Stoping motor result
 */
UART_STATUS MOTOR_Stop(void)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::STOP_MOTOR, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, &f);
}

/**
 * 
 * @brief Set the motor ramp final speed registry
 * 
 * @param[in] ref : Value to set in rpm
 * @return UART_STATUS Setting result 
 */
UART_STATUS MOTOR_SetRefSpeed(int ref)
{
    Frame cmd = Frame(1, FRAME_CODES::SET, (int)STEVAL_REGISTERS::RAMP_FIN_SPEED, (int)STEVAL_REGISTERS_LEN::RAMP_FIN_SPEED, ref);
    return send(cmd, uart, &f);
}

/**
 * @brief TODO
 * 
 * @return TODO
 */
UART_STATUS MOTOR_FaultAck(void)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::FAULT_ACT, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, &f);
}

/**
 * @brief TODO
 * 
 * @param[in] duration : TODO
 * @param[in] finalSpeed : TODO
 * @return TODO
 */
UART_STATUS MOTOR_ExecRampSpeed(int duration, int finalSpeed)
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

    Frame cmd = Frame(1, FRAME_CODES::EXE_RAMP, (int)STEVAL_REGISTERS::NO_REG, (int)STEVAL_REGISTERS_LEN::RAMP_EXE, n);
    return send(cmd, uart, &f);
}

/**
 * @brief TODO
 * 
 * @return TODO
 */
UART_STATUS MOTOR_StopRamp(void)
{
    Frame cmd = Frame(1, FRAME_CODES::EXE, (int)STEVAL_REGISTERS::STOP_RAMP, (int)STEVAL_REGISTERS_LEN::EXE_CMD, NO_DATA);
    return send(cmd, uart, &f);
}

/**
 * @brief Get measured motor speed
 *  
 * @param[out] payload : Number of received bytes (expeted 4)
 * @param[out] speed : Measured or estimated speed in rpm
 * @return UART_STATUS Getting result
 */
UART_STATUS MOTOR_GetMeasSpeed(int* payload, int* speed)
{
    Frame rec;
    UART_STATUS status = MOTOR_GetRegistry(STEVAL_REGISTERS::SPEED_MEAS, STEVAL_REGISTERS_LEN::GET, &rec);
    *payload = rec.payload;
    *speed = rec.data;
    return status;
}