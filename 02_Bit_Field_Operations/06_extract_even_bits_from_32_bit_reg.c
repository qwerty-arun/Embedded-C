// Extract Even Bits Only from 32-bit Register

/*
From a 32-bit register, extract all even-positioned bits (0, 2, 4, …, 30).
Return the compressed value formed by only these bits (shifted to be consecutive).

Example 1

Input: reg = 0b0101 0101 
Output: 0b1111

Example 2 

Input: reg = 0b1010 1010 
Output: 0b0000
*/

#include <stdio.h>
#include <stdint.h>

uint32_t extract_even_bits(uint32_t reg) {
    uint16_t even_bits = 0;
    uint16_t count = 0;
    for(uint32_t i = 0; i < 32; i = i + 2){
        if(reg & (1 << i)){
            even_bits |= (1 << (count++));
        }
    }
    return even_bits;
}

int main() {
    uint32_t reg;
    scanf("%u", &reg);
    printf("%u", extract_even_bits(reg));
    return 0;
}