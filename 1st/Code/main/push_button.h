#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

#include <stdint.h>

#define BUTTON_PORT   PORTB
#define BUTTON_DDR    DDRB
#define BUTTON_PIN    PB1
#define BUTTON_PINREG PINB  

void Button_Init(void);
uint8_t Button_Read(void);

#endif
