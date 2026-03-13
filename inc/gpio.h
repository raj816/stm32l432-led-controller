#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// STM32L432KC GPIO Ports from the datasheet
#define GPIOA 0x48000000
#define GPIOB 0x48000400

// GPIO Pins
#define PIN_0  0
#define PIN_1  1
#define PIN_2  2
#define PIN_3  3  // PB3 - Onboard led on STM32L432KC

// GPIO States
#define GPIO_HIGH 1
#define GPIO_LOW  0

// GPIO Direction
#define GPIO_OUTPUT 1
#define GPIO_INPUT  0

// PWM setiings for blinking
#define PWM_MIN 0 // 0% duty cycle
#define PWM_MAX 100 // 100% duty cycle

//PWM Function prototypes
void gpio_pwm(uint32_t port, uint8_t pin, uint8_t duty_cycle);

// Function prototypes
void gpio_init(uint32_t port, uint8_t pin, uint8_t direction);
void gpio_write(uint32_t port, uint8_t pin, uint8_t state);
void gpio_toggle(uint32_t port, uint8_t pin);
uint8_t gpio_read(uint32_t port, uint8_t pin);
void gpio_blink(uint16_t times);
#endif // GPIO_H
