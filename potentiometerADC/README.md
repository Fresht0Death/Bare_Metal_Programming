# STM32 ADC Potentiometer Reader (UART Output)

This project demonstrates reading an analog signal from a potentiometer using the STM32 ADC and transmitting the converted value over UART for real-time monitoring. The goal is to build a solid understanding of ADC fundamentals on STM32 at a low level.

## Project Overview

- Reads analog voltage from a potentiometer using the ADC
- Converts the signal into a digital value
- Sends ADC data over UART to a serial terminal
- Continuously updates in real time

This project focuses on clarity and fundamentals rather than abstraction-heavy frameworks.

## Hardware Used

- STM32 Nucleo board (STM32F4 family)
- Potentiometer
- Breadboard
- Jumper wires
- USB cable (power + UART via ST-LINK)

## Wiring

| Potentiometer Pin | STM32 Connection |
|-------------------|------------------|
| VCC               | 3.3V             |
| GND               | GND              |
| Wiper (middle)    | ADC input pin (e.g., PA0) |

⚠️ **Important:** Do not use 5V. STM32 ADC pins are not 5V tolerant.

## Software Structure

- `main.c`  
  Initializes peripherals and runs the main loop

- `adc.c / adc.h`  
  Handles ADC configuration and analog-to-digital conversion

- `uart.c / uart.h`  
  Handles UART initialization and serial transmission

- `syscalls.c / sysmem.c`  
  Required for `printf` support in STM32CubeIDE

## Program Flow

1. System clock initialization
2. UART initialization
3. ADC initialization
4. Main loop:
   - Read ADC value
   - Transmit value over UART
   - Optional delay for readability

## Example UART Output



(Optionally converted to voltage if implemented.)

## How to Run

1. Open the project in **STM32CubeIDE**
2. Build and flash the code to the board
3. Open a serial terminal (e.g., PuTTY, Tera Term, minicom)
4. Use the following UART settings:
   - Baud rate: 115200
   - Data bits: 8
   - Stop bits: 1
   - Parity: None
5. Rotate the potentiometer and observe the output

## Learning Objectives

- Understand STM32 ADC resolution and scaling
- Learn how analog voltage maps to digital values
- Practice UART-based debugging
- Reinforce embedded system fundamentals

If you can explain why the ADC value changes as the potentiometer turns, you understand the core concept.

## Future Improvements

- Convert ADC values to actual voltage readings
- Use ADC interrupts or DMA
- Add moving average or digital filtering
- Display values on an LCD or TFT
- Implement threshold-based actions

## Author

Jahmai Cabrera  
Computer Science Student | Embedded & Firmware Systems

