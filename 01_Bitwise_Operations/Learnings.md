# Bitwise Operations
- `|` is Bitwise `OR`: typically used to `set` a bit
- `&` is Bitwise `AND`: typically used to `clear` a bit
- `^` is Bitwise `XOR`: used to toggle (invert) a bit
- `~` is Bitwise `NOT`: used to flip all bits (1 to 0, 0 to 1)
- `<<`, `>>` are Bit Shift left/right: used to move bit positions

## Bit-masking patterns
```c
reg |= (1 << n);     // Set bit n
reg &= ~(1 << n);    // Clear bit n
reg ^= (1 << n);     // Toggle bit n
if (reg & (1 << n))  // Check if bit n is set
```

## 32-bit Register Usage
- Same techniques are used for `uint32_t` types: often used in 32-bit MCUs for status/configuration registers.
- `ctrl_reg |= (1U << 23);` // set bit 23 in a 32-bit control register

## Common Pitfalls (Practical Tips)
- Forgetting parentheses: 1 << n must be inside parentheses during masking: ✅ reg |= (1 << 4) vs ❌ reg |= 1 << 4 & 0xF
- Using signed types: Never use int for register work — use uint8_t, uint16_t, or uint32_t. Signed values may cause undefined behavior when shifting, as MSB (Most Significant Bit) used for sign.
- Wrong shift width: Shifting more than the data type width (e.g. 1 << 32 on a 32-bit int) is undefined.
- Accidental overwrite:
```c
reg = (1 << 2); // WRONG: overwrites entire register  
reg |= (1 << 2); // RIGHT: sets only the 2nd bit
```

- Check before toggle: Be careful when toggling flags — you may unintentionally clear a set flag.

## Relevance in Embedded/Firmware
- All MCU peripherals are controlled via register bits — timers, GPIOs, UART, ADC, interrupts, etc.
- Bit masking ensures safe modification without overwriting unrelated fields.
- Used in flags, control masks, interrupt status checks, and power/clock configuration.

---
- In embedded systems, a single register often contains multiple fields, each controlling a different function. These fields are packed into specific bit positions.

Example: A 16-bit Control Register

Bits	Field Name
15 – 12	Mode
11 – 8	Speed
7 – 0	Flags

### To work with them, we need two core skills:
- Extracting a field (reading the bits at a specific position)
- Replacing or updating that field (without touching other bits)

### To extract Speed field (bits 8 to 11):
`uint16_t speed = (reg >> 8) & 0x0F;`

### To update the Mode field (bits 12 to 15):

```c
reg &= ~(0x0F << 12);         // Clear Mode bits
reg |= ((new_mode & 0x0F) << 12); // Set new ModeCopy
```
--- 
## Key Operations

### Extract a bit field
```
value = (reg >> position) & mask;
```

### Replace a bit field
```
/* Where mask is a binary mask for the number of bits in the field.
E.g., For 3-bit field → mask = 0x07 */


reg &= ~(mask << position);            // Clear the bits (mask= high bits)
reg |= ((new_value & mask) << position); // Set the new bits
```

## Relevance in Embedded/Firmware
- Most hardware registers (UART, Timer, ADC, SPI) use bit fields to define different parameters.
- Peripheral setup often involves:
    - Extracting status bits (e.g., data ready, error)
    - Modifying specific bits (e.g., set baud rate, enable TX)
- It’s unsafe to overwrite the entire register — instead, we update only the target bits.

---
- This is why precise extraction and modification using bit masks is a core embedded skill.