#include <stdio.h>
#include <unistd.h>
#include "gpio.h"
#include "uart.h"

// Blink delay in microseconds
#define BLINK_FAST 200000   // 0.2 seconds
#define BLINK_SLOW 1000000  // 1 second

// Current blink speed
static int blink_delay = BLINK_SLOW;
static int led_running = 1;

// Print welcome message
void print_banner(void) {
    printf("\n");
    printf("================================\n");
    printf("  STM32L432KC LED Controller\n");
    printf("  Target: PB3 Onboard LED\n");
    printf("  UART:   115200 baud\n");
    printf("================================\n");
    printf("Commands:\n");
    printf("  A - LED ON\n");
    printf("  B - LED OFF\n");
    printf("  C - LED TOGGLE\n");
    printf("  D - FAST blink\n");
    printf("  E - SLOW blink\n");
    printf("  Q - QUIT\n");
    printf("================================\n\n");
}

// Initialize all hardware
void system_init(void) {
    printf("[SYSTEM] Initializing STM32L432KC...\n");

    // Initialize UART at 115200 baud
    uart_init(UART_BAUD_115200);

    // Initialize PB3 as output (onboard LED)
    gpio_init(GPIOB, PIN_3, GPIO_OUTPUT);

    printf("[SYSTEM] Initialization complete!\n\n");
}

int main(void) {
    // Initialize system
    system_init();

    // Print banner
    print_banner();

    // Main application loop
    while (led_running) {
        char cmd = uart_receive_char();

        switch (cmd) {
            case CMD_LED_ON:
                gpio_write(GPIOB, PIN_3, GPIO_HIGH);
                uart_send_string("LED is ON");
                break;

            case CMD_LED_OFF:
                gpio_write(GPIOB, PIN_3, GPIO_LOW);
                uart_send_string("LED is OFF");
                break;

            case CMD_LED_TOGGLE:
                gpio_toggle(GPIOB, PIN_3);
                uart_send_string("LED toggled");
                break;

            case CMD_LED_FAST:
                blink_delay = BLINK_FAST;
                uart_send_string("Blink speed: FAST");
                for (int i = 0; i < 10; i++) {
                    gpio_toggle(GPIOB, PIN_3);
                    usleep(blink_delay);
                }
                break;

            case CMD_LED_SLOW:
                blink_delay = BLINK_SLOW;
                uart_send_string("Blink speed: SLOW");
                for (int i = 0; i < 4; i++) {
                    gpio_toggle(GPIOB, PIN_3);
                    usleep(blink_delay);
                }
                break;

            case 'Q':
                uart_send_string("Shutting down...");
                gpio_write(GPIOB, PIN_3, GPIO_LOW);
                led_running = 0;
                break;
            
            case 'F':
                gpio_blink(6);
                break;
            case 'P':
                uart_send_string("PWM Demo - LED brightness levels");
                gpio_pwm(GPIOB, PIN_3, 0);    // OFF
                usleep(500000);
                gpio_pwm(GPIOB, PIN_3, 25);   // DIM
                usleep(500000);
                gpio_pwm(GPIOB, PIN_3, 50);   // MEDIUM
                usleep(500000);
                gpio_pwm(GPIOB, PIN_3, 75);   // BRIGHT
                usleep(500000);
                gpio_pwm(GPIOB, PIN_3, 100);  // FULL
                break;
            default:
                uart_send_string("Unknown command!");
                break;
        }
    }

    printf("\n[SYSTEM] Goodbye!\n");
    return 0;
}