/**
  ******************************************************************************
  * @file    time_util.h
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Simple time utility: delay and timestamp functions
  * 
  ******************************************************************************
  */

#ifndef __TIME_UTIL_H__
#define __TIME_UTIL_H__

/* Public function prototypes ------------------------------------------------*/
/**
  * @brief Standard delay function based on 'nanosleep'.
  * 
  * @param[in] msec : delay time in millisecond 
  * @retval    0 if success 
  *         != 0 otherwise
  */
int delay_ms(long msec);

/**
 * @brief Time stamp expressed in microseconds.
 * 
 * @retval Current time stamp in microseconds since first function call.
*/
float timestamp_us(void);

#endif // __TIME_UTIL_H__
