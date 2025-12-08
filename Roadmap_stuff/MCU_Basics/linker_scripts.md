
---

# 🔥 What is a Linker Script?

A **linker script** tells the **linker (ld)** exactly *where* your program should be placed in the MCU’s memory:

* Where **flash** starts and ends
* Where **SRAM** starts and ends
* Where to store **.text**, **.data**, **.bss**, **stack**, **heap**
* Where the **vector table** must be placed
* Where the **reset handler** should point
* How the startup code should initialize RAM variables

Without a linker script, your MCU firmware **cannot run** because the linker will not know the memory layout.

---

# 🧠 Why do MCUs need a linker script?

Because MCU memory is **fixed and mapped at specific addresses**.

Example STM32 memory map:

```bash
0x0800 0000  →  Flash
0x2000 0000  →  SRAM
0x4000 0000  →  Peripheral registers
```

Your code **must** go into Flash. Your global variables must go into RAM.
The linker script is the blueprint.

---

# 🧱 Structure of a Typical Linker Script (`.ld`)

A typical linker script has 2 big parts:

```ld
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data :
    {
        *(.data*)
    } > RAM AT > FLASH

    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM
}
```

Let’s explain each part clearly.

---

# 🗂️ 1. MEMORY Block

Defines the physical memory regions of the MCU.

```ld
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 20K
}
```

* `FLASH` only allows **read & execute**.
* `RAM` allows **read/write/execute**.

This tells the linker:

👉 "If you put something in FLASH, place it starting at 0x08000000."

👉 "If you put something in RAM, place it starting at 0x20000000."

---

# 🗂️ 2. SECTIONS Block

Defines what code/data goes where.

---

## 📌 `.text` Section — Code + const data

```ld
.text :
{
    *(.isr_vector)
    *(.text*)
    *(.rodata*)
} > FLASH
```

* **Interrupt vector table** goes first.
* All compiled **code** goes here.
* All **const variables** go here.

Placed in **FLASH** because code must be non-volatile.

---

## 📌 `.data` Section — Initialized Globals in RAM

```ld
.data :
{
    *(.data*)
} > RAM AT > FLASH
```

Meaning:

* At runtime, `.data` lives in **RAM**.
* But initial values are **stored in Flash**.

Startup code copies data:

```
for each variable in .data:
    RAM[i] = FLASH[i] (initial value)
```

---

## 📌 `.bss` Section — Uninitialized Globals in RAM

```ld
.bss :
{
    *(.bss*)
    *(COMMON)
} > RAM
```

* Global variables without initial values (zero-filled)
* Startup code **zeroes this region**

---

## 📌 Stack & Heap

Often defined symbolically:

```
_estack = ORIGIN(RAM) + LENGTH(RAM);
```

Stack grows downward from the top of RAM.

Heap is typically:

```
_sheap = .;
_eheap = _estack;
```

---

# 🔄 How the Linker Script Works During MCU Boot

1. MCU resets → loads **stack pointer** from vector table address
2. Looks up **Reset_Handler** address
3. Reset handler executes startup code:

   * Copies `.data` initial values from Flash → RAM
   * Zeroes `.bss`
   * Calls `main()`

Everything about this process relies on the linker script’s memory map.

---

# 🧩 Minimal Example Linker Script (Barebones)

```ld
ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data : 
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM AT > FLASH

    _sidata = LOADADDR(.data);

    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}
```

---

# 🎯 Why You Should Understand Linker Scripts (As an Embedded Engineer)

They help you:

✔ Fix memory overflow issues
✔ Place buffers in specific RAM regions (DMA requires this!)
✔ Put bootloaders at custom addresses
✔ Create custom sections for peripherals
✔ Debug faults caused by incorrect memory placement
✔ Build bare-metal systems without any RTOS/framework

Understanding linker scripts = understanding **how your MCU really runs**.

---