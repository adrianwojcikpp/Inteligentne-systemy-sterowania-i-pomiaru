/**
  ******************************************************************************
  * @file    menu_config.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Simple LCD menu configuration file. 
  *
  ******************************************************************************
  */
#ifndef INC_MENU_CONFIG_H_
#define INC_MENU_CONFIG_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "menu.h"
#include "bh1750_config.h"
#include "bmp280_config.h"

/* Typedef -------------------------------------------------------------------*/
typedef struct {
  float temp;
  float pres;
  float light;
} Measurements_TypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern MenuItem_TypeDef* menu_item;

extern MenuItem_TypeDef menu_light1;

extern MenuItem_TypeDef menu_temp1;

extern MenuItem_TypeDef menu_pres1;

extern Measurements_TypeDef measurements;

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_MENU_CONFIG_H_ */
