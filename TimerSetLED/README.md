# STM32 Bare-Metal Timer (TIM) Driver with ADC and UART Integration

![Timer Testing and Deployment](testing_deployment1.gif)

## Overview

This project focuses on implementing a bare-metal **STM32 timer (TIM) driver** and integrating it into an application-level control flow. The timer module is the primary focus of this repository and is exercised directly from `main.c`.

ADC and UART are included to demonstrate how the timer logic fits into a real firmware workflow, but the core emphasis is on **timer configuration, control, and usage** using register-level programming.

No high-level abstraction libraries are used.

## Primary Focus Files

- `tim.c / tim.h`  
  Implements a reusable bare-metal TIM driver using direct register access.

- `main.c`  
  Demonstrates how the timer driver is initialized and used within the main application loop.

## Hardware

- STM32F4 series microcontroller (tested on STM32F446RE)
- UART connection via ST-Link virtual COM port or external adapter
- Optional analog input source (for ADC demonstration)

## Key Features

- Register-level TIM peripheral configuration
- Clean separation between driver code and application logic
- Hardware timer–based timing (not SysTick-driven)
- Practical integration of timers into a firmware control loop
- UART output for visibility and debugging
- ADC sampling to demonstrate timer-based workflows

## Project Structure


## How It Works

1. The TIM peripheral is configured in `tim.c` using direct register access.
2. The timer is initialized and controlled from `main.c`.
3. Timing events structure the main execution loop.
4. ADC reads and UART prints are performed within the timer-driven workflow.

The timer driver is written to be reusable across projects with minimal modification.

## Build and Flash

- Open the project in STM32CubeIDE
- Build the project
- Flash using ST-Link
- Observe behavior through a serial terminal via UART

## Learning Objectives

- Understand STM32 TIM peripheral registers and clocking
- Design reusable bare-metal drivers
- Use hardware timers for deterministic timing
- Integrate low-level drivers into a real firmware application

## Notes

This project prioritizes clarity and correctness over abstraction. The timer driver is intentionally explicit to expose how STM32 TIM peripherals operate at the register level.
