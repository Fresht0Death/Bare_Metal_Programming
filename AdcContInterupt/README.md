# STM32 ADC Interrupt Sensor Reader

## Overview

This project demonstrates how to configure the **ADC peripheral on the STM32F4** to continuously sample an analog signal using an **interrupt-driven architecture** instead of polling.

An analog input connected to **PA1 (ADC Channel 1)** is continuously converted.  
Each completed conversion triggers an interrupt, where the ADC value is read and transmitted via UART.

This reflects how real embedded systems handle sensor input efficiently without blocking execution.

---

## Features

- Analog input configured on **PA1**
- Continuous ADC conversion mode
- Interrupt-based data handling (no polling)
- UART output using `printf`
- NVIC interrupt configuration
- Modular driver-style structure

---

## Hardware Used

- STM32F4 MCU
- Analog signal source connected to **PA1**
- UART2 for serial output

---

## Project Structure

| File        | Description |
|-------------|------------|
| `main.c`    | Entry point and ADC interrupt handler |
| `adc.c`     | ADC configuration |
| `adc.h`     | ADC interface |
| `uart.c`    | UART setup |
| `uart.h`    | UART interface |
| `syscalls.c` | Enables `printf` |
| `sysmem.c`   | Memory support |

---

## How It Works

### ADC Setup

PA1 is configured in analog mode and ADC1 is initialized to read from Channel 1.

End-of-conversion interrupts are enabled:

```c
ADC1->CR1 |= CR1_EOCI;
NVIC_EnableIRQ(ADC_IRQn);
