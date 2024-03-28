/**
  ******************************************************************************
  * @file    datetimestr.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    28-Mar-2024
  * @brief   Returns a string with the current date and time, up to milliseconds precision.
  *
  ******************************************************************************
  */

// C++ standard libraries
#include <cstdio>
#include <cstring>

// POSIX libraries
#include <time.h>
#include <sys/time.h>

const char* datetimestr(void)
{
    static char buffer[128];
    struct timeval tv;
    struct tm* tm_info;

    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);

    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", tm_info);
    std::sprintf(buffer + std::strlen(buffer), ".%03ld", tv.tv_usec / 1000);

    return buffer;
}
