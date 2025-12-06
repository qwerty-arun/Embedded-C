// Count Set Bits in an 8-bit Register

/*
You are given an 8-bit register. Count how many bits are set to 1 (i.e., high) in the register.


Example 1:
Input: reg = 0b0000 1111 
Output: 4

Example 2:
Input: reg = 0b1111 0000 
Output: 4

Example 3:
Input: reg = 0b0000 0000 
Output: 0

Example 4:
Input: reg = 0b1111 1111 
Output: 8
*/

#include <stdio.h>
#include <stdint.h>

uint8_t count_set_bits(uint8_t reg) {
    // Your code here
    uint8_t count = 0;
    while(reg){
        count += ( reg & 1);
        reg >>= 1;
    }
    return count;
}

int main() {
    uint8_t reg;
    scanf("%hhu", &reg);
    printf("%u", count_set_bits(reg));
    return 0;
}