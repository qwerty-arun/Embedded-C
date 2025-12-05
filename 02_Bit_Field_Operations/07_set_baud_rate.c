// Set Baud Rate Field in Control Register

/*
You are working with a 32-bit UART control register. The baud rate is controlled by 4 bits located at position 8 (i.e., bits 8 to 11). 
Write a function to update the baud rate field with a new 4-bit value. All other bits in the register must remain unchanged.

Example 1

Input: reg = 0b0000 0000 0000 0000 0000 0000 0000 0000, baud = 0b1010  
Output: 0b0000 0000 0000 0000 0000 1010 0000 0000

Example 2

Input: reg = 0b1111 1111 1111 1111 1111 1111 1111 1111, baud = 0b0000  
Output: 0b1111 1111 1111 1111 1111 0000 1111 1111

*/

#include <stdio.h>
#include <stdint.h>

uint32_t set_baud_rate(uint32_t reg, uint8_t baud) {
    // Clear bits 8 to 11 (baud rate field)
    reg &= ~(0xF << 8);
    // Mask baud to 4 bits, shift it to position 8, and insert
    reg |= (baud & 0xF) << 8;
    return reg;
}

int main() {
    uint32_t reg;
    uint8_t baud;
    scanf("%u %hhu", &reg, &baud);
    printf("%u", set_baud_rate(reg, baud));
    return 0;
}

/*
- 0xF << 8 creates a mask for the baud rate field (4 bits at position 8).
- The field is first cleared using &= ~mask.
- The new baud value is inserted using bitwise OR after shifting to the correct position.
*/