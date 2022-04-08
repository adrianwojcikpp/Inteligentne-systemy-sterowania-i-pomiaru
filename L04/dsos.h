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
  
/* Typedef -------------------------------------------------------------------*/
struct dsos {
	double a1, a2, b0, b1, b2;
	double u_prev[2];
	double y_prev[2];
};

/* Public function -----------------------------------------------------------*/
/**
 * @brief Initialization second order system
 * @param[out] sys    : Second order system structure
 * @param[in]  coeffs : Raw coefficients 
 */
 void dsos_init(struct dsos* sys, double* coeffs);
 
/**
 * @brief Single-step second order system simulation
 * @param[in/out] sys : Second order system structure
 * @param[in]     u   : Input signal sample
 * @return System response 
 */
double lsim_step(struct dsos* sys, double u);