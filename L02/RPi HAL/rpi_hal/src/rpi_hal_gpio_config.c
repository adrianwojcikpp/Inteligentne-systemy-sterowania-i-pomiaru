/**
  ******************************************************************************
  * @file    rpi_hal_gpio_config.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    Sat 19 Jun 23:37:07 CEST 2021
  * @brief
  *          Source file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_gpio_config.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
GPIO_Init_TypeDef hgpio[] = {
  /* LCD Pins */
  { LCD_E_Pin,  GPIO_OUTPUT, GPIO_PIN_RESET },
  { LCD_RS_Pin, GPIO_OUTPUT, GPIO_PIN_RESET },
  { LCD_D4_Pin, GPIO_OUTPUT, GPIO_PIN_RESET },
  { LCD_D4_Pin, GPIO_OUTPUT, GPIO_PIN_RESET },
  { LCD_D4_Pin, GPIO_OUTPUT, GPIO_PIN_RESET },
  { LCD_D4_Pin, GPIO_OUTPUT, GPIO_PIN_RESET },
  /* Push-button Pin */
  {BTN_Pin,     GPIO_INPUT,  GPIO_PIN_RESET },
  
};
 
int hgpio_size = PIN_ARRAY_LEN(hgpio);

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
