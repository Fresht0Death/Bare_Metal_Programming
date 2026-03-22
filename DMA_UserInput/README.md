# UART Echo with DMA Transmission on STM32F4

This project uses the **STM32F4** to receive user input over **UART2**, store the characters in a buffer, and then transmit the completed message back using **DMA1 Stream 6**. The input session ends when the user types `\q`.

The project was built as a hands-on exercise to better understand how **UART**, **DMA**, **interrupts**, and **register-level peripheral configuration** work together on an STM32 microcontroller.

---

## What This Project Does

- Initializes **UART2** for transmit and receive
- Prompts the user through a serial terminal
- Reads user input one character at a time
- Stops collecting input when the sequence `\q` is entered
- Replaces `\q` with a newline
- Uses **DMA1 Stream 6** to send the message back through UART2
- Toggles the onboard LED when the DMA transfer completes

---

## Features

- Register-level UART configuration
- UART receive polling
- DMA memory-to-peripheral transfer
- DMA transfer complete interrupt
- Basic serial user interaction
- LED callback on DMA completion

---

## Hardware / Platform

- **MCU:** STM32F4
- **Board:** Nucleo / STM32F4 development board
- **UART Used:** USART2
- **TX Pin:** PA2
- **RX Pin:** PA3
- **LED Pin:** PA5

---

## Concepts Practiced

This project helped reinforce several core embedded systems concepts:

- Configuring GPIO pins for alternate function mode
- Setting up UART baud rate manually
- Using polling for UART RX
- Configuring DMA for memory-to-peripheral transfers
- Selecting the correct DMA stream and channel for USART2 TX
- Enabling DMA interrupts through the NVIC
- Handling transfer complete events with an interrupt service routine
- Combining peripherals so the CPU does less work during transmission

---

## Program Flow

1. GPIOA clock is enabled
2. PA5 is configured as an output for the LED
3. UART2 is initialized for TX/RX
4. The MCU prompts the user through the serial terminal
5. Characters are received one at a time over UART
6. Input continues until `\q` is detected
7. The ending `\q` is replaced with `\r\n`
8. DMA1 Stream 6 is configured for UART2 transmission
9. The message buffer is sent to `USART2->DR` using DMA
10. When the transfer completes, the DMA interrupt fires and the LED toggles

---

## Example Serial Interaction

```text
What would you like to print!
Type \q when you are done inputting your word

H
e
l
l
o
\q

Transmitted Result:

Hello
