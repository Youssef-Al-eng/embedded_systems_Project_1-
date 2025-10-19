#include "gpio.h"

// sets a pin as input or output using a pointer to the ddr register 
void GPIO_PinMode(volatile uint8_t *ddr_reg, uint8_t pin_number, uint8_t pin_mode)
{
    if (pin_mode == OUTPUT)
        *ddr_reg |= (1 << pin_number);
    else
        *ddr_reg &= ~(1 << pin_number);
}

// writes high or low to a pin using a pointer to the port register
void GPIO_DigitalWrite(volatile uint8_t *output_port, uint8_t pin_number, uint8_t pin_value)
{
    if (pin_value)
        *output_port |= (1 << pin_number);
    else
        *output_port &= ~(1 << pin_number);
}

// reads pin state using a pointer to the pin register; returns 1 if high or 0 if low
uint8_t GPIO_DigitalRead(volatile uint8_t *pin_reg, uint8_t pin_number)
{
    if (*pin_reg & (1 << pin_number))
        return 1;
    else
        return 0;
}
