/**
  ******************************************************************************
  * @file    menu.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Simple LCD menu.
  *
  ******************************************************************************
  */
#ifndef INC_MENU_H_
#define INC_MENU_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Typedef -------------------------------------------------------------------*/
typedef struct _MenuItem MenuItem_TypeDef;

struct _MenuItem {
  char display_str[LCD_LINE_BUF_LEN];
  uint16_t display_strlen;
  MenuItem_TypeDef* next;
  MenuItem_TypeDef* prev;
  MenuItem_TypeDef* child;
  MenuItem_TypeDef* parent;
  void (*menu_function)(MenuItem_TypeDef*);
};

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void MENU_ClearDisplayBuffer(MenuItem_TypeDef* hmenuitem);
void MENU_CallFunction(MenuItem_TypeDef* hmenuitem);

#endif /* INC_MENU_H_ */
