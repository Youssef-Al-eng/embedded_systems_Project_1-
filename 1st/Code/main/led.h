#ifndef LED_H_
#define LED_H_

#include "gpio.h"

#define LED_PORT PORTB
#define LED_DDR  DDRB
#define LED_PIN  PB0

void LED_Init(void);
void LED_On(void);
void LED_Off(void);

#endif
