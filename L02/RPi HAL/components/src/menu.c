/**
  ******************************************************************************
  * @file    menu.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Simple LCD menu.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "menu.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
void MENU_ClearDisplayBuffer(MenuItem_TypeDef* hmenuitem)
{
  memset(hmenuitem->display_str, ' ', LCD_LINE_BUF_LEN);
  hmenuitem->display_str[LCD_LINE_BUF_LEN] = 0;
}

void MENU_CallFunction(MenuItem_TypeDef* hmenuitem)
{
  hmenuitem->menu_function(hmenuitem);
  hmenuitem->display_str[hmenuitem->display_strlen] = ' ';
}
