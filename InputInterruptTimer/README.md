# Input Interrupt + 5-Second Timer (Bare-Metal STM32)

## Overview

This project demonstrates how to use an external interrupt (EXTI) together with a hardware timer (TIM2) on an STM32F4 microcontroller using pure bare-metal register programming (no HAL).

Goal:

- Trigger an interrupt when the onboard user button is pressed
- Turn the onboard LED ON immediately
- Keep the LED ON for 5 seconds
- Automatically turn the LED OFF using a hardware timer interrupt

This project is fully interrupt-driven — no polling loops and no software delay functions.

---

## Hardware & Environment

Board: STM32 Nucleo-F446RE  
MCU: STM32F4 (ARM Cortex-M4)  
Clock: 16 MHz (HSI)  
Language: C (bare-metal, CMSIS only)  
IDE: STM32CubeIDE  

---

## Project Structure

InputInterruptTimer/
│
├── main.c
├── exti.c
├── exti.h
├── tim.c
├── tim.h

### main.c
- Initializes GPIO
- Configures EXTI for the user button
- Configures TIM2
- Enables NVIC interrupts
- Runs minimal main loop (interrupt-driven design)

### exti.c / exti.h
- Configures the button pin as an external interrupt
- Maps GPIO to EXTI line via SYSCFG
- Enables rising-edge trigger
- Clears pending interrupt flags
- Starts the timer when the button interrupt fires

### tim.c / tim.h
- Configures TIM2 using prescaler and auto-reload register
- Generates a 5-second duration
- Turns the LED off inside the timer interrupt handler
- Stops the timer after completion

---

## How It Works

1. Button Press (EXTI Interrupt)
   - User presses onboard button
   - EXTI interrupt fires
   - LED turns ON
   - TIM2 starts counting

2. Timer Expiration (TIM2 Interrupt)
   - TIM2 reaches ARR value
   - Timer update interrupt fires
   - LED turns OFF
   - Timer stops

Everything is handled using hardware interrupts.

---

## Timer Math

Timer frequency is determined by:

Timer Frequency = Timer Clock / (PSC + 1)

Duration = (ARR + 1) / Timer Frequency

Prescaler (PSC) slows down the timer clock.  
Auto-Reload Register (ARR) determines how long the timer counts before overflow.

TIM2 is configured to produce a 5-second interval.

---

## Concepts Demonstrated

- RCC peripheral clock enabling
- GPIO input and output configuration
- SYSCFG configuration for EXTI mapping
- Rising-edge trigger configuration
- NVIC interrupt enabling
- TIM2 configuration (PSC, ARR, DIER, SR, CR1)
- Clean interrupt service routines
- Modular driver separation (EXTI + TIM)

---

## Why This Project Matters

This project demonstrates:

- Event-driven embedded design
- Coordinating multiple peripherals
- Hardware-based timing instead of software delays
- Interrupt-based firmware architecture

It builds foundational knowledge required for:

- Real-time systems
- Low-power firmware design
- RTOS development
- Professional embedded systems work

---

## Future Improvements

- Add button debouncing
- Generalize timer driver for reuse
- Support multiple concurrent timers
- Add UART logging for debugging
- Convert to non-blocking LED state machine

---

This project is part of my bare-metal STM32 firmware portfolio focused on mastering low-level ARM Cortex-M programming through direct register access.

