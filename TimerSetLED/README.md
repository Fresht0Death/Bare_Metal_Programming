# STM32 Bare-Metal Timer (TIM) Driver with ADC and UART Integration

## Overview

This project focuses on implementing a bare-metal **STM32 timer (TIM) driver** and integrating it into an application-level control flow. The timer module is used as the core timing mechanism and is exercised directly from `main.c`.

ADC and UART are included to demonstrate how the timer logic fits into a real firmware workflow, but the primary emphasis is on **timer configuration, control, and usage**.

All peripherals are configured using register-level programming without high-level abstraction libraries.

## Primary Focus Files

- `tim.c / tim.h`  
  Implements a reusable bare-metal TIM driver, including timer initialization and timing utilities.

- `main.c`  
  Demonstrates how the timer module is initialized and used within the main application loop.

## Hardware

- STM32F4 series microcontroller (tested on STM32F446RE)
- UART connection via ST-Link virtual COM port or external adapter
- Optional analog input source (for ADC demonstration)
- Logic Analyzer (Used for testing)

## Key Features

- Register-level TIM peripheral configuration
- Reusable timer driver separated from application logic
- SysTick-independent timing via TIM peripheral
- Integration of TIM logic inside the main execution loop
- UART output for visibility and debugging
- ADC sampling to show timer-driven workflow

## Project Structure


## How It Works

1. TIM peripheral is configured in `tim.c` using direct register access.
2. The timer is initialized and controlled from `main.c`.
3. Timing events are used to structure application behavior.
4. ADC reads and UART prints are performed within the timing framework to demonstrate practical usage.

The timer module is designed to be reusable across projects with minimal modification.

## Build and Flash

- Open the project in STM32CubeIDE
- Build and flash using ST-Link
- Monitor UART output using a serial terminal

## Learning Objectives

- Understand STM32 TIM peripheral registers and clocking
- Design a clean separation between drivers and application code
- Use hardware timers for deterministic timing
- Integrate low-level drivers into a real firmware loop

## Notes

This project prioritizes clarity and correctness over abstraction. The timer driver is written explicitly to expose how STM32 TIM peripherals operate at the register level.
