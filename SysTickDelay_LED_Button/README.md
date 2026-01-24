# SysTick Delay — Bare-Metal STM32

## Overview
This project implements a millisecond delay using the ARM Cortex-M SysTick timer on an STM32F4 microcontroller. The code is written in bare-metal C using direct register access, without relying on HAL delay functions. The purpose of this project is to build a clear understanding of low-level timer configuration and usage. This is then show to work through using the onboard button to turn on the onboard LED for 5 seconds and off otherwise.

## Hardware and Tools
- MCU: STM32F4 series (tested on Nucleo board)
- System Clock: 16 MHz
- IDE / Toolchain: STM32CubeIDE
- Language: C (bare-metal, CMSIS)

## What This Project Demonstrates
- Manual configuration of the SysTick timer using LOAD, VAL, and CTRL registers
- Polling the COUNTFLAG bit to detect timer expiration
- Clean separation of timing logic using systick.c and systick.h
- Integration of a custom timing utility into a main application loop

This project provides a foundation for interrupt-driven timing, software timers, and RTOS tick scheduling.

## API
void systickDelayMS(int delay);

Provides a blocking delay in milliseconds.

## Project Structure
main.c  
systick.c  
systick.h  

## Design Notes
- Delay timing assumes a 16 MHz system clock
- The delay function is blocking by design
- Intended for learning and timing primitives rather than low-power or multitasking systems

## Future Improvements
- Interrupt-based SysTick implementation
- Non-blocking delay mechanism
- Support for variable system clock frequencies
- Simple cooperative scheduler built on SysTick

## Author
Jahmai Cabrera  
Embedded Systems / Firmware Engineering
