/**
  ******************************************************************************
  * @file    pushbtn.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Simple push button driver library.
  *
  ******************************************************************************
  */
#ifndef INC_PUSHBTN_H_
#define INC_PUSHBTN_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#if defined(RASPBERRY_PI)
#include "rpi_hal_gpio.h"
#elif defined(STM32F746xx)
#include "stm32f7xx_hal.h"
#endif

/* Typedef -------------------------------------------------------------------*/
typedef enum {
	RISING_EDGE,
	FALLING_EDGE
} BTN_EdgeTypeDef;

#if defined(RASPBERRY_PI)

#define BTN_PinType int
#define BTN_PinStateType GPIO_PinState

typedef struct {
  BTN_PinType  Pin;
  BTN_EdgeTypeDef Edge;
  BTN_PinStateType State;
} BTN_HandleTypeDef;

#elif defined(STM32F746xx)

#define BTN_PortType GPIO_TypeDef*
#define BTN_PinType uint16_t
#define BTN_PinStateType GPIO_PinState

typedef struct {
  BTN_PortType Port;
  BTN_PinType  Pin;
  BTN_EdgeTypeDef Edge;
  BTN_PinStateType State;
} BTN_HandleTypeDef;

#endif


/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Push button edge detection.
 * @param[in] hbtn Push button handler
 * @return Edge detection flag
 * @retval 1 -> Sensitive edge detected
 * @retval 0 -> Sensitive edge not detected
 */
uint8_t BTN_EdgeDetected(BTN_HandleTypeDef* hbtn);

#endif /* INC_PUSHBTN_H_ */
