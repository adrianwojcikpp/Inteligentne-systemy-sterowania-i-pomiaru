/**
  ******************************************************************************
  * @file    bh1750_config.c
  * @author  AW
  * @version V2.0
  * @date    27-Mar-2021
  * @brief   Digital light sensor BH1750 driver in C++ for Raspberry Pi.
  *          Source file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bh1750.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief Platform-specific command writing routine
 * @param[in] hbh1750 BH1750 digital light sensor handler 
 * @param[in] command Single-byte command
 */
void __bh1750_i2c_write_command(BH1750_HandleTypeDef* hbh1750, uint8_t command);

/**
 * @brief Platform-specific measurement reading routine
 * @param[in] hbh1750 BH1750 digital light sensor handler 
 * @param[out] data Two-byte raw measurement data array
 */
void __bh1750_i2c_read_data(BH1750_HandleTypeDef* hbh1750, uint8_t* data);

/* Private function ----------------------------------------------------------*/
#if defined BH1750_RASPBERRY_PI

void __bh1750_i2c_write_command(BH1750_HandleTypeDef* hbh1750, uint8_t command)
{
  HAL_I2C_Master_Transmit(hbh1750->I2C, &command, BH1750_COMMAND_SIZE);
}

void __bh1750_i2c_read_data(BH1750_HandleTypeDef* hbh1750, uint8_t* data)
{
  HAL_I2C_Master_Receive(hbh1750->I2C, data, BH1750_DATA_SIZE);
}

#elif defined BH1750_STM32

// TOOD: STM32 HAL I2C support

#endif

/* Public function -----------------------------------------------------------*/
/**
 * @brief BH1750 initialization procedure.
 * @note Sensor is set to continuous high resolution mode (1).
 *       Uses blocking mode I2C transmitting routine.
 * @param[in] hbh1750 BH1750 digital light sensor handler 
 * @return None
 */
void BH1750_Init(BH1750_HandleTypeDef* hbh1750)
{
  __bh1750_i2c_write_command(hbh1750, BH1750_POWER_ON);
  __bh1750_i2c_write_command(hbh1750, BH1750_CONTINOUS_H_RES_MODE);
}

/**
 * @brief BH1750 measurement read routine.
 * @note Uses blocking mode I2C receiving routine.
 * @param[in] hbh1750 BH1750 digital light sensor handler 
 * @return Measurement result in lux [lx]
 */
float BH1750_ReadLux(BH1750_HandleTypeDef* hbh1750)
{
  uint8_t rxarray[BH1750_DATA_SIZE];
  __bh1750_i2c_read_data(hbh1750, rxarray);
  // @see BH1750 technical note p. 10;
  return ((rxarray[BH1750_DATA_MSB]<<8) | rxarray[BH1750_DATA_LSB]) / 1.2;
}