/**
  ******************************************************************************
  * @file    rpi_hal_i2c.cpp
  * @author  AW
  * @version V2.0
  * @date    27-Mar-2021
  * @brief   Simple hardware abstraction layer for Raspberry Pi I2C bus
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_i2c.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

/**
 * @brief Adapter /dev/i2c-x initialization 
 * @param[in,out] hi2c I2C handler
 * @return 
 */
int HAL_I2C_Init(I2C_Handle_TypeDef* hi2c)
{
  // Open device
  hi2c->fd = open(hi2c->dev, O_RDWR);
  if (hi2c->fd < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
     return -1;
  }
  return 0;
}

/**
 * @brief Adapter /dev/i2c-x deinitialization 
 * @param[in] hi2c I2C handler
 * @return 
 */
int HAL_I2C_Deinit(I2C_Handle_TypeDef* hi2c)
{
  // Close device
  return close(hi2c->fd);
}

/**
 * @brief Adapter /dev/i2c-x slave address selection 
 * @param[in] hi2c    I2C handler
 * @param[in] address Slave device 7-bit address 
 * @return 
 */
int HAL_I2C_SetSlaveAddress(I2C_Handle_TypeDef* hi2c, int address)
{
  // Set slave address
  if (ioctl(hi2c->fd, I2C_SLAVE, address) < 0) 
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
     return -1;
  }
  return 0;
}

/**
 * @brief Adapter /dev/i2c-x master data transmission routine 
 * @param[in]  hi2c  I2C handler
 * @param[in]  tx    Data to transmit
 * @param[in]  len   Data length
 * @return 
 */
int HAL_I2C_Master_Transmit(I2C_Handle_TypeDef* hi2c, uint8_t* tx, int len)
{
  if (write(hi2c->fd, tx, len) != len) 
  {
    /* ERROR HANDLING: i2c transaction failed */
     return -1;
  }
  return 0;
}

/**
 * @brief Adapter /dev/i2c-x master data reception routine 
 * @param[in]  hi2c  I2C handler
 * @param[out] rx    Receive data buffer
 * @param[in]  len   Data length
 * @return 
 */
int HAL_I2C_Master_Receive(I2C_Handle_TypeDef* hi2c, uint8_t* rx, int len)
{
  if (read(hi2c->fd, rx, len) != len) 
  {
    /* ERROR HANDLING: i2c transaction failed */
     return -1;
  }
  return 0;
}