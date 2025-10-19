#include "push_button.h"
#include <avr/io.h>
#include <util/delay.h>

// initializes push button >> input and enalbe the pull-up.
void Button_Init(void)
{    BUTTON_DDR &= ~(1 << BUTTON_PIN);     
    BUTTON_PORT |= (1 << BUTTON_PIN);     
}

// reads button_state and returns 1 if released else return 0 {Pressed}
uint8_t Button_Read(void)
{
    uint8_t button_state = (BUTTON_PINREG & (1 << BUTTON_PIN)) ? 1 : 0;

    if (button_state == 0)
    {
        _delay_ms(20); 
        button_state = (BUTTON_PINREG & (1 << BUTTON_PIN)) ? 1 : 0;
    }

    return button_state;
}
