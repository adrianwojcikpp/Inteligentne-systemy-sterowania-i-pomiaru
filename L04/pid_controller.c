/**
  ******************************************************************************
  * @file    pid_controller.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    06 Sep 2021 
  * @brief   Simple PID controller implementation.
  *          Source file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "pid_controller.h"

/* Public function -----------------------------------------------------------*/

void PID_Init(PID_HandleTypeDef* hpid)
{
  hpid->e_prev = 0.0f;
  hpid->e_int = 0.0f;
  hpid->d_prev = 0.0f;
}
 
float PID_GetOutput(PID_HandleTypeDef* hpid, float yref, float y)
{
  float u;     // control signal (before saturation)
  float u_sat; // control signal (after saturation)
  float e = yref - y; // control error

  // PID algorithm based on MATLAB doc
  // Parallel Form:
  //   u = Kp*e + Ki*e/s + Kd*N / (1 + N/s)
  // Forward Euler:
  //   1/s = Ts/(z - 1)

  /* Integral */
  hpid->e_int += hpid->Ki * hpid->Ts * e;

  /* Derivative */
  hpid->d_prev = (hpid->Kd*hpid->N)*(e - hpid->e_prev) + (1.0f - hpid->N*hpid->Ts)*hpid->d_prev;
  hpid->e_prev = e;

  /* Output */
  u = (hpid->Kp * e) + hpid->e_int + hpid->d_prev;

  /* Saturation */
  if( u > hpid->Limit )
	  u_sat = hpid->Limit;
  else if( u < -hpid->Limit )
	  u_sat = -hpid->Limit;
  else
	  u_sat = u;

  /* Anti wind-up */
  if( u != u_sat)
	hpid->e_int -= hpid->Ki * hpid->Ts * e;

  return u_sat;
}
