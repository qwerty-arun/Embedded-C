// Pack Multiple Fields into a 16-bit Control Register

/*
In embedded systems, multiple configuration fields are often packed into a single register using bit-level operations.

You are given the following field specifications to be packed into a 16-bit control register:

Field	    Bits	Position (LSB-first)
Mode	    3	    Bits 0–2
Speed	    5	    Bits 3–7
Reserved	2	    Bits 8–9 (must be 0)
Status	    6	    Bits 10–15


Your task is to:
- Read mode, speed, and status from input
- Pack them into a uint16_t register following the given bit layout
- Ensure reserved bits (8–9) remain 0
- Print the resulting packed value

Example-1

Input: mode = 3, speed = 10, status = 12
Output: 12371
(Hex: 0x3053, Binary: 0011000001010011)

Example-2

Input: mode = 7, speed = 31, status = 63
Output: 64767
(Hex: 0xFCFF, Binary: 1111110011111111)

Example-3

Input: mode = 4, speed = 16, status = 8
Output: 8324
(Hex: 0x2084, Binary: 0010000010000100)

*/

#include <stdio.h>
#include <stdint.h>

uint16_t pack_register(uint8_t mode, uint8_t speed, uint8_t status) {
    uint16_t reg = 0;
    reg |= mode;
    reg |= (speed << 3);
    reg |= (status << 10);
    // reg |= (mode << 0) | (speed << 3) | (status << 10);
    return reg;
}

/* Alternate Method
uint16_t pack_register(uint8_t mode, uint8_t speed, uint8_t status) {
    uint16_t reg = 0;

    // Validate input limits
    if (mode > 7) mode = 7;         // 3 bits max
    if (speed > 31) speed = 31;     // 5 bits max
    if (status > 63) status = 63;   // 6 bits max

    reg |= (mode & 0x07);           // Bits 0–2
    reg |= (speed & 0x1F) << 3;     // Bits 3–7
    // Bits 8–9 (Reserved) left as 0
    reg |= (status & 0x3F) << 10;   // Bits 10–15

    return reg;
}
*/

int main() {
    uint8_t mode, speed, status;
    scanf("%hhu %hhu %hhu", &mode, &speed, &status);

    uint16_t reg = pack_register(mode, speed, status);
    printf("%u", reg);
    return 0;
}
