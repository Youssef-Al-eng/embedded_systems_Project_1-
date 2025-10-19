#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

/* 
 * initialzed uart and set the baud rate ,  set-up the transmitter, receiver and the  frame format.
 */
void UART_Init(unsigned long baudrate)
{
    uint16_t ubrr = (F_CPU / (16UL * baudrate)) - 1;
    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/* 
 * send a character through uart then >> wait when the buffer is ready 
 */
void UART_TransmitChar(char data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

/* 
 * sending string via UART and send the char sequentially until to the end
 */
void UART_TransmitString(const char *str)
{
    while (*str)
        UART_TransmitChar(*str++);
    _delay_ms(2);
}

/* 
 *  recieve a single character from the UART and blocks until data is available.
 */
char UART_ReceiveChar(void)
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

/*
 *check uart recieved then return 1 if data avilable else return 0
 */
uint8_t UART_DataAvailable(void)
{
    if (UCSR0A & (1 << RXC0))
        return 1;
    else
        return 0;
}
