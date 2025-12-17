// Register Bitfields Using Struct Overlay

/*
You are implementing a simulated 8-bit control register where each bit controls a feature. Rather than using masks, you’ll use a bitfield struct to access individual bits.

The register layout is as follows:

Bit	    Field	    Size
0	    enable	    1
1–2	    mode	    2
3	    interrupt	1
4–7	    reserved	4

Your task is to:

- Define a union that overlays:
    - A struct with bitfields: enable, mode, interrupt
    - A raw uint8_t register
- Read values for enable, mode, interrupt from input
- Construct the struct, and print the final register as an 8-bit unsigned value

Assume:
- enable is 0 or 1
- mode ranges from 0–3
- interrupt is 0 or 1

Example-1
Input: 1 2 1
Output: 13

Explanation:
Binary = 00001101 → enable=1, mode=10, interrupt=1
 
Example-2
Input: 0 0 1
Output: 8
Binary = 00001000
*/

#include <stdio.h>
#include <stdint.h>

typedef union {
    struct {
        uint8_t enable    : 1;
        uint8_t mode      : 2;
        uint8_t interrupt : 1;
        uint8_t reserved  : 4;
    } bits;
    uint8_t reg;
} ControlRegister;

int main() {
    uint8_t e, m, i;
    scanf("%hhu %hhu %hhu", &e, &m, &i);

    // Construct and print register value
    ControlRegister value;
    value.bits.enable = e;
    value.bits.mode = m;
    value.bits.interrupt = i;
    printf("%d", value.reg);
    return 0;
}