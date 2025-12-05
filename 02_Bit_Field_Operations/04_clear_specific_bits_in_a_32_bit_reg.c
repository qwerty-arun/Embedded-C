// Clear Specific Bits in a 32-bit Register

/*
You are given a 32-bit control register. Clear a group of bits (set them to 0) starting at a given position and length.

Other bits must stay untouched.


Example 1

Input: reg = 0b1111 1111, pos = 4, len = 4 
Output: 0b0000 1111

Example 2 

Input: reg = 0b0000 1111, pos = 0, len = 2 
Output: 0b0000 1100
*/

#include <stdio.h>
#include <stdint.h>

uint32_t clear_bits(uint32_t reg, uint8_t pos, uint8_t len) {
    uint32_t mask = ((1 << len) - 1) << pos;
    //return reg & ~mask;
    return reg ^ mask;
}

int main() {
    uint32_t reg;
    uint8_t pos, len;
    scanf("%u %hhu %hhu", &reg, &pos, &len);
    printf("%u", clear_bits(reg, pos, len));
    return 0;
}