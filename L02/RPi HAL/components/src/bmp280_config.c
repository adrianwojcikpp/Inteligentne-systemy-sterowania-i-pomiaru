/**
  ******************************************************************************
  * @file    bmp280_config.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Configuration file for BMP280 sensor driver library: 
  *          SPI routines implementation
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bmp280_config.h"
#include "rpi_hal_delay.h"
#include "rpi_hal_spi.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define BMP280_SPI_BUFFER_LEN 28
#define BMP280_DATA_INDEX     1

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
struct bmp280_dev temp_press_sensor = {
  .dev_id = 0,
  .intf = BMP280_SPI_INTF,
  .read = bmp280_spi_reg_read, .write = bmp280_spi_reg_write,
  .delay_ms = HAL_Delay_ms
};

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

/*!
 *  @brief Initialization function
 *
 *  @param[in] bmp        : BMP280 device structure
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t BMP280_Init(struct bmp280_dev* bmp)
{
  int8_t rslt;
  struct bmp280_config conf;

  rslt = bmp280_init(bmp);

  /* Always read the current settings before writing, especially when all the configuration is not modified  */
  rslt = bmp280_get_config(&conf, bmp);

  /* configuring the temperature oversampling, filter coefficient and output data rate */
  /* Overwrite the desired settings */
  conf.filter = BMP280_FILTER_COEFF_2;

  /* Temperature oversampling set at 1x */
  conf.os_temp = BMP280_OS_4X;

  /* Temperature oversampling set at 1x */
  conf.os_pres = BMP280_OS_4X;

  /* Setting the output data rate as 1 Hz (100 ms) */
  conf.odr = BMP280_ODR_1000_MS;

  rslt = bmp280_set_config(&conf, bmp);

  /* Always set the power mode after setting the configuration */
  rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, bmp);

  return rslt;
}

/*!
 *  @brief Function for writing the sensor's registers through SPI bus.
 *
 *  @param[in] cs           : Chip select to enable the sensor.
 *  @param[in] reg_addr     : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose data has to be written.
 *  @param[in] length       : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t bmp280_spi_reg_write(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

  /* Implement the SPI write routine according to the target machine. */
  uint8_t txarray[BMP280_SPI_BUFFER_LEN];
  uint8_t stringpos;

  txarray[0] = reg_addr;
  for (stringpos = 0; stringpos < length; stringpos++) {
    txarray[stringpos+BMP280_DATA_INDEX] = reg_data[stringpos];
  }
  /* Software slave selection procedure */
  // TODO: Hardware CS0

  /* Data exchange */
  int status = HAL_SPI_Transmit(&hspi0, (uint8_t*)(&txarray), length+1);

  /* Disable all slaves */
  // TODO: Hardware CS0
    
  return (int8_t)status;
}

/*!
 *  @brief Function for reading the sensor's registers through SPI bus.
 *
 *  @param[in] cs       : Chip select to enable the sensor.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t bmp280_spi_reg_read(uint8_t cs, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
  /* Implement the SPI read routine according to the target machine. */
  uint8_t txarray[BMP280_SPI_BUFFER_LEN] = {0,};
  uint8_t rxarray[BMP280_SPI_BUFFER_LEN] = {0,};
  uint8_t stringpos;

  txarray[0] = reg_addr;

  /* Software slave selection procedure */
  // TODO: Hardware CS0

  /* Data exchange */
  int status = HAL_SPI_TransmitReceive(&hspi0, (uint8_t*)(&txarray), (uint8_t*)(&rxarray), length+1);

  /* Disable all slaves */
  // TODO: Hardware CS0

  for (stringpos = 0; stringpos < length; stringpos++) {
    *(reg_data + stringpos) = rxarray[stringpos + BMP280_DATA_INDEX];
  }

  return (int8_t)status;
}