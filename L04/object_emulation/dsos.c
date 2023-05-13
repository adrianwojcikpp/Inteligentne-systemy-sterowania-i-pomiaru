/**
  ******************************************************************************
  * @file    dsos.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    08 Apr 2022 
  * @brief   Simple second order section implementation.
  *          Source file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "dsos.h"

/* Public function -----------------------------------------------------------*/
/**
 * @brief Initialization second order system
 * @param[out] sys    : Second order system structure
 * @param[in]  coeffs : Raw coefficients 
 */
 void DSOS_Init(DSOS_HandleTypeDef* sys, double* coeffs)
 {
	sys->a1 = coeffs[0]; 
	sys->a2 = coeffs[1];
	sys->b0 = coeffs[2]; 
	sys->b1 = coeffs[3]; 
	sys->b2 = coeffs[4];	 
 }

/**
 * @brief Single-step second order system simulation
 * @param[in/out] sys : Second order system structure
 * @param[in]     u   : Input signal sample
 * @return System response 
 */
double DSOS_GetOutput(DSOS_HandleTypeDef* sys, double u)
{
	double y = sys->a1*sys->y_prev[0] + sys->a2*sys->y_prev[1] + sys->b0*u + sys->b1*sys->u_prev[0] + sys->b2*sys->u_prev[1];
	sys->y_prev[1] = sys->y_prev[0];
	sys->y_prev[0] = y;
	sys->u_prev[1] = sys->u_prev[0];
	sys->u_prev[0] = u;
	return y;
}