/**
  ******************************************************************************
  * @file    rpi_hal_spi.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Simple hardware abstraction layer for Raspberry Pi SPI bus
  *
  ******************************************************************************
  */
#include <stdio.h>
/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_spi.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
/**
 * @brief
 * @param[in] hpsi : 
 * @return 
 */
int HAL_SPI_Init(SPI_Handle_TypeDef* hspi)
{
  //uint8_t mode = SPI_MODE_0;
  //uint8_t bits = 8;           /* SPI0 bits per word  */
  //uint32_t speed = 500000;    /* SPI0 max speed [Hz] */
  //uint16_t delay = 0;         /* SPI0 delay [us]     */
  
  hspi->tr.delay_usecs = (hspi->Init.delay);
	hspi->fd = open(DEV_SPI0, O_RDWR);
	if (hspi->fd < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -1;
  }

	/* SPI0 mode */
	if (ioctl(hspi->fd, SPI_IOC_WR_MODE, &(hspi->Init.mode)) < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -2;
  }
  if (ioctl(hspi->fd, SPI_IOC_RD_MODE, &(hspi->Init.mode)) < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -3;
  }

  /* SPI0 bits per word */
  if (ioctl(hspi->fd, SPI_IOC_WR_BITS_PER_WORD, &(hspi->Init.bits)) < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -4;
  }
  if (ioctl(hspi->fd, SPI_IOC_RD_BITS_PER_WORD, &(hspi->Init.bits)) < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
  }
  hspi->tr.bits_per_word = (hspi->Init.bits);

	/* SPI0 max speed [Hz] */ 
  if (ioctl(hspi->fd, SPI_IOC_WR_MAX_SPEED_HZ, &(hspi->Init.speed)) < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -5;
  }
  
  if (ioctl(hspi->fd, SPI_IOC_RD_MAX_SPEED_HZ, &(hspi->Init.speed)) < 0)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -6;
  }
  hspi->tr.speed_hz = (hspi->Init.speed);
  return 0; 
}

/**
 * @brief
 * @param[in] hpsi : 
 * @return 
 */
int HAL_SPI_Deinit(SPI_Handle_TypeDef* hspi)
{
  return close(hspi->fd);
}

/**
 * @brief
 * @param[in] hpsi : 
 * @param[in] tx : 
 * @param[in] len : 
 * @return 
 */
int HAL_SPI_Transmit(SPI_Handle_TypeDef* hspi, uint8_t* tx, uint32_t len)
{
  hspi->tr.tx_buf = (unsigned long)tx;
  hspi->tr.rx_buf = (unsigned long)NULL;
  hspi->tr.len = len;
  
  if(ioctl(hspi->fd, SPI_IOC_MESSAGE(1), &(hspi->tr)) != len)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -1;
  }
  return 0;
}

/**
 * @brief
 * @param[in] hpsi : 
 * @param[in] tx : 
 * @param[in] rx : 
 * @param[in] len : 
 * @return 
 */
int HAL_SPI_TransmitReceive(SPI_Handle_TypeDef* hspi, uint8_t* tx, uint8_t* rx, uint32_t len)
{
  hspi->tr.tx_buf = (unsigned long)tx;
  hspi->tr.rx_buf = (unsigned long)rx;
  hspi->tr.len = len;
  
  if(ioctl(hspi->fd, SPI_IOC_MESSAGE(1), &(hspi->tr)) != len)
  {
    /* ERROR HANDLING; 
       you can check errno to see what went wrong 
     */
    return -1;
  }
  return 0;
}