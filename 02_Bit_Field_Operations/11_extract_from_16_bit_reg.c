// Extract Bit Field from 16-bit Register

/*
Your task is to:
- Read a uint16_t register value
- Extract the 5-bit field from bits 4 to 8 (LSB = bit 0)
- Return the value of that field as an unsigned integer
 
Example-1

Input: 0x01F0
Output: 31
(Binary = 0000 0001 1111 0000 → bits 4–8 are all 1)


Example-2

Input: 0x0000
Output: 0


Example-3

Input: 0x00B0
Output: 11
(Binary = 0000 0000 1011 0000 → bits 4–8 = 01011)
*/

#include <stdio.h>
#include <stdint.h>

uint8_t extract_field(uint16_t reg) {
    return (reg >> 4) & ((1U << 5) - 1);
}

/* Actual Solution
uint8_t extract_field(uint16_t reg) {
    return (reg >> 4) & 0x1F;  // Shift right to align bits 4–8 to LSB, mask 5 bits
}
*/

int main() {
    uint16_t reg;
    scanf("%hx", &reg);
    printf("%u", extract_field(reg));
    return 0;
}