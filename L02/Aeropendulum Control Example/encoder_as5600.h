/**
  ******************************************************************************
  * @file    encoder_as5600.h
  * @author  Jakub Walkowski
  * @author  AW		(adrian.wojcik@put.poznan.pl)
  * @version 3.0.0
  * @date    19-Mar-2024
  * @brief   Aeropendulum angular positon measurement: magnetic encoder AS5600
  *
  ******************************************************************************
  */

#ifndef INC_AS5600_H_
#define INC_AS5600_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Typedef -------------------------------------------------------------------*/
typedef enum {
	AS5600_OK = 0, AS5600_ERROR = 1
} AS5600_STATUS;

/* Define --------------------------------------------------------------------*/
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

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Initializes AS5600
 * @return AS5600 status
 */
AS5600_STATUS ENCODER_Init(void);

/**
 * @brief Set mode of AS5600
 * @param[in] mode : 0, output PWM,
 *                   1 output analog (full range from 0% to 100% between GND and VDD)
 * @return AS5600 status
 */
AS5600_STATUS ENCODER_SetMode(uint8_t mode);

/**
 * @brief Sets a value in maximum angle register.
 * @details If no value is provided, method will read 
 * position of magnet. Setting this register zeros out 
 * max position register.
 * @param[in] newMaxAngle : new maximum angle to set OR none
 * @return value of max angle register
 */
uint16_t ENCODER_setMaxAngle(uint16_t newMaxAngle);

/**
 * @brief TODO
 * @return TODO
 */
uint16_t ENCODER_getMaxAngle(void);

/**
 * @brief Sets a value in start position register.
 * @details If no value is provided, method will 
 * read position of magnet.
 * @param[in] startAngle : new start angle position
 * @return value of start position register
 */
uint16_t ENCODER_setStartPosition(uint16_t startAngle);

/**
 * @brief Gets value of start position register.
 * @return value of start position register
 */
uint16_t ENCODER_getStartPosition(void);

/**
 * @brief Sets a value in end position register.
 * @details If no value is provided, method will 
 * read position of magnet.
 * @param[in] endAngle : new end angle position
 * @return value of end position register
 */
uint16_t ENCODER_setEndPosition(uint16_t endAngle);

/**
 * @brief Gets value of end position register.
 * @return value of end position register
 */
uint16_t ENCODER_getEndPosition(void);

/**
 * @brief Gets raw value of magnet position.
 * @details start, end, and max angle settings do not apply
 * @return value of raw angle register
 */
uint16_t ENCODER_getRawAngle(void);

/**
 * @brief Gets scaled value of magnet position.
 * @details start, end, or max angle settings are used to
 * determine value.
 * @return value of scaled angle register
 */
uint16_t ENCODER_getScaledAngle(void);

/**
 * @brief Reads status register and examines the MH bit.
 * @return 1 if magnet is detected, 0 if not
 */
int ENCODER_detectMagnet(void);

/**
 * @brief Reads status register andexamins the MH,ML,MD bits
 * @return 0 if no magnet is detected
 *      1 if magnet is to weak
 *      2 if magnet is just right
 *      3 if magnet is to strong
 */
int ENCODER_getMagnetStrength(void);

/**
 * @brief Gets value of AGC register.
 * @return value of AGC register
 */
uint8_t ENCODER_getAgc(void);

/**
 * @brief Gets value of magnitude register.
 * @return value of magnitude register
 */
uint16_t ENCODER_getMagnitude(void);

/**
 * @brief Determines how many times chip has been permanently written to.
 * @return value of zmco register
 */
uint8_t ENCODER_getBurnCount(void);

/**
 * @brief Burns start and end positions to chip.
 * @details THIS CAN ONLY BE DONE 3 TIMES
 * @return 1 success
 *        -1 no magnet
 *        -2 burn limit exceeded
 *        -3 start and end positions not set (useless burn)
 */
int ENCODER_burnAngle(void);

/**
 * @brief Burns max angle and config data to chip.
 * @details THIS CAN ONLY BE DONE 1 TIME
 * @return 1 success
 *        -1 burn limit exceeded
 *        -2 max angle is to small, must be at or above 18 degrees
 */
int ENCODER_burnMaxAngleAndConfig(void);

/**
 * @brief TODO
 * @param[in] newAngle : TODO
 * @return TODO
 */
float ENCODER_convertScaledAngleToDegrees(uint16_t newAngle);

/**
 * @brief TODO
 * @param[in] newAngle : TODO
 * @return TODO
 */
float ENCODER_convertRawAngleToDegrees(uint16_t newAngle);

#endif /* INC_AS5600_H_ */