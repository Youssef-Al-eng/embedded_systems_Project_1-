#include "lcd.h"

// sends a short enable pulse to the lcd to latch data or commands
static void LCD_PulseEnable(void)
{
    PORTB |= (1 << LCD_EN);
    _delay_us(1);
    PORTB &= ~(1 << LCD_EN);
    _delay_us(100);
}

// sends a 4-bit half byte to the lcd data pins (used for command and data transfer)
static void LCD_SendHalfByte(uint8_t half)
{
    if (half & 0x10) PORTD |= (1 << LCD_D4); else PORTD &= ~(1 << LCD_D4);
    if (half & 0x20) PORTD |= (1 << LCD_D5); else PORTD &= ~(1 << LCD_D5);
    if (half & 0x40) PORTD |= (1 << LCD_D6); else PORTD &= ~(1 << LCD_D6);
    if (half & 0x80) PORTD |= (1 << LCD_D7); else PORTD &= ~(1 << LCD_D7);

    LCD_PulseEnable();
}

// sends a command byte to the lcd (like clear or set cursor)
void LCD_Command(uint8_t cmd)
{
    PORTB &= ~(1 << LCD_RS);
    LCD_SendHalfByte(cmd & 0xF0);
    LCD_SendHalfByte(cmd << 4);
    _delay_ms(2);
}

// displays a single character on the lcd
void LCD_Char(uint8_t data)
{
    PORTB |= (1 << LCD_RS);
    LCD_SendHalfByte(data & 0xF0);
    LCD_SendHalfByte(data << 4);
    _delay_ms(2);
}

// displays a full string starting from the current cursor position
void LCD_String(const char *str)
{
    while (*str)
        LCD_Char(*str++);
}

// clears all content on the lcd screen
void LCD_Clear(void)
{
    LCD_Command(0x01);
    _delay_ms(2);
}

// moves the lcd cursor to the given row and column
void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0 ? 0x00 : 0x40) + col;
    LCD_Command(0x80 | addr);
}

// initializes the lcd in 4-bit mode and sets display configuration
void LCD_Init(void)
{
    DDRB |= (1 << LCD_RS) | (1 << LCD_EN);
    DDRD |= (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);

    _delay_ms(20);

    LCD_Command(0x33);
    LCD_Command(0x32);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Clear();
}
