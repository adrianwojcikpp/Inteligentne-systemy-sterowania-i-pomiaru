/**
  ******************************************************************************
  * @file    rpi_hal_gpio_config.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    Sat 19 Jun 23:37:07 CEST 2021
  * @brief
  *          Header file.
  *
  ******************************************************************************
  */
#ifndef RPI_HAL_GPIO_CONFIG_H_
#define RPI_HAL_GPIO_CONFIG_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_gpio.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define LCD_E_Pin  4
#define LCD_RS_Pin 27
#define LCD_D4_Pin 26
#define LCD_D5_Pin 6
#define LCD_D6_Pin 5
#define LCD_D7_Pin 22

#define BTN_Pin    16

#define PIN_ARRAY_LEN(n) sizeof(n)/sizeof(GPIO_Init_TypeDef)

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern GPIO_Init_TypeDef hgpio[];
extern int hgpio_size;

/* Public function prototypes ------------------------------------------------*/

#endif /* RPI_HAL_GPIO_CONFIG_H_ */
