/**
  ******************************************************************************
  * @file    encoder_as5600.cpp
  * @author  Jakub Walkowski
  * @author  AW		(adrian.wojcik@put.poznan.pl)
  * @version 3.0.0
  * @date    19-Mar-2024
  * @brief   Aeropendulum angular positon measurement: magnetic encoder AS5600
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <wiringPiI2C.h>

#include "encoder_as5600.h"

/* Private variables ---------------------------------------------------------*/
int as5600;

uint16_t _rawStartAngle;
uint16_t _zPosition;
uint16_t _rawEndAngle;
uint16_t _mPosition;
uint16_t _maxAngle;

/* Private function ----------------------------------------------------------*/

/**
 * @brief Reads one byte register from i2c
 * @param[out] Result : TODO
 * @param[in]  in_adr : TODO
 * @return AS5600 status
 */
AS5600_STATUS readOneByte(uint8_t *Result, uint8_t in_adr)
{
  int response = wiringPiI2CReadReg8(as5600,in_adr);
	if (response !=-1) {
		*Result = response;
		return AS5600_OK;
	}
	return AS5600_ERROR;
}

/**
 * @brief Reads two bytes register from i2c
 * @param[out] Result : TODO
 * @param[in]  in_adr : TODO
 * @return AS5600 status
 */
AS5600_STATUS readTwoBytes(uint16_t *Result, uint16_t in_adr) 
{
  int response = wiringPiI2CReadReg16(as5600,in_adr);
	if (response !=-1) {
		*Result = response;
		return AS5600_OK;
	}
	return AS5600_ERROR;
}

/**
 * @brief Writes one byte to a i2c register
 * @param[in] adr_in : TODO
 * @param[in] dat_in : TODO
 * @return AS5600 status
 */
AS5600_STATUS writeOneByte(uint8_t in_adr, uint8_t dat_in) 
{
  int response = wiringPiI2CWriteReg8(as5600,in_adr,dat_in);
	if (response != -1) {
		return AS5600_OK;
	}
	return AS5600_ERROR;
}

/**
 * @brief Writes two byte to a i2c register
 * @param[in] adr_in : TODO
 * @param[in] dat_in : TODO
 * @return AS5600 status
 */
AS5600_STATUS writeTwoByte(uint16_t in_adr, uint16_t dat_in)
{
  int response = wiringPiI2CWriteReg16(as5600,in_adr,dat_in);
	if (response != -1) {
		return AS5600_OK;
	}
	return AS5600_ERROR;
}

/* Public function -----------------------------------------------------------*/

/**
 * @brief Initializes AS5600
 * @return AS5600 status
 */
AS5600_STATUS ENCODER_Init(void) 
{
	as5600 = wiringPiI2CSetup(AS5600_ADDRESS);
  if(as5600 >= 0)
    return AS5600_OK;
  return AS5600_ERROR;
}

/**
 * @brief Set mode of AS5600
 * @param[in] mode : 0, output PWM,
 *                   1 output analog (full range from 0% to 100% between GND and VDD)
 * @return AS5600 status
 */
AS5600_STATUS ENCODER_SetMode(uint8_t mode)
{
  uint8_t config_status;
  if(readOneByte(&config_status,_conf_lo)==AS5600_OK)
  {
    if(mode == 1){
    	config_status = config_status & 0xcf;
    }
    else{
    	config_status = config_status & 0xef;
    }
    return writeOneByte(_conf_lo, (uint8_t)(config_status << 8));
  }
  return AS5600_ERROR;
}

/**
 * @brief Sets a value in maximum angle register.
 * @details If no value is provided, method will read 
 * position of magnet. Setting this register zeros out 
 * max position register.
 * @param[in] newMaxAngle : new maximum angle to set OR none
 * @return value of max angle register
 */
uint16_t ENCODER_setMaxAngle(uint16_t newMaxAngle)
{
	uint16_t retVal;
	if (newMaxAngle == -1) {
		_maxAngle = ENCODER_getRawAngle();
	} else
		_maxAngle = newMaxAngle;

    writeTwoByte(_mang,newMaxAngle);
	readTwoBytes(&retVal,_mang);
	return retVal;
}

/**
 * @brief TODO
 * @return TODO
 */
uint16_t ENCODER_getMaxAngle(void)
{
	uint16_t result;
	readTwoBytes(&result,_mang);
	return result;
}

/**
 * @brief Sets a value in start position register.
 * @details If no value is provided, method will 
 * read position of magnet.
 * @param[in] startAngle : new start angle position
 * @return value of start position register
 */
uint16_t ENCODER_setStartPosition(uint16_t startAngle)
{
  if(startAngle == -1)
  {
    _rawStartAngle = ENCODER_getRawAngle();
  }
  else
    _rawStartAngle = startAngle;

  writeTwoByte(_zpos, _rawStartAngle);
  readTwoBytes(&_zPosition,_zpos);

  return _zPosition;
}

/**
 * @brief Gets value of start position register.
 * @return value of start position register
 */
uint16_t ENCODER_getStartPosition(void)
{
	uint16_t result;
	readTwoBytes(&result,_zpos);
	return result;
}

/**
 * @brief Sets a value in end position register.
 * @details If no value is provided, method will 
 * read position of magnet.
 * @param[in] endAngle : new end angle position
 * @return value of end position register
 */
uint16_t ENCODER_setEndPosition(uint16_t endAngle)
{
  if(endAngle == -1)
    _rawEndAngle = ENCODER_getRawAngle();
  else
    _rawEndAngle = endAngle;
  writeTwoByte(_mpos, _rawEndAngle);

  readTwoBytes(&_mPosition, _mpos);

  return(_mPosition);
}

/**
 * @brief Gets value of end position register.
 * @return value of end position register
 */
uint16_t ENCODER_getEndPosition(void)
{
	uint16_t result;
	readTwoBytes(&result, _mpos);
	return result;
}

/**
 * @brief Gets raw value of magnet position.
 * @details start, end, and max angle settings do not apply
 * @return value of raw angle register
 */
uint16_t ENCODER_getRawAngle(void)
{
	uint16_t result;
	readTwoBytes(&result,_raw_ang);
	return result;
}

/**
 * @brief Gets scaled value of magnet position.
 * @details start, end, or max angle settings are used to
 * determine value.
 * @return value of scaled angle register
 */
uint16_t ENCODER_getScaledAngle(void)
{
	uint16_t result;
	readTwoBytes(&result,_ang);
	return result;
}

/**
 * @brief Reads status register and examines the MH bit.
 * @return 1 if magnet is detected, 0 if not
 */
int ENCODER_detectMagnet(void)
{
  uint8_t magStatus;
  int retVal = 0;
  /*0 0 MD ML MH 0 0 0*/
  /* MD high = AGC minimum overflow, Magnet to strong */
  /* ML high = AGC Maximum overflow, magnet to weak*/
  /* MH high = magnet detected*/
  readOneByte(&magStatus,_stat);

  if(magStatus & 0x20)
    retVal = 1;

  return retVal;
}

/**
 * @brief Reads status register andexamins the MH,ML,MD bits
 * @return 0 if no magnet is detected
 *      1 if magnet is to weak
 *      2 if magnet is just right
 *      3 if magnet is to strong
 */
int ENCODER_getMagnetStrength(void)
{
  uint8_t magStatus;
  int retVal = 0;
  /*0 0 MD ML MH 0 0 0*/
  /* MD high = AGC minimum overflow, Magnet to strong */
  /* ML high = AGC Maximum overflow, magnet to weak*/
  /* MH high = magnet detected*/
  readOneByte(&magStatus,_stat);
  if(ENCODER_detectMagnet() ==1)
  {
      retVal = 2; /*just right */
      if(magStatus & 0x10)
        retVal = 1; /*to weak */
      else if(magStatus & 0x08)
        retVal = 3; /*to strong */
  }

  return retVal;
}

/**
 * @brief Gets value of AGC register.
 * @return value of AGC register
 */
uint8_t ENCODER_getAgc(void)
{
	uint8_t result;
	readOneByte(&result,_agc);
	return result;
}

/**
 * @brief Gets value of magnitude register.
 * @return value of magnitude register
 */
uint16_t ENCODER_getMagnitude(void)
{
	uint16_t result;
	readTwoBytes(&result,_mag);
	return result;
}

/**
 * @brief Determines how many times chip has been permanently written to.
 * @return value of zmco register
 */
uint8_t ENCODER_getBurnCount(void)
{
	uint8_t result;
	readOneByte(&result,_zmco);
	return result;
}

/**
 * @brief Burns start and end positions to chip.
 * @details THIS CAN ONLY BE DONE 3 TIMES
 * @return 1 success
 *        -1 no magnet
 *        -2 burn limit exceeded
 *        -3 start and end positions not set (useless burn)
 */
int ENCODER_burnAngle(void)
{
  int retVal = 1;
  _zPosition = ENCODER_getStartPosition();
  _mPosition = ENCODER_getEndPosition();
  _maxAngle  = ENCODER_getMaxAngle();

  if(ENCODER_detectMagnet() == 1)
  {
    if(ENCODER_getBurnCount() < 3)
    {
      if((_zPosition == 0)&&(_mPosition ==0))
        retVal = -3;
      else
        writeOneByte(_burn, 0x80);
    }
    else
      retVal = -2;
  }
  else
    retVal = -1;

  return retVal;
}

/**
 * @brief Burns max angle and config data to chip.
 * @details THIS CAN ONLY BE DONE 1 TIME
 * @return 1 success
 *        -1 burn limit exceeded
 *        -2 max angle is to small, must be at or above 18 degrees
 */
int ENCODER_burnMaxAngleAndConfig(void)
{
  int retVal = 1;
  _maxAngle  = ENCODER_getMaxAngle();

  if(ENCODER_getBurnCount() ==0)
  {
    if(_maxAngle*0.087 < 18)
      retVal = -2;
    else
      writeOneByte(_burn, 0x40);
  }
  else
    retVal = -1;

  return retVal;
}

/**
 * @brief TODO
 * @param[in] newAngle : TODO
 * @return TODO
 */
float ENCODER_convertScaledAngleToDegrees(uint16_t newAngle)
{
  uint16_t startPos = ENCODER_getStartPosition();
  uint16_t endPos = ENCODER_getEndPosition();
  uint16_t maxAngle = ENCODER_getMaxAngle();

  float multipler = 0;

  /* max angle and end position are mutually exclusive*/
  if(maxAngle >0)
  {
    if(startPos == 0)
      multipler = (maxAngle*0.0878)/4096;
    else  /*startPos is set to something*/
      multipler = ((maxAngle*0.0878)-(startPos * 0.0878))/4096;
  }
  else
  {
    if((startPos == 0) && (endPos == 0))
      multipler = 0.0878;
    else if ((startPos > 0 ) && (endPos == 0))
      multipler = ((360 * 0.0878) - (startPos * 0.0878)) / 4096;
    else if ((startPos == 0 ) && (endPos > 0))
      multipler = (endPos*0.0878) / 4096;
    else if ((startPos > 0 ) && (endPos > 0))
      multipler = ((endPos*0.0878)-(startPos * 0.0878))/ 4096;
  }
  return (newAngle * multipler);
}

/**
 * @brief TODO
 * @param[in] newAngle : TODO
 * @return TODO
 */
float ENCODER_convertRawAngleToDegrees(uint16_t newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = (float)(newAngle) * 0.087;
  return retVal;
}
