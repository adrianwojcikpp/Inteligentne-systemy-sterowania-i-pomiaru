/**
  ******************************************************************************
  * @file    lcd.h
  * @author  Olivier Van den Eede [ https://github.com/4ilo/HD44780-Stm32HAL ]
  * @author  AW (adjustments for Raspberry Pi.)
  * @version V2.0
  * @date    24-Apr-2021
  * @brief   Simple HD44780 driver library for Raspberry Pi.
  *          NOTE!: This code provides only WRITE features, no READ features.
  *
  ******************************************************************************
  */
#ifndef INC_LCD_H_
#define INC_LCD_H_

/* Config --------------------------------------------------------------------*/
#define LCD_PRINTF_ENABLE

// #define LCD20xN 		// For 20xN LCDs
#define LCD16xN			// For 16xN LCDs

#ifdef LCD16xN
#define LCD_LINE_BUF_LEN 16
#else
#define LCD_LINE_BUF_LEN 20
#endif

/* Includes ------------------------------------------------------------------*/
#include "rpi_hal_gpio.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#ifdef LCD_PRINTF_ENABLE
#include <stdarg.h>
#endif

/* Typedef -------------------------------------------------------------------*/
#define LCD_PinType int

typedef enum {
	LCD_4_BIT_MODE,
	LCD_8_BIT_MODE
} LCD_ModeTypeDef;

typedef struct {
	LCD_PinType* DATA_Pins;
	LCD_PinType  RS_Pin;
	LCD_PinType  E_Pin;
	LCD_ModeTypeDef Mode;
	_Bool IsInitialized;
} LCD_HandleTypeDef;

/* Define --------------------------------------------------------------------*/
#define LCD_CLEAR_DISPLAY 0x01

#define LCD_RETURN_HOME 0x02

#define LCD_ENTRY_MODE_SET 0x04
#define LCD_OPT_S   0x01				// Shift entire display to right
#define LCD_OPT_INC 0x02			 	// Cursor increment

#define LCD_DISPLAY_ON_OFF_CONTROL 0x08
#define LCD_OPT_D  0x04					// Turn on display
#define LCD_OPT_C  0x02					// Turn on cursor
#define LCD_OPT_B  0x01					// Turn on cursor blink

#define LCD_CURSOR_DISPLAY_SHIFT 0x10	// Move and shift cursor
#define LCD_OPT_SC 0x08
#define LCD_OPT_RL 0x04

#define LCD_FUNCTION_SET    0x20
#define LCD_OPT_DL          0x10		// Set interface data length
#define LCD_OPT_N           0x08		// Set number of display lines
#define LCD_OPT_F           0x04		// Set alternate font
#define LCD_SETCGRAM_ADDR  0x040
#define LCD_SET_DDRAM_ADDR  0x80	    // Set DDRAM address

#define LCD_NIB  4
#define LCD_BYTE 8

#define LCD_DATA_REG    1
#define LCD_COMMAND_REG 0

/** LCD Special characters ****************************************************/
#define LCD_DEGREE_SIGN 223

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief LCD initialization procedure.
 * @note Cursor off, Cursor increment on, No blink @see HD44780 technical note.
 * @param[in] hlcd LCD handler
 * @return None 
 */
void LCD_Init(LCD_HandleTypeDef* hlcd);

/**
 * @brief Write a decimal number on the current position.
 * @param[in] hlcd   LCD handler
 * @param[in] number Decimal number, max. 10 digits
 * @return None 
 */
void LCD_printInt(LCD_HandleTypeDef* hlcd, int number);

/**
 * @brief Write a hexadecimal number on the current position.
 * @param[in] hlcd   LCD handler
 * @param[in] number Hexadecimal number, max. 10 digits
 * @return None 
 */
void LCD_printHex(LCD_HandleTypeDef* hlcd, int number);

/**
 * @brief Write a character array on the current position.
 * @param[in] hlcd : LCD handler
 * @param[in] array : Character array 
 * @param[in] len : Character array length
 * @return None 
 */
void LCD_printArray(LCD_HandleTypeDef* hlcd, char* array, uint8_t len);

/**
 * @brief Write a string on the current position.
 * @param[in] hlcd LCD handler
 * @param[in] str  Null-terminated string
 * @return None 
 */
void LCD_printStr(LCD_HandleTypeDef* hlcd, char* str);

/**
 * @brief Set the cursor position.
 * @param[in] hlcd LCD handler
 * @param[in] row  Display row (line): 0 to N
 * @param[in] col  Display column: 0 to 15 (16 character display) or 19 (20 character display)
 * @return None 
 */
void LCD_SetCursor(LCD_HandleTypeDef* hlcd, uint8_t row, uint8_t col);

/**
 * @brief Clear the screen.
 * @param[in] hlcd LCD handler
 * @return None 
 */
void LCD_Clear(LCD_HandleTypeDef * lcd);

/**
 * @brief Clear the screen.
 * @param[in] hlcd   LCD handler
 * @param[in] code   Defined character code in display memory @see HD44780 technical note.
 * @param[in] bitmap Defined character array @see HD44780 technical note.
 * @return None 
 */
void LCD_DefineChar(LCD_HandleTypeDef* lcd, uint8_t code, uint8_t bitmap[]);

#ifdef LCD_PRINTF_ENABLE
/**
 * @brief Write text in standard format on the current position.
 * @param[in] hlcd   LCD handler
 * @param[in] format Text format @see http://www.cplusplus.com/reference/cstdio/printf/
 * @param[in] ...    Variadic arguments
 * @return None
 */
void LCD_printf(LCD_HandleTypeDef * lcd, const char* format, ...);
#endif

#endif /* INC_LCD_H_ */
