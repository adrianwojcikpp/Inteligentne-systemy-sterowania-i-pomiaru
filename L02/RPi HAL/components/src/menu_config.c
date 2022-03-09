/**
  ******************************************************************************
  * @file    menu_config.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    13 Jun 2021
  * @brief   Simple LCD menu configuration file. 
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "menu_config.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
MenuItem_TypeDef* menu_item;
Measurements_TypeDef measurements; 

/** MENU LIGHT SENSORS CODE BEGIN *******************************************************************************************/
void menu_light_sensors_fcn(MenuItem_TypeDef* hmenuitem, BH1750_HandleTypeDef* hsensor)
{
  measurements.light = BH1750_ReadLux(hsensor);
  hmenuitem->display_strlen = sprintf(hmenuitem->display_str, "L: %8.2f lx  ", measurements.light);
}

/* Digital light sensor #1: BH1750 (ADDR = 'L') */
void menu_light_sensor1_fcn(MenuItem_TypeDef* hmenuitem){ menu_light_sensors_fcn(hmenuitem, &light_sensor); }
MenuItem_TypeDef menu_light1 = {"L:     0.00 lx  ", 16, &menu_temp1, &menu_pres1, NULL, NULL, menu_light_sensor1_fcn};

/** MENU LIGHT SENSORS CODE END *********************************************************************************************/

/** MENU TEMPERATURE SENSORS CODE BEGIN **************************************************************************************/
void menu_temp_sensors_fcn(MenuItem_TypeDef* hmenuitem, struct bmp280_dev* hsensor)
{
  struct bmp280_uncomp_data bmp280_data;
  bmp280_get_uncomp_data(&bmp280_data, hsensor);
  int32_t temp;
  bmp280_get_comp_temp_32bit(&temp, bmp280_data.uncomp_temp, hsensor);
  measurements.temp = (float)temp / 100.0;
  hmenuitem->display_strlen = sprintf(hmenuitem->display_str, "T: %5d.%02d %cC  ", temp/100, temp%100, LCD_DEGREE_SIGN);
}

/* Digital temperature sensor #1: BMP280 */
void menu_temp_sensor1_fcn(MenuItem_TypeDef* hmenuitem){ menu_temp_sensors_fcn(hmenuitem, &temp_press_sensor); }
MenuItem_TypeDef menu_temp1 = {"T:     0.00  C", 16, &menu_pres1, &menu_light1, NULL, NULL, menu_temp_sensor1_fcn};

/** MENU TEMPERATURE SENSORS CODE END ****************************************************************************************/

/** MENU PRESSURE SENSORS CODE BEGIN *****************************************************************************************/
void menu_pres_sensors_fcn(MenuItem_TypeDef* hmenuitem, struct bmp280_dev* hsensor)
{
  struct bmp280_uncomp_data bmp280_data;
  bmp280_get_uncomp_data(&bmp280_data, hsensor);
  int32_t temp;
  bmp280_get_comp_temp_32bit(&temp, bmp280_data.uncomp_temp, hsensor); // 't_fine' coefficient used in 'bmp280_get_comp_pres_32bit'
  measurements.temp = (float)temp / 100.0;
  uint32_t pres;                                                       // is set up in 'bmp280_get_comp_temp_32bit'
  bmp280_get_comp_pres_32bit(&pres, bmp280_data.uncomp_press, hsensor);
  measurements.pres = (float)pres / 100.0;
  hmenuitem->display_strlen = sprintf(hmenuitem->display_str, "P: %5d.%02d hPa ", pres/100, pres%100);
}

/* Digital pressure sensor #1: BMP280 */
void menu_pres_sensor1_fcn(MenuItem_TypeDef* hmenuitem){ menu_pres_sensors_fcn(hmenuitem, &temp_press_sensor); }
MenuItem_TypeDef menu_pres1 = {"P:     0.00 hPa", 16, &menu_light1, &menu_temp1, NULL, NULL, menu_pres_sensor1_fcn};

/** MENU TEMPERATURE SENSORS CODE END *****************************************************************************************/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
