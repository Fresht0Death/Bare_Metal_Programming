SysTick Delay — Bare-Metal STM32
Overview
Bare-metal implementation of a millisecond delay using the ARM Cortex-M SysTick timer on an STM32F4 MCU.
Built with direct register access to reinforce low-level timer fundamentals without HAL delay calls.
Stack
MCU: STM32F4 (Nucleo)
Clock: 16 MHz
Toolchain: STM32CubeIDE
Language: C (bare-metal, CMSIS)
What This Shows
SysTick configuration via LOAD, VAL, and CTRL
Polling COUNTFLAG for precise timing
Clean driver separation (systick.c / .h)
Integration into a real application loop
Foundational work for schedulers, RTOS ticks, and non-blocking timing.
API
void systickDelayMS(int delay);
Blocking delay in milliseconds.
Structure
├── main.c
├── systick.c
└── systick.h
Notes
Assumes 16 MHz system clock
Blocking by design
Intended for learning and timing primitives
Next Steps
Interrupt-driven SysTick
Non-blocking delays
Simple task scheduler
Author
Jahmai Cabrera
Embedded Systems / Firmware Engineering
