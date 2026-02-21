# 🚀 STM32F4 UART Sequence Detector (FSM)

A low-level, bare-metal C implementation for the **STM32F446RE** that detects a specific character sequence ("cod") using an interrupt-driven Finite State Machine (FSM).



---

## 🛠️ The "Heisenbug" Solution
This project was designed to solve a classic embedded "Heisenbug"—where code works in **Debug Mode** (manual stepping) but fails at **Run-Time** speed. 

By implementing a **Finite State Machine (FSM)** inside the UART Interrupt Service Routine (ISR), we ensure that the CPU processes exactly one character per interrupt, preventing the timing mismatches caused by high-speed UART data arrival.

## 📂 Project Structure
This project follows professional C modularity standards:

| File | Purpose |
| :--- | :--- |
| **`main.c`** | Application entry point and FSM logic within the ISR. |
| **`uart.c`** | Driver implementation for GPIO mapping, Baud Rate calculation, and Peripheral init. |
| **`uart.h`** | Header file containing public API prototypes and register bit-masks. |
| **`stm32f4xx.h`** | CMSIS device header for register access. |

---

## 🔧 Hardware Configuration
* **Board:** NUCLEO-64 STM32F446RE
* **Peripheral:** USART2
* **Baud Rate:** 115200
* **Output:** User LED on **PA5**
* **Inputs:** PA2 (TX) and PA3 (RX)



---

## 💡 How it Works
The detector uses a state-based logic to track your typing in real-time:

1.  **`WAITING_FOR_C`**: The idle state. It ignores all characters until a 'c' is received.
2.  **`WAITING_FOR_O`**: Transitions here after 'c'. If 'o' follows, it moves forward. If 'c' is hit again, it stays here (handling "ccod").
3.  **`WAITING_FOR_D`**: Transitions here after 'o'. If 'd' is hit, the sequence is complete, and the LED triggers!

### Code Snippet: The State Machine
```c
switch (currentState) {
    case WAITING_FOR_C:
        if (key == 'c') currentState = WAITING_FOR_O;
        break;
    case WAITING_FOR_O:
        if (key == 'o') currentState = WAITING_FOR_D;
        else if (key == 'c') currentState = WAITING_FOR_O;
        else currentState = WAITING_FOR_C;
        break;
    // ... logic continues
}
