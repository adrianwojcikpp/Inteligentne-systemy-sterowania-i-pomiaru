/**
  ******************************************************************************
  * @file    motor_steval.h
  * @author  Jakub Walkowski
  * @author  AW		(adrian.wojcik@put.poznan.pl)
  * @version 3.0.0
  * @date    19-Mar-2024
  * @brief   Aeropendulum angular drive: STEVAL serial communication
  *
  ******************************************************************************
  */

#ifndef INC_MOTOR_STEVAL_H_
#define INC_MOTOR_STEVAL_H_

/* Includes ------------------------------------------------------------------*/
#include <climits>

#include "motor_steval_reg.h"

/* Define --------------------------------------------------------------------*/
#define NO_DATA INT_MAX

/* Typedef -------------------------------------------------------------------*/
/**
 * @brief Uart connection object
 * 
 */
struct UART
{
    int baud;
    const char *device;
    int connection;         /*< WiringPi UART connection ID */
};
/**
 * @brief UART frame obejct
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
            printf("[ERROR_UART_DATA] %s\n", "Error in Frame constructor.");
            throw;
        }
        data = 0;
        payload = array[1];
        CRC = array[lenght - 1];

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

            if (sig)
                data = -((~data) & (0xffff)) - 1;
            frameCode = FRAME_CODES::RECEIVE;
            motorId = -1;
  
        }
        else if (payload == 1 && array[0] != 0xf0)
        {
            data = array[2];
            frameCode = FRAME_CODES::ERROR;
            motorId = -1;
        }
        else if (array[0] != 0xf0)
        {
            printf("[ERROR_UART_DATA] %s FRAME:", "Error in Frame constructor.");
            for (int i = 0; i < lenght; i++)
            {
                printf("%02x ", array[i]);
            }
            printf("\n");
            throw;
        }
    }

    int motorId;           /*< Motor id */
    FRAME_CODES frameCode; /*< Frame code from FRAME_CODES enum */
    int reg;               /*< Motor control register id from STEVAL_REGISTERS enum */
    int payload;           /*< Motor control register payload length */
    long long data;        /*< Data in frame */
    int CRC;               /*< Cyclic redundancy check */

};

/* Public function prototypes ------------------------------------------------*/

std::ostream& operator<<(std::ostream& out, const ERROR_CODES value);

/**
 * @brief Set the registry value
 * 
 * @param[in] reg  : Motor control register id
 * @param[in] regL : Montrol register payload length
 * @param[in] data : Value to set
 * @return UART_STATUS Setting result
 */
UART_STATUS MOTOR_SetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, int data);

/**
 * @brief Get the registry value
 * 
 * @param reg Motor control register id
 * @param regL Montrol register payload length
 * @return UART_STATUS Getting result
 */
UART_STATUS MOTOR_GetRegistry(STEVAL_REGISTERS reg, STEVAL_REGISTERS_LEN regL, Frame *f);

/**
 * @brief TODO
 * 
 * @return TODO
 */
UART_STATUS MOTOR_Init(void);

/**
 * @brief TODO
 * 
 */
void MOTOR_DeInit(void);

/**
 * @brief Execute start motor command
 * 
 * @return UART_STATUS Starting motor result
 */
UART_STATUS MOTOR_Start(void);

/**
 * @brief Execute stop motor command
 * 
 * @return UART_STATUS  Stoping motor result
 */
UART_STATUS MOTOR_Stop(void);

/**
 * 
 * @brief Set the motor ramp final speed registry
 * 
 * @param[in] ref : Value to set in rpm
 * @return UART_STATUS Setting result 
 */
UART_STATUS MOTOR_SetRefSpeed(int ref);

/**
 * @brief TODO
 * 
 * @return TODO
 */
UART_STATUS MOTOR_FaultAck(void);

/**
 * @brief TODO
 * 
 * @param[in] duration : TODO
 * @param[in] finalSpeed : TODO
 * @return TODO
 */
UART_STATUS MOTOR_ExecRampSpeed(int duration, int finalSpeed);

/**
 * @brief TODO
 * 
 * @return TODO
 */
UART_STATUS MOTOR_StopRamp(void);

/**
 * @brief Get measured motor speed
 *  
 * @param[out] payload : Number of received bytes (expeted 4)
 * @param[out] speed : Measured or estimated speed in rpm
 * @return UART_STATUS Getting result
 */
UART_STATUS MOTOR_GetMeasSpeed(int* payload, int* speed);

/**
 * @brief TODO
 *  
 * @param[out] payload : Number of received bytes (expeted ?)
 * @param[out] error : TODO
 * @return UART_STATUS Getting result
 */
UART_STATUS MOTOR_GetErrorStatus(int* payload, ERROR_CODES* error);

#endif /* INC_MOTOR_STEVAL_H_ */