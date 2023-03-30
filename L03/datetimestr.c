/**
  ******************************************************************************
  * @file    datetimestr.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    30-Mar-2023
  * @brief   Returns a string with the current date and time, up to milliseconds precision.
  *
  ******************************************************************************
  */

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

char* datetimestr(void)
{
    static char buffer[128];
    struct timeval tv;
    struct tm* tm_info;

    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);

    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", tm_info);
    sprintf(buffer + strlen(buffer), ".%03ld", tv.tv_usec / 1000);

    return buffer;
}
