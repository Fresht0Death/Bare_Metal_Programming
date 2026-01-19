# Bare Metal Programming (STM32 + C)

![STM32 ADC Potentiometer Project](./potentiometerADC/IMG_3204.jpeg)

This repository documents my progression through **bare-metal C programming on STM32**, focusing on understanding microcontrollers at the register level rather than relying on heavy abstractions.

I am following a **Udemy bare-metal embedded C course** using an STM32 Nucleo board. My workflow is deliberate and structured to ensure real understanding—not just copying code.

---

## ⭐ Highlighted Project (Independent Work)

### STM32 ADC Potentiometer Reader
Located in: `potentiometerADC/`

This is the **first project I built independently** without following a tutorial line-by-line.

It demonstrates:
- ADC configuration
- Analog signal sampling
- UART output for real-time debugging
- End-to-end understanding of analog → digital conversion

This project is pinned because it represents the transition from *learning* to *building*.

---

## Repository Structure & Workflow

### 📁 LearningVideoCode
Code written while following along with the Udemy course videos.

- Used to learn new peripherals and concepts
- Code may resemble instructor examples
- Focus is on understanding system behavior

---

### 📁 Learning Projects (Rewritten From Memory)
After completing a module, I re-implement the project **from memory** a few days later.

Rules I follow:
- No copying from the course
- Minimal reference to documentation
- Full recall of peripheral setup and logic

These projects reflect **retained knowledge**, not guided repetition.

---

### 📁 Standalone Projects
Projects written independently using learned concepts.

- `potentiometerADC` (pinned)
- Focus on correctness, clarity, and low-level understanding

---

## Hardware & Tools

- **Board:** STM32 Nucleo (STM32F4 family)
- **Language:** C
- **IDE:** STM32CubeIDE
- **Debugging:** UART serial output
- **Approach:** Bare-metal / register-level where possible

---

## Why Bare Metal?

The goal is to deeply understand:
- Memory-mapped registers
- Peripheral initialization
- ADCs, UART, GPIO, and clocks
- What actually happens between C code and hardware

This repository is a **learning log and proof of skill**, not a polished product dump.

---

## Author

**Jahmai Cabrera**  
Computer Science Student  
Embedded Systems / Firmware Focus  

This repo reflects long-term skill development and disciplined embedded practice.

