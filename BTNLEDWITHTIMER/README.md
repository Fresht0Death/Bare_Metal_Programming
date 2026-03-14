# STM32 Button Timer LED Prototype

## Overview

This project is a **prototype** built on the **STM32F446RE** using **bare-metal register-level programming** in C.

The goal of this prototype was to practice building a small embedded system from scratch by separating functionality into modules for:

- **Button input**
- **LED output**
- **Timer-based delay behavior**

When the button is pressed, the LED is turned on and a timer begins counting. After the timer reaches its update event, the LED is turned off.

This project is mainly meant as a **learning and architecture prototype**, not a polished final implementation.

---

## Prototype Status

**Important:** this project is still a **prototype**.

That means:

- The code was written as a learning exercise
- The structure is intentional, but some implementation details are still being refined
- Logic, timing behavior, naming, and debounce handling may still change
- This is not yet intended to be treated as production-ready embedded code

The point of this build was to strengthen my understanding of:

- GPIO input configuration
- GPIO output configuration
- Timer initialization and update events
- Register-level STM32 programming
- Organizing embedded code into multiple `.c` and `.h` files

---

## Features

- Bare-metal STM32 development
- GPIO output control for LED
- GPIO input reading for button
- TIM2-based timing logic
- Modular code split across multiple source files
- External button hardware using resistor/capacitor debounce

---

## Project Structure

```bash
.
├── main.c
├── button.c
├── button.h
├── led.c
├── led.h
├── tim.c
├── tim.h
├── syscalls.c
└── sysmem.c
