/**
  ******************************************************************************
  * @file    dsos.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    08 Apr 2022 
  * @brief   Simple second order section implementation.
  *          header file.
  *
  ******************************************************************************
  */
  
#ifndef __DSOS_H__
#define __DSOS_H__

/* Typedef -------------------------------------------------------------------*/
typedef struct {
	double a1, a2, b0, b1, b2;
	double u_prev[2];
	double y_prev[2];
} DSOS_HandleTypeDef;

/* Public function -----------------------------------------------------------*/
/**
 * @brief Initialization second order system
 * 
 * @param[out] sys    : Second order system structure
 * @param[in]  coeffs : Raw coefficients 
 */
 void DSOS_Init(DSOS_HandleTypeDef* sys, double* coeffs);
 
/**
 * @brief Single-step second order system simulation
 * 
 * @param[inout] sys : Second order system structure
 * @param[in]    u  : Input signal sample
 * @retval System response
 */
double DSOS_GetOutput(DSOS_HandleTypeDef* sys, double u);

#endif // __DSOS_H__