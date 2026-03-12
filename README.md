# STM32L432KC LED Controller

A simulated firmware project for the STM32L432KC Nucleo-32 board.
Structured as professional embedded firmware with separate drivers.

## Target Hardware
- STM32L432KC Nucleo-32
- Onboard LED: PB3
- UART: 115200 baud

## Project Structure
```
stm32l432-led-controller/
├── src/
│   ├── main.c      # Application entry point
│   ├── gpio.c      # GPIO driver implementation
│   └── uart.c      # UART driver implementation
├── inc/
│   ├── gpio.h      # GPIO driver interface
│   └── uart.h      # UART driver interface
├── Makefile        # Build system
└── README.md       # Project documentation
```

## How To Build
```bash
make
```

## How To Run
```bash
./led-controller
```

## UART Commands
| Command | Action |
|---------|--------|
| A | LED ON |
| B | LED OFF |
| C | LED TOGGLE |
| D | Fast blink |
| E | Slow blink |
| Q | Quit |

## Skills Demonstrated
- C driver architecture (header/source separation)
- GPIO abstraction layer
- UART communication simulation
- Makefile build system
- Git version control