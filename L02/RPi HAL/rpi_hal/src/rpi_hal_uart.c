/**
  ******************************************************************************
  * @file    rpi_hal_uart.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    Sat 19 Jun 17:16:11 CEST 2021
  * @brief   Simple hardware abstraction layer for Raspberry Pi serial port
  *          Source file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_uart.h"

#if defined(DEBUG)
#include <string.h>
#include <stdio.h>
#include <errno.h>  
#endif

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

int __uart_get_baud(int baud)
{
  switch(baud)
  {
    case     0: return B0;
    case    50: return B50;
    case    75: return B75;
    case   110: return B110;
    case   134: return B134;
    case   150: return B150;
    case   200: return B200;
    case   300: return B300;
    case   600: return B600;
    case  1200: return B1200;
    case  1800: return B1800;
    case  2400: return B2400;
    case  4800: return B4800;
    case  9600: return B9600;
    case 19200: return B19200;
    case 38400: return B38400;
    default: return B9600;
  }
}

/* Public function -----------------------------------------------------------*/

/**
 * @brief Adapter /dev/ttySx initialization 
 * @param[in,out] huart : UART handler
 * @return Initialization status: 0 if OK
 *                               -1 if can't open port
 *                               -2 if can't read settings
 *                               -3 if can't write settings
 */
int HAL_UART_Init(UART_Handle_TypeDef* huart)
{
  huart->fd = open(huart->dev, O_RDWR);
  
  if(huart->fd < 0)
    return -1;   // Can't open device

  struct termios tty;

  // Read in existing settings, and handle any error
  if(tcgetattr(huart->fd , &tty) != 0)
  {
    #if defined(DEBUG)
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    #endif
    return -2;
  }

  tty.c_cflag &= ~PARENB;        // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB;        // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE;         // Clear all bits that set the data size 
  tty.c_cflag |= CS8;            // 8 bits per byte (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore control lines (CLOCAL = 1)

  tty.c_lflag &= ~ICANON;        // Disable canonical mode 
  tty.c_lflag &= ~ECHO;          // Disable echo
  tty.c_lflag &= ~ECHOE;         // Disable erasure
  tty.c_lflag &= ~ECHONL;        // Disable new-line echo
  tty.c_lflag &= ~ISIG;          // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow control
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

  tty.c_oflag &= ~OPOST;      // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR;      // Prevent conversion of newline to carriage return/line feed
  // tty.c_oflag &= ~OXTABS;  // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // tty.c_oflag &= ~ONOEOT;  // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

  tty.c_cc[VTIME] = 255;      // Wait for up to 25.5s (255 deciseconds), returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;

  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, __uart_get_baud(huart->Init.speed));
  cfsetospeed(&tty, __uart_get_baud(huart->Init.speed));

  // Save tty settings, also checking for error
  if(tcsetattr(huart->fd , TCSANOW, &tty) != 0)	  
  {
    #if defined(DEBUG)
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    #endif
    return -3;
  }
  
  return 0; // OK
}

/**
 * @brief Adapter /dev/ttySx deinitialization 
 * @param[in] huart : UART handler
 * @return 
 */
int HAL_UART_Deinit(UART_Handle_TypeDef* huart)
{
  // Close device
  return close(huart->fd);
}

/**
 * @brief Adapter /dev/ttySx data transmission routine 
 * @param[in] huart : UART handler
 * @param[in] tx    : Data to transmit
 * @param[in] len   : Data length
 * @return Writing status: 0 if OK
 *                        -1 if can't write to port
 *                        -2 if incorrect message size
 */
int HAL_UART_Transmit(UART_Handle_TypeDef* huart, uint8_t* tx, int len)
{

   int rslt = write(huart->fd, tx, len); 
   
   if(rslt < 0)
   {
     #if defined(DEBUG)
     printf("Can't write to port [%i]: %s\n", errno, strerror(errno));
     #endif
     return -1; // Can't write to port
   }
 
  if(rslt != len)
  {
    #if defined(DEBUG)
    printf("Incorrect message size [%i]: %s\n", errno, strerror(errno));
    #endif
    return -2; // Incorrect message size
  }
   
  return 0; // OK
}

/**
 * @brief Adapter /dev/ttySx data data reception routine 
 * @param[in]  huart : UART handler
 * @param[out] rx    : Receive data buffer
 * @param[in]  len   : Data length
 * @return Reading status: 0 if OK
 *                        -1 if can't read from port
 *                        -2 if incorrect message size
 */
int HAL_UART_Receive(UART_Handle_TypeDef* huart, uint8_t* rx, int len)
{
   int rslt = read(huart->fd, rx, len); 
   
   if(rslt < 0)
   {
     #if defined(DEBUG)
     printf("Can't read to port [%i]: %s\n", errno, strerror(errno));
     #endif
     return -1; // Can't write to port
   }
 
  if(rslt != len)
  {
    #if defined(DEBUG)
    printf("Incorrect message size [%i]: %s\n", errno, strerror(errno));
    #endif
    return -2; // Incorrect message size
  }

  return 0; // OK
}