#include "uart.h"
#include <stdio.h>
#include <string.h>

// Simulated UART state
static uint32_t uart_baudrate = 0;
static uint8_t  uart_initialized = 0;

// Initialize UART
uint8_t uart_init(uint32_t baudrate) {
    if (baudrate != UART_BAUD_9600 && 
        baudrate != UART_BAUD_115200) {
        printf("[UART] ERROR: Invalid baudrate %d\n", baudrate);
        return UART_ERROR;
    }

    uart_baudrate = baudrate;
    uart_initialized = 1;

    printf("[UART] Initialized at %d baud\n", baudrate);
    return UART_OK;
}

// Send single character
void uart_send_char(char c) {
    if (!uart_initialized) {
        printf("[UART] ERROR: Not initialized!\n");
        return;
    }
    printf("[UART TX] %c\n", c);
}

// Send string
void uart_send_string(const char *str) {
    if (!uart_initialized) {
        printf("[UART] ERROR: Not initialized!\n");
        return;
    }
    printf("[UART TX] %s\n", str);
}

// Receive single character
char uart_receive_char(void) {
    if (!uart_initialized) {
        printf("[UART] ERROR: Not initialized!\n");
        return 0;
    }
    char c;
    printf("[UART RX] Waiting for command: ");
    scanf(" %c", &c);
    printf("[UART RX] Received: %c\n", c);
    return c;
}

// Send number as text
void uart_send_number(int number) {
    if (!uart_initialized) {
        printf("[UART] ERROR: Not initialized!\n");
        return;
    }
    printf("[UART TX] %d\n", number);
}