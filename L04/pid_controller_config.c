/**
  ******************************************************************************
  * @file    pid_controller_config.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    06 Sep 2021 
  * @brief   Simple PID controller implementation.
  *          Configuration file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "pid_controller.h"
#include "control_loop.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
PID_HandleTypeDef pid_ctrl1 = { 
  .Kp = 2.3333f, .Ki = 66.6667f, .Kd = 0.0f,
  .N = 0.01f, .Ts = SAMPLE_TIME, .Limit = 1.0f
};

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
