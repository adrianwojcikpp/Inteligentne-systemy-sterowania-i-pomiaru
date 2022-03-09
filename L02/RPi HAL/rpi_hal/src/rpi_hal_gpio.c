/**
  ******************************************************************************
  * @file    rpi_hal_gpio.c
  * @author  AW 
  * @version V1.0
  * @date    24-Apr-2021
  * @brief   Raspberry Pi GPIO API example source file
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_gpio.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define GPIO_BUFFER_MAX 3
#define GPIO_DIRECTION_MAX 35
#define GPIO_VALUE_MAX 30

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

int HAL_GPIO_Init(GPIO_Init_TypeDef* hgpio, int n)
{
  for(int i = 0; i < n; i++)
  {
    if(HAL_GPIO_ExportPin(hgpio[i].pin) < 0)
      return -100-i;
    
    if(HAL_GPIO_SetPinDirection(hgpio[i].pin, hgpio[i].dir) < 0)
      return -200-i;
    
    if(hgpio[i].pin == GPIO_OUTPUT)
    {
      if(HAL_GPIO_WritePin(hgpio[i].pin, hgpio[i].value) < 0)
        return -300-i;
    }
  }
  return 0;
}

int HAL_GPIO_ExportPin(int pin)
{
  int fd = open("/sys/class/gpio/export", O_WRONLY);
  if(fd == -1) 
  {
    fprintf(stderr, "Failed to open export for writing!\n");
    return -1;
  }

  char buffer[GPIO_BUFFER_MAX];
  ssize_t bytes_written = snprintf(buffer, GPIO_BUFFER_MAX, "%d", pin);
  write(fd, buffer, bytes_written);
  close(fd);
  return 0;
}

int HAL_GPIO_UnexportPin(int pin)
{
  int fd = open("/sys/class/gpio/unexport", O_WRONLY);
  if(fd == -1) 
  {
    fprintf(stderr, "Failed to open unexport for writing!\n");
    return -1;
  }

  char buffer[GPIO_BUFFER_MAX];
  ssize_t bytes_written = snprintf(buffer, GPIO_BUFFER_MAX, "%d", pin);
  write(fd, buffer, bytes_written);
  close(fd);
  return 0;
}

int HAL_GPIO_SetPinDirection(int pin, GPIO_Direction dir)
{
  static const char dir_str[][4] = {"in", "out"};
  static const int dir_str_len[] = {2, 3};

  char path[GPIO_DIRECTION_MAX];
  snprintf(path, GPIO_DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
  int fd = open(path, O_WRONLY);
  if(fd == -1) 
  {
    fprintf(stderr, "Failed to open GPIO direction for writing!\n");
    return -1;
  }

  if(write(fd, dir_str[dir == GPIO_INPUT ? 0 : 1], dir_str_len[dir == GPIO_INPUT ? 0 : 1]) == -1) 
  {
    fprintf(stderr, "Failed to set direction!\n");
    return -1;
  }

  close(fd);
  return 0;
}

GPIO_PinState HAL_GPIO_ReadPin(int pin)
{
  char path[GPIO_VALUE_MAX];
  snprintf(path, GPIO_VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
  int fd = open(path, O_RDONLY);
  if(fd == -1)
  {
    fprintf(stderr, "Failed to open GPIO value for reading!\n");
    return -1 ;
  }

  char value;
  if(read(fd, &value, 1) == -1) 
  {
    fprintf(stderr, "Failed to read value!\n");
    return -1 ;
  }

  close(fd);

  if(value == '1')
    return GPIO_PIN_SET;
  else if(value == '0')
    return GPIO_PIN_RESET;
  else
    return -1;
}

int HAL_GPIO_WritePin(int pin, GPIO_PinState value)
{
  static const char values_str[] = {'0', '1'};

  char path[GPIO_VALUE_MAX];
  snprintf(path, GPIO_VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
  int fd = open(path, O_WRONLY);
  if (fd == -1) 
  {
    fprintf(stderr, "Failed to open GPIO value for writing!\n");
    return -1;
  }

  if(write(fd, &values_str[value == GPIO_PIN_RESET ? 0 : 1], 1) != 1) 
  {
    fprintf(stderr, "Failed to write value!\n");
    return -1;
  }

  close(fd);
  return 0;
}