// Extract and Modify Field in a 32-bit Register

/*
In embedded systems, a 32-bit configuration register often contains several packed fields. 

Your task is to extract a 5-bit field located at bit positions 10 to 14 from a 32-bit register value. 

If this field’s value is less than 31, increment it by 1. Then write the updated value back to the same bit positions in the register, leaving all other bits unchanged.

Use only bitwise operations to extract, modify, and update the register.

Bit layout example (bit 0 is LSB):
Register: [31 ... 15 | 14 13 12 11 10 | 9 ... 0]
                        ↑  ↑  ↑  ↑  ↑ (target field)

Example-1

Input: 0x00003C00
Output: 0x00004000
(Field at bits 10–14 was 0x1E = 30 → incremented to 31)


Example-2

Input: 0x00000000
Output: 0x00000400
(Field was 0 → becomes 1)
 

Example-3

Input: 0x00007C00
Output: 0x00007C00
(Field was 31 → remains unchanged)
*/

#include <stdio.h>
#include <stdint.h>

uint32_t update_register(uint32_t reg) {
    // Extract Bit Field
    uint32_t value = (reg >> 10) & ((1U << 5) - 1);

    // Check if value is less than 31
    if(value < 31){
        value += 1;
    }
    
    // Mask
    uint32_t mask = ((1 << 5) -1) << 10;

    // Clear those bits
    reg &= ~mask;

    // Update with incremented value
    reg |= (value << 10);
    return reg;
}

/* Actual Solution
uint32_t update_register(uint32_t reg) {
    uint32_t mask = 0x1F << 10; // 5-bit field at bits 10–14
    uint32_t field = (reg & mask) >> 10; // Extract field

    if (field < 31) {
        field += 1; // Increment
    }

    reg &= ~mask; // Clear bits 10–14
    reg |= (field << 10); // Write updated field

    return reg;
}
*/

int main() {
    uint32_t reg;
    scanf("%u", &reg);
    uint32_t updated = update_register(reg);
    printf("%u", updated);
    return 0;
}