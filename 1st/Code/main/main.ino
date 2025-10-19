#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <ctype.h>
#include "uart.h"
#include "led.h"
#include "push_button.h"
#include "lcd.h"  

static uint8_t lastButtonState = 1;

// for checking converts all letters in string to lowercase to avoid test case errors
void toLowerString(char *str)
{
    for(uint8_t i=0; str[i]; i++)
        str[i] = (char)tolower((unsigned char)str[i]);
}

// sends "ready" message to show system is initialized and ready to stert 
void sendReadySignal(void)
{
    UART_TransmitString("READY\r\n");
}
// initializes all peripherals and shows welcome message on lcd
void setup(void)
{
    UART_Init(9600);
    LED_Init();
    Button_Init();
    LCD_Init();

    LCD_SetCursor(0,0);
    LCD_String("1  2  3");
    _delay_ms(2000);
    LCD_SetCursor(2,1);
    LCD_String("welcome @ tkh");
    _delay_ms(2000);
    LCD_Clear();

    sendReadySignal();  
}

void loop(void)
{
    uint8_t buttonState = Button_Read();
    // detects changing in button state
    if (buttonState != lastButtonState)
    {
        if (buttonState == 0)
        {
            UART_TransmitString("BUTTON_PRESSED\r\n");
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_String("3");
        }
        else
        {
            UART_TransmitString("BUTTON_RELEASED\r\n");
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_String("4");
        }
        lastButtonState = buttonState;
    }

    
    if (UART_DataAvailable())
    {
        char buffer[20] = {0};
        uint8_t i = 0;
        _delay_ms(2);

        // reads uart input until newline or space
        while (UART_DataAvailable() && i < sizeof(buffer) - 1)
        {
            char c = UART_ReceiveChar();
            if (c == '\r' || c == '\n' || c == ' ')
                continue;
            buffer[i++] = c;
        }
        buffer[i] = '\0';
        toLowerString(buffer);

        // processes received commands
        if (i > 0)
        {
            if (strcmp(buffer, "on") == 0)
            {
                LED_On();
                UART_TransmitString("led turned on\r\n");
                LCD_Clear();
                LCD_SetCursor(0,0);
                LCD_String("1");
            }
            else if (strcmp(buffer, "of") == 0)
            {
                LED_Off();
                UART_TransmitString("led turned off\r\n");
                LCD_Clear();
                LCD_SetCursor(0,0);
                LCD_String("2");
            }
            else
            {
                UART_TransmitString("invalid command\r\n");
                LCD_Clear();
                LCD_SetCursor(0,0);
                LCD_String("invalid");
            }
        }

        // clears extra data from uart buffer
        while (UART_DataAvailable())
            (void)UART_ReceiveChar();
    }

    _delay_ms(50);
}

int main(void)
{
    setup(); 
    while (1)
    {
        loop();  
    }
}
