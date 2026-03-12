#include "gpio.h"
#include <stdio.h>

// Simulated GPIO state (replaces actual registers on STM32)
static uint8_t gpio_state[2][16] = {0}; // [port][pin]
static uint8_t gpio_direction[2][16] = {0};

// Get port index (GPIOA=0, GPIOB=1)
static int get_port_index(uint32_t port) {
    if (port == GPIOA) return 0;
    if (port == GPIOB) return 1;
    return -1;
}

// Initialize GPIO pin
void gpio_init(uint32_t port, uint8_t pin, uint8_t direction) {
    int idx = get_port_index(port);
    if (idx < 0) return;

    gpio_direction[idx][pin] = direction;
    gpio_state[idx][pin] = GPIO_LOW;

    printf("[GPIO] Port %s Pin %d initialized as %s\n",
           (port == GPIOA) ? "A" : "B",
           pin,
           (direction == GPIO_OUTPUT) ? "OUTPUT" : "INPUT");
}

// Write HIGH or LOW to pin
void gpio_write(uint32_t port, uint8_t pin, uint8_t state) {
    int idx = get_port_index(port);
    if (idx < 0) return;

    gpio_state[idx][pin] = state;

    printf("[GPIO] Port %s Pin %d set to %s\n",
           (port == GPIOA) ? "A" : "B",
           pin,
           (state == GPIO_HIGH) ? "HIGH" : "LOW");
}

// Toggle pin state
void gpio_toggle(uint32_t port, uint8_t pin) {
    int idx = get_port_index(port);
    if (idx < 0) return;

    gpio_state[idx][pin] = !gpio_state[idx][pin];

    printf("[GPIO] Port %s Pin %d toggled to %s\n",
           (port == GPIOA) ? "A" : "B",
           pin,
           (gpio_state[idx][pin] == GPIO_HIGH) ? "HIGH" : "LOW");
}

// Read pin state
uint8_t gpio_read(uint32_t port, uint8_t pin) {
    int idx = get_port_index(port);
    if (idx < 0) return 0;
    return gpio_state[idx][pin];
}