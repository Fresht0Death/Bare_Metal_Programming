# Bare Metal Programming (STM32 + C)

This repository documents my progression through **bare-metal C programming on STM32**, with an emphasis on understanding microcontrollers at the register level rather than relying on high-level abstractions.

I am following a **Udemy bare-metal embedded C course** using an STM32 Nucleo board, with a structured workflow designed to ensure real understanding—not copy-paste familiarity.

---

## Highlighted Project (Independent Work)

### STM32 Timer (TIM) Driver and Integration
Located in: `TimerSetLED/`

![TIM Driver Test and Deployment](./TimerSetLED/testing_deployment1.gif)

This project focuses on implementing and integrating a **bare-metal STM32 TIM peripheral driver**.  
The core logic lives in `tim.c`, `tim.h`, and `main.c`.

It demonstrates:
- Register-level TIM configuration
- Hardware timer–based timing (not SysTick-driven)
- Clean separation between driver code and application logic
- Practical integration of a reusable timer driver inside `main.c`
- UART output for runtime visibility
- ADC usage to demonstrate timer-driven workflows

This project represents a transition from peripheral demos to **driver-style firmware design**.

---

## Independent Timing Project

### SysTick Delay (Bare-Metal)
Located in: `SysTickDelay_LED_Button/`

This project implements a **millisecond delay using the ARM Cortex-M SysTick timer** with direct register access.  
No HAL delay utilities are used.

It demonstrates:
- Manual configuration of SysTick `LOAD`, `VAL`, and `CTRL` registers
- Polling the `COUNTFLAG` bit for precise timing
- A blocking millisecond delay API (`systickDelayMS`)
- Clean separation of timing logic (`systick.c / systick.h`)
- Integration with application logic using the onboard button and LED

The onboard button triggers the LED to turn on for **5 seconds**, validating correct SysTick timing behavior.

This project serves as a foundation for understanding **interrupt-driven timing, RTOS ticks, and software timers**.

---

## Previously Highlighted Project (Independent Work)

### STM32 ADC Potentiometer Reader
Located in: `potentiometerADC/`

![STM32 ADC Potentiometer Project](./potentiometerADC/IMG_3204.jpeg)

This was the **first project built independently** without following a tutorial line-by-line.

It demonstrates:
- ADC configuration
- Analog signal sampling
- UART output for real-time debugging
- End-to-end understanding of analog → digital conversion

This project is pinned because it marks the transition from *learning* to *building*.

---

## Repository Structure & Workflow

### LearningVideoCode
Code written while following along with Udemy course videos.

- Used to learn new peripherals and concepts
- Code may resemble instructor examples
- Focus is on understanding system behavior

---

### Learning Projects (Rewritten From Memory)
After completing a module, I re-implement the project **from memory** a few days later.

Rules I follow:
- No copying from the course
- Minimal reference to documentation
- Full recall of peripheral setup and logic

These projects reflect **retained knowledge**, not guided repetition.

---

### Standalone / Independent Projects
Projects written independently using learned concepts.

- `TimerSetLED`
- `SysTickDelay_LED_Button`
- `potentiometerADC`

These emphasize correctness, clarity, and low-level understanding.

---

## Hardware & Tools

- **Board:** STM32 Nucleo (STM32F4 family)
- **Language:** C (bare-metal, CMSIS)
- **IDE:** STM32CubeIDE
- **Debugging:** UART serial output
- **Approach:** Bare-metal / register-level where possible

---

## Why Bare Metal?

The goal is to deeply understand:
- Memory-mapped registers
- Peripheral initialization
- Timers, SysTick, ADCs, UART, GPIO, and clocks
- What actually happens between C code and hardware

This repository is a **learning log and proof of skill**, not a polished product dump.

---

## Author

**Jahmai Cabrera**  
Computer Science Student  
Embedded Systems / Firmware Focus  

This repository reflects long-term skill development and disciplined embedded systems practice.

