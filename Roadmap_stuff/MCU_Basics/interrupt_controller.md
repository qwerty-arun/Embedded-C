
---

# 🔥 **What Is an Interrupt Controller?**

The **Interrupt Controller** is a dedicated hardware block inside the MCU that:

1. **Receives interrupt requests** from peripherals (GPIO, Timer, UART, I2C, ADC, etc.).
2. **Decides which interrupt is more important** (priority).
3. **Tells the CPU to pause current execution** and jump to the correct **Interrupt Service Routine (ISR)**.
4. **Restores the CPU state after the ISR** and resumes normal execution.

It acts like a **traffic cop**, managing all interrupt signals coming from the MCU’s subsystems.

---

# 🔌 **Why Do We Need an Interrupt Controller?**

Because the MCU gets *many* interrupt signals, and the CPU cannot directly handle all of them.
Example:

* Timer overflow
* UART received byte
* GPIO button press
* ADC conversion complete
* SPI transfer done

The CPU needs a manager to decide:

* Which interrupt runs first?
* What if two happen at the same time?
* Should some interrupts be disabled?

This is the job of the **NVIC**.

---

# 🧠 **Core Responsibilities of NVIC / Interrupt Controller**

### ✔ **1. Enable or Disable Each Interrupt**

Every peripheral has an “interrupt enable” bit inside NVIC.

Example in ARM Cortex-M (pseudo):

```c
NVIC_EnableIRQ(USART1_IRQn);
NVIC_DisableIRQ(EXTI0_IRQn);
```

---

### ✔ **2. Set Interrupt Priority**

Not all interrupts are equal.

Timer may be **high priority**, UART **medium**, ADC **low**.

```c
NVIC_SetPriority(TIM2_IRQn, 1);   // higher priority
NVIC_SetPriority(ADC_IRQn, 5);    // lower priority
```

Lower number = higher priority.

---

### ✔ **3. Vector Table Lookup**

The interrupt controller uses a **vector table** (array of function pointers) to map each interrupt to its handler.

Example (simplified):

```
Address 0x0000: Reset_Handler
Address 0x0004: NMI_Handler
Address 0x0008: HardFault_Handler
...
Address 0x0048: EXTI0_IRQHandler   --> GPIO interrupt
Address 0x0050: TIM2_IRQHandler    --> Timer interrupt
```

---

### ✔ **4. Nested Interrupts (NVIC Feature)**

Higher-priority interrupts can interrupt lower-priority ones.

Example:

* ADC interrupt running (priority 5)
* UART interrupt occurs (priority 1)

NVIC interrupts the ADC ISR → jumps to UART ISR → returns → continues ADC ISR.

This is why it’s called **Nested**.

---

### ✔ **5. Auto stack save/restore**

When an interrupt fires:

The CPU automatically pushes registers **R0–R3, R12, LR, PC, xPSR** onto the stack.

After ISR returns, NVIC pops the registers and resumes execution.

You don't have to worry about storing CPU state manually.

---

# ⚙ **Interrupt Controller Workflow (Step-by-Step)**

Let’s say GPIO pin detects a rising edge.

### **Step 1: Peripheral raises interrupt signal**

GPIO → EXTI module → NVIC

### **Step 2: NVIC checks**

* Is this interrupt enabled?
* Is it masked/disabled?
* Is its priority higher than currently running ISR?

### **Step 3: NVIC triggers the CPU**

The CPU:

* Finishes current instruction
* Saves context to stack
* Loads ISR address from vector table

### **Step 4: MCU executes ISR**

Example:

```c
void EXTI0_IRQHandler(void) {
    // Clear interrupt flag
    EXTI->PR |= (1 << 0);

    // Your code
    toggle_LED();
}
```

### **Step 5: Return from interrupt**

ISR ends with `BX LR` or `return`, CPU restores state and continues where it left.

---

# 🧩 **Interrupt Masking vs Disabling (Important!)**

### **Disabling (NVIC)**

Stops receiving that interrupt completely.

### **Masking (PRIMASK, BASEPRI)**

Temporarily blocks specific priority levels.

Example in critical section:

```c
__disable_irq();
// critical code
__enable_irq();
```

---

# 🏗 **Block Diagram (Conceptual)**

![Image](https://microcontrollerslab.com/wp-content/uploads/2020/09/Nested-vectored-interrupt-controller-NVIC-ARM-CortexM-microcontrollers.jpg?utm_source=chatgpt.com)

![Image](https://toshiba.semicon-storage.com/content/dam/toshiba-ss-v3/master/en/semiconductor/knowledge/e-learning/tx03-series-microcontrollers/chapter2/2-1-1.gif?utm_source=chatgpt.com)

Important components:

* Interrupt input lines
* Priority encoder
* Vector address generator
* Control registers (enable, pending, active)
* CPU interface

---

# 📌 **Useful Registers in NVIC**

| Register | Purpose                          |
| -------- | -------------------------------- |
| **ISER** | Interrupt Set-Enable Register    |
| **ICER** | Interrupt Clear-Enable Register  |
| **ISPR** | Interrupt Set-Pending Register   |
| **ICPR** | Interrupt Clear-Pending Register |
| **IPR**  | Interrupt Priority Registers     |

Example:

```c
NVIC->ISER[0] |= (1 << 6);  // Enable interrupt #6
NVIC->IPR[1]  = 0x20;       // Set priority
```

---

# 🧪 Want a practical example with full code?

I can show you how an interrupt goes from **GPIO → EXTI → NVIC → ISR** or from **Timer → NVIC → ISR** with complete pseudocode and actual register values.