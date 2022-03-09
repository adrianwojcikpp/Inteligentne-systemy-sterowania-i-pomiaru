/**
  ******************************************************************************
  * @file    bh1750.h
  * @author  AW
  * @version V2.0
  * @date    27-Mar-2021
  * @brief   Digital light sensor BH1750 driver in C++ for Raspberry Pi.
  *          Header file.
  *
  ******************************************************************************
  */
  
#ifndef INC_BH1750_H_
#define INC_BH1750_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/

#if defined BH1750_RASPBERRY_PI
#include "rpi_hal_i2c.h"
#elif defined BH1750_STM32
// TOOD: include STM32 HAL 
#endif

/* Typedef -------------------------------------------------------------------*/

#if defined BH1750_RASPBERRY_PI
#define BH1750_I2CType     I2C_Handle_TypeDef*
#define BH1750_AddressType uint8_t
#define BH1750_TimoutType  int 
#elif defined BH1750_STM32
// TOOD: STM32 HAL types support
#endif

typedef struct {
  BH1750_I2CType I2C;          //! I2C bus handler 
  BH1750_AddressType Address;  //! sensor 7-bit address 
  BH1750_TimoutType Timeout;   //! timeout in millisecond
} BH1750_HandleTypeDef;

/* Define --------------------------------------------------------------------*/
#define BH1750_ADDRESS_L 0x23		//! ADDR = 'L' @see BH1750 technical note p. 10
#define BH1750_ADDRESS_H 0x5C		//! ADDR = 'H' @see BH1750 technical note p. 10

#define BH1750_POWER_DOWN							0x00
#define BH1750_POWER_ON								0x01
#define BH1750_RESET									0x07
#define BH1750_CONTINOUS_H_RES_MODE		0x10
#define BH1750_CONTINOUS_H_RES_MODE2	0x11
#define BH1750_CONTINOUS_L_RES_MODE		0x13
#define BH1750_ONE_TIME_H_RES_MODE		0x20
#define BH1750_ONE_TIME_H_RES_MODE2		0x21
#define BH1750_ONE_TIME_L_RES_MODE		0x23

#define BH1750_COMMAND_SIZE	1
#define BH1750_DATA_SIZE		2
#define BH1750_DATA_MSB			0
#define BH1750_DATA_LSB			1

#define BH1750_MAX_LUX 65535.0

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief BH1750 initialization procedure.
 * @note Sensor is set to continuous high resolution mode (1).
 * @param[in] hbh1750 BH1750 digital light sensor handler 
 * @return None
 */
void BH1750_Init(BH1750_HandleTypeDef* hbh1750);

/**
 * @brief BH1750 measurement read routine.
 * @note Uses blocking mode I2C receiving routine.
 * @param[in] hbh1750 BH1750 digital light sensor handler 
 * @return Measurement result in lux [lx]
 */
float BH1750_ReadLux(BH1750_HandleTypeDef* hbh1750);

#endif /* INC_BH1750_H_ */