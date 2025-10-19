#include "led.h"

// make led pin >> Output and start in state off
void LED_Init(void)
{
    GPIO_PinMode(&LED_DDR, LED_PIN, OUTPUT);
    LED_Off();
}

// led turn on 
void LED_On(void)
{
    GPIO_DigitalWrite(&LED_PORT, LED_PIN, 1);
}

// led turn off
void LED_Off(void)
{
    GPIO_DigitalWrite(&LED_PORT, LED_PIN, 0);
}
