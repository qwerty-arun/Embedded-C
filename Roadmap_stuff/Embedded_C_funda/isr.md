# ⭐ What is an Interrupt?

An **interrupt** is a hardware or software event that *pauses* the normal execution of your program so that the CPU can handle an urgent task.

Example:

* A timer overflows → interrupt
* A GPIO pin changes state → interrupt
* A UART receives a byte → interrupt

When an interrupt occurs, the CPU **jumps** to a special function called an **Interrupt Service Routine (ISR)**.

---

# ⭐ What is an Interrupt Service Routine (ISR)?

An **ISR** is a function that runs automatically when an interrupt occurs.

You do **not** call an ISR manually — the hardware does.

---

# ⭐ How an ISR Works Internally (Simplified)

1. CPU is running your main code.
2. Interrupt event occurs.
3. CPU:

   * Saves current program counter
   * Saves context (registers)
   * Jumps to ISR address
4. ISR executes.
5. ISR finishes using a special return instruction (`reti`, `iret`, etc.)
6. CPU restores context and continues from where it stopped.

---

# ⭐ ISR Syntax (MCU-specific examples)

Below are examples for common Microcontroller families.

---

## ✔ **1. AVR / Arduino GCC ISR Example (avr-gcc)**

```c
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect) {
    // Timer1 overflow interrupt logic
    PORTB ^= (1 << PB0);   // Toggle LED
}

int main() {
    DDRB |= (1 << PB0);    // LED pin as output

    TCCR1B |= (1 << CS12); // Prescaler
    TIMSK |= (1 << TOIE1); // Enable overflow interrupt

    sei();                 // Global interrupt enable

    while(1) {
        // Main loop
    }
}
```

---

## ✔ **2. ARM Cortex-M (STM32 HAL Example)**

```c
void EXTI0_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0); 
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}
```

---

## ✔ **3. PIC Microcontroller ISR Example**

```c
void __interrupt() myISR() {
    if (INTF) {         // External interrupt flag
        PORTBbits.RB0 ^= 1;
        INTF = 0;       // Clear flag
    }
}
```

---

# ⭐ Rules for Writing ISRs

### ✔ **1. ISR must be very small and fast**

No delays, no long loops.

Bad:

```c
for(int i=0; i<10000; i++);
```

Good:

```c
flag = 1;
```

---

### ✔ **2. Avoid functions inside ISR**

Unless they compile to something safe and short.

---

### ✔ **3. Use `volatile` for variables shared with ISR**

```c
volatile uint8_t flag = 0;

ISR(TIMER0_OVF_vect) {
    flag = 1;
}
```

Without `volatile`, the compiler may optimize out reads/writes.

---

### ✔ **4. Always clear the interrupt flag**

Otherwise the ISR will fire continuously.

---

### ✔ **5. Avoid heavy operations**

* Printing (`printf`)
* Dynamic memory (`malloc`)
* Complex math

---

# ⭐ Polling vs Interrupts (Quick Difference)

| Polling                   | Interrupt                   |
| ------------------------- | --------------------------- |
| CPU keeps checking events | CPU reacts only when needed |
| Wastes time               | Efficient                   |
| Simple                    | More complex                |
| Slow response             | Fast response               |

---

# ⭐ Example: Button Interrupt to Toggle LED (Simple ISR Simulation Logic)

```c
volatile int button_pressed = 0;

ISR(INT0_vect) {
    button_pressed = 1;      // ISR updates flag
}

int main() {
    setup_interrupts();
    while (1) {
        if (button_pressed) {
            button_pressed = 0;
            toggleLED();
        }
    }
}
```

ISR only sets a flag → main loop handles logic.

---

# ⭐ Real-World Use Cases of ISRs

| Peripherals | ISR Trigger               |
| ----------- | ------------------------- |
| Timers      | Periodic tasks            |
| UART        | Byte received/transmitted |
| ADC         | Conversion complete       |
| I2C/SPI     | Transfer complete         |
| GPIO        | Button press              |
| Watchdog    | Reset warning             |

---

# ⭐ Common Mistakes Beginners Make

❌ Writing long code inside ISR
❌ Forgetting `volatile`
❌ Calling delay functions inside ISR
❌ Not clearing interrupt flags
❌ Depending only on ISR without a main loop
❌ Overusing interrupts (use RTOS tasks for bigger systems)

---

# ⭐ Want Code for a Specific MCU?

I can give you **working ISR code** for:

* STM32 (HAL/LL)
* Arduino / AVR
* PIC (XC8)
* MSP430
* ESP32
* ARM bare-metal (vector table + ISR)

Just tell me **which microcontroller** you’re learning.

---