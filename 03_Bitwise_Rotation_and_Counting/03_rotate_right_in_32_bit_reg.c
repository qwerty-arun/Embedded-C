// Rotate Right in a 32-bit Register

/*
You are given a 32-bit hardware register and a number n. Rotate the register to the right by n bits in a circular fashion.
The bits shifted out on the right should reappear on the left.

Example 1

Input: reg = 0b0000 0000 0000 0000 0000 0000 0000 1111,  n = 4 
Output: 0b1111 0000 0000 0000 0000 0000 0000 0000

Example 2 

Input: reg = 0b0000 0000 0000 0000 0000 0000 0000 0001, n = 1 
Output: 0b1000 0000 0000 0000 0000 0000 0000 0000

Example 3

Input: reg = 0b1000 0000 0000 0000 0000 0000 0000 0000, n = 2 
Output: 0b0010 0000 0000 0000 0000 0000 0000 0000
*/

#include <stdio.h>
#include <stdint.h>

uint32_t rotate_right(uint32_t reg, uint8_t n) {
    n %= 32;
    return (reg >> n) | (reg << (32 - n));
}

int main() {
    uint32_t reg;
    uint8_t n;
    scanf("%u %hhu", &reg, &n);
    printf("%u", rotate_right(reg, n));
    return 0;
}