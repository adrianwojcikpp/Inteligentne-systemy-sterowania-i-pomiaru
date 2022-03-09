/**
  ******************************************************************************
  * @file    rpi_hal_gpio.h
  * @author  AW 
  * @version V1.0
  * @date    24-Apr-2021
  * @brief   Raspberry Pi GPIO API example header file
  *
  ******************************************************************************
  */
#ifndef RPI_HAL_GPIO_H_
#define RPI_HAL_GPIO_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_delay.h"

/* Typedef -------------------------------------------------------------------*/
typedef enum { GPIO_PIN_RESET = 0, GPIO_PIN_SET } GPIO_PinState;
typedef enum { GPIO_INPUT = 0, GPIO_OUTPUT } GPIO_Direction;

typedef struct {
  int pin;
  GPIO_Direction dir;
  GPIO_PinState value;
} GPIO_Init_TypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief
 * @param[in] hgpio
 * @param[in] n
 * @return 
 */
int HAL_GPIO_Init(GPIO_Init_TypeDef* hgpio, int n);

/**
 * @brief
 * @param[in] pin
 * @return 
 */
int HAL_GPIO_ExportPin(int pin);

/**
 * @brief
 * @param[in] pin
 * @return 
 */
int HAL_GPIO_UnexportPin(int pin);

/**
 * @brief
 * @param[in] pin
 * @param[in] dir
 * @return 
 */
int HAL_GPIO_SetPinDirection(int pin, GPIO_Direction dir);

/**
 * @brief
 * @param[in] pin
 * @return 
 */
GPIO_PinState HAL_GPIO_ReadPin(int pin);

/**
 * @brief
 * @param[in] pin  
 * @param[in] value
 * @return 
 */
int HAL_GPIO_WritePin(int pin, GPIO_PinState value);

#endif /* RPI_HAL_GPIO_H_ */
