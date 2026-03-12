# STM32L432KC LED Controller - Makefile
# Simulated build for Linux

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -I./inc

# Directories
SRC_DIR = src
INC_DIR = inc

# Source files
SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/gpio.c \
	   $(SRC_DIR)/uart.c

# Output binary
TARGET = led-controller

# Default target - builds everything
all: $(TARGET)

# Build rule
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	@echo "Build successful! Run with: ./led-controller"

# Clean build files
clean:
	rm -f $(TARGET)
	@echo "Cleaned build files"

# Rebuild from scratch
rebuild: clean all

# Show help
help:
	@echo "Available commands:"
	@echo "  make         - build project"
	@echo "  make clean   - remove binary"
	@echo "  make rebuild - clean and rebuild"