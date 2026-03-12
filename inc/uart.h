#ifndef UART_H
#define UART_H

#include <stdint.h>

// STM32L432KC UART Settings
#define UART_BAUD_9600   9600
#define UART_BAUD_115200 115200

// UART Status
#define UART_OK    0
#define UART_ERROR 1

// UART Commands for LED control
#define CMD_LED_ON     'A'
#define CMD_LED_OFF    'B'
#define CMD_LED_TOGGLE 'C'
#define CMD_LED_FAST   'D'
#define CMD_LED_SLOW   'E'

// Function prototypes
uint8_t uart_init(uint32_t baudrate);
void    uart_send_char(char c);
void    uart_send_string(const char *str);
char    uart_receive_char(void);
void    uart_send_number(int number);

#endif // UART_H