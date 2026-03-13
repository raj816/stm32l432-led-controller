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

// function to blink LED N times
void gpio_blink(uint16_t times){
    for (uint16_t i = 0; i < times; i++) {
        gpio_toggle(GPIOB, PIN_3);
        // Simulate delay (in real code, use a timer or delay function)
        printf("[GPIO] Blinking... (%d/%d)\n", i + 1, times);
    }
}

//function to simulate pwm by toggling pin with duty cycle
void gpio_pwm(uint32_t port, uint8_t pin, uint8_t duty_cycle) {
    if (duty_cycle > PWM_MAX) {
        printf("[GPIO] ERROR: Invalid duty cycle %d\n", duty_cycle);
        return;
    }
    printf("[GPIO] Simulating PWM on Port %s Pin %d with duty cycle %d%%\n",
           (port == GPIOA) ? "A" : "B",
           pin,
           duty_cycle);

    if(duty_cycle == PWM_MIN) {
        gpio_write(port, pin, GPIO_LOW);
        printf("[GPIO] PWM OFF (0%%)\n");
    } else if (duty_cycle == PWM_MAX) {
        gpio_write(port, pin, GPIO_HIGH);
        printf("[GPIO] PWM ON (100%%)\n");
    }  
      else if(duty_cycle <30){
        printf("[GPIO] PWM LOW (duty cycle < 30%%)\n");
      }
      else if(duty_cycle <70){
        printf("[GPIO] PWM MEDIUM (duty cycle 30%% - 70%%)\n");
      }
      else {
        printf("[GPIO] PWM HIGH (duty cycle > 70%%)\n");
      }
    }