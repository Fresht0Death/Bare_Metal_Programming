TM32 ADC + Potentiometer Input (UART Output)
This project demonstrates reading an analog signal from a potentiometer using the STM32 ADC and sending the converted value over UART for real-time monitoring. It’s a bare-bones embedded setup focused on fundamentals: ADC configuration, polling/conversion, and serial output.
What This Project Does
Reads a potentiometer voltage via ADC
Converts the analog voltage to a digital value
Sends the raw ADC reading (and/or voltage) over UART
Runs continuously for real-time feedback
This is intentionally simple and low-level to reinforce how ADCs actually work on STM32—not magic HAL abstractions.
Hardware Used
STM32 Nucleo board (STM32F4 family)
Potentiometer
Breadboard
Jumper wires
USB cable (power + UART via ST-LINK)
Wiring Overview
Potentiometer Pin	STM32
VCC	3.3V
GND	GND
Wiper (middle)	ADC input pin (e.g., PA0)
⚠️ Do not use 5V on the potentiometer. STM32 ADC pins are not 5V tolerant.
Software Overview
Core files:
main.c – System setup and main loop
adc.c / adc.h – ADC initialization and read logic
uart.c / uart.h – UART initialization and transmit functions
syscalls.c, sysmem.c – Required for printf support
Flow
Initialize system clock
Initialize UART
Initialize ADC
Continuously:
Read ADC value
Print value over UART
Delay (optional)
Example Output (UART)
ADC Value: 2048
ADC Value: 2156
ADC Value: 1987
Optionally converted to voltage:
Voltage: 1.65 V
How to Run
Open project in STM32CubeIDE
Build the project
Flash to board
Open a serial terminal:
Baud rate: 115200
Data bits: 8
Stop bits: 1
Parity: None
Turn the potentiometer and observe output
Why This Matters
This project builds intuition for:
ADC resolution and scaling
Reference voltage limits
Polling vs interrupt-driven ADC
UART debugging (essential for embedded work)
If you can’t explain why the ADC value changes when you turn the knob, you don’t understand ADCs yet. This project fixes that.
Possible Extensions
Convert ADC value to voltage properly
Use ADC interrupts or DMA
Display value on an LCD/TFT
Add moving average filtering
Trigger actions based on thresholds
Author
Jahmai Cabrera
Embedded / Firmware-focused Computer Science student
Built as part of low-level STM32 practice
