#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define LCD_RS PB0
#define LCD_EN PB1
#define LCD_D4 PD4
#define LCD_D5 PD5
#define LCD_D6 PD6
#define LCD_D7 PD7

void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Char(uint8_t data);
void LCD_String(const char *str);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif
