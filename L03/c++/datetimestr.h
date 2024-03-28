/**
  ******************************************************************************
  * @file    datetimestr.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    28-Mar-2024
  * @brief   Returns a string with the current date and time, up to milliseconds precision.
  *
  ******************************************************************************
  */
#ifndef DATETIME_H
#define DATETIME_H

/**
 * @brief Returns a string with the current date and time, up to milliseconds precision.
 *
 * The function uses the `localtime` and `gettimeofday` functions to get the current date and time 
 * and format it as a string with the specified precision. The resulting string is stored in 
 * a static buffer, which is reused on subsequent calls to the function.
 *
 * @return A pointer to a static buffer containing the formatted date and time string.
 */
char* datetimestr(void);

#endif /* DATETIME_H */
