/**
  ******************************************************************************
  * @file    pushbtn.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Simple push button driver library.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "pushbtn.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

/**
 * @brief Push button edge detection.
 * @param[in] hbtn Push button handler
 * @return Edge detection flag
 * @retval 1 -> Sensitive edge detected
 * @retval 0 -> Sensitive edge not detected
 */
uint8_t BTN_EdgeDetected(BTN_HandleTypeDef* hbtn)
{
  uint8_t EdgeDectectionFlag = 0;

#if defined(STM32F746xx)
  GPIO_PinState state = HAL_GPIO_ReadPin(hbtn->Port, hbtn->Pin);
#else
  GPIO_PinState state = HAL_GPIO_ReadPin(hbtn->Pin);
#endif
  
  if(hbtn->Edge == RISING_EDGE)
    EdgeDectectionFlag = (state == GPIO_PIN_SET && hbtn->State == GPIO_PIN_RESET);
  else if(hbtn->Edge == FALLING_EDGE)
    EdgeDectectionFlag = (state == GPIO_PIN_RESET && hbtn->State == GPIO_PIN_SET);
  
  hbtn->State = state;
  
  return EdgeDectectionFlag;
}
