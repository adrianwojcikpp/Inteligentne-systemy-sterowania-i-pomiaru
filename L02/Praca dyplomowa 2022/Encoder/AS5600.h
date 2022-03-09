/*
 * AS5600.h
 *
 *  Created on: Oct 8, 2020
 *      Author: walko
 */

#ifndef INC_AS5600_H_
#define INC_AS5600_H_

typedef enum {
	AS5600_OK = 0, AS5600_ERROR = 1
} AS5600_STATUS;

#define AS5600_ADDRESS 	0x36

/* Registers */
#define _zmco  			0x00
#define _zpos_hi  		0x01
#define _zpos_lo  		0x02   
#define _zpos  		    0x102   
#define _mpos_hi  		0x03
#define _mpos_lo  		0x04
#define _mpos  		    0x304
#define _mang_hi  		0x05
#define _mang_lo  		0x06
#define _mang           0x506	
#define _conf_hi  		0x07
#define _conf_lo  		0x08
#define _raw_ang_hi  	0x0c
#define _raw_ang_lo  	0x0d
#define _raw_ang        0xc0d
#define _ang_hi  		0x0e
#define _ang_lo  		0x0f
#define _ang      		0xe0f
#define _stat  			0x0b
#define _agc  			0x1a
#define _mag_hi  		0x1b
#define _mag_lo  		0x1c
#define _mag            0x1b1c
#define _burn  			0xff

#include <stdint.h>
AS5600_STATUS AS5600_Init(int *fd);
AS5600_STATUS AS5600_SetMode(uint8_t mode);

uint16_t setMaxAngle(uint16_t newMaxAngle);
uint16_t getMaxAngle();
uint16_t setStartPosition(uint16_t startAngle);
uint16_t getStartPosition();
uint16_t setEndPosition(uint16_t endAngle);
uint16_t getEndPosition();
uint16_t getRawAngle();
uint16_t getScaledAngle();
int detectMagnet();
int getMagnetStrength();
uint8_t getAgc();
uint16_t getMagnitude();
uint8_t getBurnCount();
int burnAngle();
int burnMaxAngleAndConfig();
float convertScaledAngleToDegrees(uint16_t newAngle);
float convertRawAngleToDegrees(uint16_t newAngle);

#endif /* INC_AS5600_H_ */