/**
  ******************************************************************************
  * @file    time_util.cpp
  * @author  AW         Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 May 2023
  * @brief   Simple time utility: delay and timestamp functions
  * 
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
// GNU C library
#include <time.h>
int nanosleep(const struct timespec *req, struct timespec *rem);
#include <errno.h>

/* Public functions ----------------------------------------------------------*/
/**
  * @brief Standard delay function based on 'nanosleep'.
  * 
  * @param[in] msec : delay time in millisecond 
  * @retval    0 if success 
  *         != 0 otherwise
  */
int delay_ms(long msec)
{
  struct timespec ts;
  int res;

  if (msec < 0)
  {
    errno = EINVAL;
    return -1;
  }

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);

  return res;
}

/**
 * @brief Time stamp expressed in microseconds.
 * 
 * @retval Current time stamp in microseconds since first function call.
*/
float timestamp_us(void)
{
    static bool isStartTimeSet = false;
    static timespec startTime;

    if(!isStartTimeSet)
    {
      clock_gettime(CLOCK_MONOTONIC, &startTime);
      isStartTimeSet = true;
    }

    timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);

    long long int elapsedSeconds = currentTime.tv_sec - startTime.tv_sec;
    long long int elapsedNanoseconds = currentTime.tv_nsec - startTime.tv_nsec;
    long long int elapsedMicroseconds = (elapsedSeconds * 1000000) + (elapsedNanoseconds / 1000);

    return (float)elapsedMicroseconds;
}