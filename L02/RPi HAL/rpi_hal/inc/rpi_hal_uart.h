/**
  ******************************************************************************
  * @file    rpi_hal_uart.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    Sat 19 Jun 17:16:11 CEST 2021
  * @brief   Simple hardware abstraction layer for Raspberry Pi serial port
  *          Header file.
  *
  ******************************************************************************
  */
#ifndef RPI_HAL_UART_H_
#define RPI_HAL_UART_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <fcntl.h>     
#include <termios.h>  
#include <unistd.h>   

/* Typedef -------------------------------------------------------------------*/

typedef struct
{
  int speed;
} UART_Init_TypeDef;

typedef struct
{
  int fd;
  const char* dev;
  UART_Init_TypeDef Init;
} UART_Handle_TypeDef;

/* Define --------------------------------------------------------------------*/
#define DEV_UART0 "/dev/ttyS0"

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Adapter /dev/ttySx initialization 
 * @param[in,out] huart : UART handler
 * @return 
 */
int HAL_UART_Init(UART_Handle_TypeDef* huart);

/**
 * @brief Adapter /dev/ttySx deinitialization 
 * @param[in] huart : UART handler
 * @return 
 */
int HAL_UART_Deinit(UART_Handle_TypeDef* huart);

/**
 * @brief Adapter /dev/ttySx data transmission routine 
 * @param[in] huart : UART handler
 * @param[in] tx    : Data to transmit
 * @param[in] len   : Data length
 * @return 
 */
int HAL_UART_Transmit(UART_Handle_TypeDef* huart, uint8_t* tx, int len);

/**
 * @brief Adapter /dev/ttySx data data reception routine 
 * @param[in]  huart : UART handler
 * @param[out] rx    : Receive data buffer
 * @param[in]  len   : Data length
 * @return 
 */
int HAL_UART_Receive(UART_Handle_TypeDef* huart, uint8_t* rx, int len);

#endif /* RPI_HAL_UART_H_*/