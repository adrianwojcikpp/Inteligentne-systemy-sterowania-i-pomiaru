#include "AS5600.h"
#include <wiringPiI2C.h>
#include <stdio.h>

int as5600;

uint16_t _rawStartAngle;
uint16_t _zPosition;
uint16_t _rawEndAngle;
uint16_t _mPosition;
uint16_t _maxAngle;

/*******************************************************
* Reads one byte register from i2c
* @param[out] Resoult
* @param[in] in_adr
* @return AS5600 status
*******************************************************/
AS5600_STATUS readOneByte(uint8_t *Resoult,uint8_t in_adr) {
	
    int response = wiringPiI2CReadReg8(as5600,in_adr);
	if (response !=-1) {
		*Resoult = response;
		return AS5600_OK;
	}
	return AS5600_ERROR;
}
/*******************************************************
* Reads two bytes register from i2c
* @param[out] Resoult
* @param[in] in_adr
* @return AS5600 status
*******************************************************/
AS5600_STATUS readTwoBytes(uint16_t *Resoult, uint16_t in_adr) {
    int response = wiringPiI2CReadReg16(as5600,in_adr);
	if (response !=-1) {
		*Resoult = response;
		return AS5600_OK;
	}
	return AS5600_ERROR;
}
/*******************************************************
* Writes one byte to a i2c register
* @param[in] adr_in
* @param[in] dat_in
* @return AS5600 status
*******************************************************/
AS5600_STATUS writeOneByte(uint8_t in_adr, uint8_t dat_in) {
    int response = wiringPiI2CWriteReg8(as5600,in_adr,dat_in);
	if (response !=-1) {
		return AS5600_OK;
	}
	return AS5600_ERROR;
}
/*******************************************************
* Writes two byte to a i2c register
* @param[in] adr_in
* @param[in] dat_in
* @return AS5600 status
*******************************************************/
AS5600_STATUS writeTwoByte(uint16_t in_adr, uint16_t dat_in) {
    int response = wiringPiI2CWriteReg16(as5600,in_adr,dat_in);
	if (response !=-1) {
		return AS5600_OK;
	}
	return AS5600_ERROR;
}
/*******************************************************
* Initialize AS5600
* @param[out] fd
* @return AS5600 status
*******************************************************/
AS5600_STATUS AS5600_Init(int *fd) {
	*fd,as5600 = wiringPiI2CSetup(AS5600_ADDRESS);
    //as5600= *fd;
    return AS5600_OK;
}
/*******************************************************
* Set mode of AS5600
* mode = 0, output PWM,
* mode = 1 output analog (full range from 0% to 100% between GND and VDD)
* @param[in] mode
* @return AS5600 status
*******************************************************/
AS5600_STATUS AS5600_SetMode(uint8_t mode){
    uint8_t config_status;
    if(readOneByte(&config_status,_conf_lo)==AS5600_OK){
    	if(mode == 1){
    	        config_status = config_status & 0xcf;
    	    }else{
    	        config_status = config_status & 0xef;
    	    }
    	return writeOneByte(_conf_lo, (uint8_t)(config_status << 8));
    }
    return AS5600_ERROR;
}
/*******************************************************
* Sets a value in maximum angle register.
* If no value is provided, method will read position of
* magnet.  Setting this register zeros out max position
* register.
* @param[in] newMaxAngle new maximum angle to set OR none
* @return value of max angle register
*******************************************************/
uint16_t setMaxAngle(uint16_t newMaxAngle) {
	uint16_t retVal;
	if (newMaxAngle == -1) {
		_maxAngle = getRawAngle();
	} else
		_maxAngle = newMaxAngle;

    writeTwoByte(_mang,newMaxAngle);
	readTwoBytes(&retVal,_mang);
	return retVal;
}
uint16_t getMaxAngle()
{
	uint16_t result;
	readTwoBytes(&result,_mang);
	return result;
}
/*******************************************************
 * Sets a value in start position register.
 * If no value is provided, method will read position of
 * magnet.
 * @param[in] startAngle new start angle position
 * @return value of start position register
*******************************************************/
uint16_t setStartPosition(uint16_t startAngle)
{
  if(startAngle == -1)
  {
    _rawStartAngle = getRawAngle();
  }
  else
    _rawStartAngle = startAngle;

  writeTwoByte(_zpos, _rawStartAngle);
  readTwoBytes(&_zPosition,_zpos);

  return _zPosition;
}
/*******************************************************
* Gets value of start position register.
* @return value of start position register
*******************************************************/
uint16_t getStartPosition()
{
	uint16_t result;
	readTwoBytes(&result,_zpos);
	return result;
}
/*******************************************************
* Sets a value in end position register.
* If no value is provided, method will read position of
* magnet.
* @param[in] endAngle new end angle position
* @return value of end position register
*******************************************************/
uint16_t setEndPosition(uint16_t endAngle)
{
  if(endAngle == -1)
    _rawEndAngle = getRawAngle();
  else
    _rawEndAngle = endAngle;
  writeTwoByte(_mpos, _rawEndAngle);

  readTwoBytes(&_mPosition, _mpos);

  return(_mPosition);
}
/*******************************************************
* Gets value of end position register.
* @return value of end position register
*******************************************************/
uint16_t getEndPosition()
{
	uint16_t result;
	readTwoBytes(&result, _mpos);
	return result;
}
/*******************************************************
* Gets raw value of magnet position.
* start, end, and max angle settings do not apply
* @return value of raw angle register
*******************************************************/
uint16_t getRawAngle()
{
	uint16_t result;
	readTwoBytes(&result,_raw_ang);
	return result;
}
/*******************************************************
* Gets scaled value of magnet position.
* start, end, or max angle settings are used to
* determine value.
* @return value of scaled angle register
*******************************************************/
uint16_t getScaledAngle()
{
	uint16_t result;
	readTwoBytes(&result,_ang);
	return result;
}
/*******************************************************
* Reads status register and examines the
* MH bit.
* @return 1 if magnet is detected, 0 if not
*******************************************************/
int detectMagnet()
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
/*******************************************************
* Reads status register andexamins the MH,ML,MD bits
* @return 0 if no magnet is detected
*      1 if magnet is to weak
*      2 if magnet is just right
*      3 if magnet is to strong
*******************************************************/
int getMagnetStrength()
{
  uint8_t magStatus;
  int retVal = 0;
  /*0 0 MD ML MH 0 0 0*/
  /* MD high = AGC minimum overflow, Magnet to strong */
  /* ML high = AGC Maximum overflow, magnet to weak*/
  /* MH high = magnet detected*/
  readOneByte(&magStatus,_stat);
  if(detectMagnet() ==1)
  {
      retVal = 2; /*just right */
      if(magStatus & 0x10)
        retVal = 1; /*to weak */
      else if(magStatus & 0x08)
        retVal = 3; /*to strong */
  }

  return retVal;
}
/*******************************************************
* Gets value of AGC register.
* @return value of AGC register
*******************************************************/
uint8_t getAgc()
{
	uint8_t result;
	readOneByte(&result,_agc);
	return result;
}
/*******************************************************
* Gets value of magnitude register.
* @return value of magnitude register
*******************************************************/
uint16_t getMagnitude()
{
	uint16_t result;
	readTwoBytes(&result,_mag);
	return result;
}
/*******************************************************
* Determines how many times chip has been
* permanently written to.
* @return value of zmco register
*******************************************************/
uint8_t getBurnCount()
{
	uint8_t result;
	readOneByte(&result,_zmco);
	return result;
}
/*******************************************************
* Burns start and end positions to chip.
* THIS CAN ONLY BE DONE 3 TIMES
* @return 1 success
*     -1 no magnet
*     -2 burn limit exceeded
*     -3 start and end positions not set (useless burn)
*******************************************************/
int burnAngle()
{
  int retVal = 1;
  _zPosition = getStartPosition();
  _mPosition = getEndPosition();
  _maxAngle  = getMaxAngle();

  if(detectMagnet() == 1)
  {
    if(getBurnCount() < 3)
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
/*******************************************************
* Burns max angle and config data to chip.
* THIS CAN ONLY BE DONE 1 TIME
* @return 1 success
*     -1 burn limit exceeded
*     -2 max angle is to small, must be at or above 18 degrees
*******************************************************/
int burnMaxAngleAndConfig()
{
  int retVal = 1;
  _maxAngle  = getMaxAngle();

  if(getBurnCount() ==0)
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
float convertScaledAngleToDegrees(uint16_t newAngle)
{
  uint16_t startPos = getStartPosition();
  uint16_t endPos = getEndPosition();
  uint16_t maxAngle = getMaxAngle();

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
float convertRawAngleToDegrees(uint16_t newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = (float)(newAngle) * 0.087;
  return retVal;
}
