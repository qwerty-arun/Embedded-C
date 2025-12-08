
# ⭐ 1. **Clock System in an MCU**


The **clock system** decides *how fast* the MCU runs. It provides timing to:

* CPU core
* Buses (AHB, APB)
* Timers
* UART/I2C/SPI
* ADC, DAC
* DMA

### 🔹 **Common Clock Sources**

MCUs usually have multiple clock sources:

| Clock Source                             | Description                                                | Pros / Cons                                            |
| ---------------------------------------- | ---------------------------------------------------------- | ------------------------------------------------------ |
| **HSI (High-Speed Internal oscillator)** | Internal RC oscillator (e.g., 8 MHz, 16 MHz)               | Fast startup, low power, but **less accurate**         |
| **HSE (High-Speed External)**            | Crystal/oscillator connected externally (4–25 MHz typical) | **High accuracy**, stable, used when precision matters |
| **LSI (Low-Speed Internal)**             | Slow RC (~32 kHz)                                          | For watchdogs / low-power                              |
| **LSE (Low-Speed External)**             | External 32.768 kHz crystal                                | Accurate RTC clock                                     |

### 🔹 **Clock Distribution Overview**

Most MCUs follow this flow:

```
Clock Source → PLL → System Clock (SYSCLK) → AHB → APB1 & APB2 → Peripherals
```

### 🔹 **Prescalers**

Prescalers divide the clock for different subsystems:

* **AHB Prescaler:** CPU speed
* **APB Prescaler:** Peripherals like UART, SPI
* **Timer Clock Doubling:**
  In STM32, if APB prescaler ≠ 1 → timer clock ×2

---

# ⭐ 2. **PLL (Phase-Locked Loop)**


The **PLL is a frequency multiplier**.

### Example

You have an **8 MHz** HSI clock.
But you want the MCU to run at **80 MHz or 168 MHz**.

→ Feed the 8 MHz into the PLL
→ Multiply using PLLM, PLLN
→ Divide using PLLP

Example for STM32F4:

```
Input: 8 MHz
PLLM: 8
PLLN: 336
PLLP: 2

VCO = 8 / 8 * 336 = 336 MHz
SYSCLK = 336 / 2 = 168 MHz
```

### Why Use the PLL?

| Benefit                       | Explanation                                   |
| ----------------------------- | --------------------------------------------- |
| **High clock speed**          | Achieve 48–200+ MHz from small crystal values |
| **Stable frequency**          | Comes from stable external crystal            |
| **USB requires exact 48 MHz** | PLL can generate precise 48 MHz clock         |

### Steps to Configure PLL (Generic)

1. Select input source (HSI or HSE)
2. Disable PLL
3. Set PLL multipliers/dividers
4. Enable PLL
5. Wait for PLL ready flag
6. Switch System Clock to PLL

---

# ⭐ 3. **Memory Architecture in an MCU**


MCUs typically use a Harvard-like architecture with several memory regions.

## 🔹 **Major Memory Sections**

### 1️⃣ **Flash Memory**

* Non-volatile (retains data after reset)
* Stores:
  ✔ Program code (.text)
  ✔ Read-only data (.rodata)
* Slow compared to SRAM
* Typical sizes: 32 KB → 1 MB

### 2️⃣ **SRAM**

* Volatile, fast memory
* Stores runtime data:
  ✔ Stack
  ✔ Heap
  ✔ Global/static variables (.data & .bss)
* Typical sizes: 4 KB → 256 KB

### 3️⃣ **Peripheral Registers**

Memory-mapped registers for:

* GPIO
* UART
* SPI
* Timers
* ADC
* Interrupt controller (NVIC)

Example (STM32):

```
0x40020000 → GPIOA base
0x40021000 → GPIOB base
```

### 4️⃣ **System Memory**

* Stores the bootloader (factory programmed)
* Allows firmware flashing via USB/UART

### 5️⃣ **Option Bytes**

* Flash configuration (read protection, BOR levels, watchdog modes)

---

# ⭐ 4. **Memory Layout During Compilation & Linking**

When compiling a C program for MCU, memory is divided:

| Section     | Stored In    | Description                     |
| ----------- | ------------ | ------------------------------- |
| **.text**   | Flash        | Program instructions            |
| **.rodata** | Flash        | const data                      |
| **.data**   | Flash → SRAM | Initialized globals/static      |
| **.bss**    | SRAM         | Uninitialized globals/static    |
| **Heap**    | SRAM         | Dynamic allocations             |
| **Stack**   | SRAM         | Function calls, local variables |


---

# ⭐ 5. **Where Linker Scripts Fit In**

The **linker script** tells the compiler:

* Where Flash begins
* Where SRAM begins
* Size of Flash and SRAM
* Where to place .text, .data, .bss, stack, heap

Example (generic):

```
FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 64K
```

---

# ⭐ Summary (Clear & Simple)

| Concept           | One-line Explanation                                 |
| ----------------- | ---------------------------------------------------- |
| **Clock System**  | Supplies and distributes clocks to CPU & peripherals |
| **PLL**           | Multiplies frequency to run MCU faster               |
| **Flash**         | Program storage                                      |
| **SRAM**          | Variables, stack, heap                               |
| **Registers**     | Memory-mapped peripheral control                     |
| **Linker script** | Maps code/data into Flash/SRAM correctly             |

---