/**
  ******************************************************************************
  * @file    rpi_hal_delay.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Raspberry Pi delay API
  *
  ******************************************************************************
  */
#ifndef RPI_HAL_DELAY_H_
#define RPI_HAL_DELAY_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <time.h>
#include <stdint.h>

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define HAL_Delay HAL_Delay_ms
/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function  ----------------------------------------------------------*/

// https://man7.org/linux/man-pages/man2/nanosleep.2.html
int nanosleep(const struct timespec *req, struct timespec *rem);

void HAL_Delay_ms(uint32_t ms);
void HAL_Delay_us(uint32_t us);

#endif /* RPI_HAL_DELAY_H_ */
