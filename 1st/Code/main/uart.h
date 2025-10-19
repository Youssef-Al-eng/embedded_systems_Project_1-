#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

void UART_Init(unsigned long baudrate);
void UART_TransmitChar(char data);
void UART_TransmitString(const char *str);
char UART_ReceiveChar(void);
uint8_t UART_DataAvailable(void);

#endif
