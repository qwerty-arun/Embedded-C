// Keep Only the Highest Set Bit

/*
You are given a 16-bit register (uint16_t).
Your task is to:
- Return a value where only the highest (leftmost) set bit is retained
- All other bits must be cleared

Example 1:
Input:  44        // Binary: 0000000000101100  
Output: 32        // Binary: 0000000000100000

Example 2:
Input:  512       // Binary: 0000001000000000  
Output: 512       // Binary: 0000001000000000

Example 3:
Input:  255       // Binary: 0000000011111111  
Output: 128       // Binary: 0000000010000000
*/

#include <stdio.h>
#include <stdint.h>

uint16_t highest_set_bit(uint16_t reg) {
    if(reg == 0){
        return 0;
    }
    int leftmost_set_bit_pos = 0;
    for (uint16_t i = 0; i < 16; i++){
        if (reg & (1 << i)){
            leftmost_set_bit_pos = (leftmost_set_bit_pos > i) ? leftmost_set_bit_pos : i;
        }
    }
    return (1 << leftmost_set_bit_pos);
}

/*
uint16_t highest_set_bit(uint16_t reg) {
    uint16_t setBitNo = 0;
    while(reg)
    {
        setBitNo++;
        reg>>=1;
    }
    return (1<<(setBitNo-1));
}
*/

int main() {
    uint16_t reg;
    scanf("%hu", &reg);

    uint16_t result = highest_set_bit(reg);
    printf("%hu", result);
    return 0;
}