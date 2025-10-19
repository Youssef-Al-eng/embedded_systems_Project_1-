#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include <stdint.h>

#define INPUT  0
#define OUTPUT 1

void GPIO_PinMode(volatile uint8_t *ddr_reg, uint8_t pin_number, uint8_t pin_mode);
void GPIO_DigitalWrite(volatile uint8_t *output_port, uint8_t pin_number, uint8_t pin_value);
uint8_t GPIO_DigitalRead(volatile uint8_t *pin_reg, uint8_t pin_number);

#endif
