// Little Endian to Big Endian

/*
In embedded systems, communication between processors may require byte-order conversion. You are given a 32-bit unsigned integer stored in little-endian format.

Your task is to convert this value to big-endian by swapping its bytes, and print the result.

Example-1
Input: 305419896
Output: 2018915346
(0x12345678 → 0x78563412)

Example-2
Input: 1
Output: 16777216
(0x00000001 → 0x01000000)

Example-3
Input: 0xAABBCCDD
Output: 0xDDCCBBAA → 3721182122
*/

#include <stdio.h>
#include <stdint.h>

uint32_t convert_endian(uint32_t value) {
    // Write logic to swap bytes
        return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8)  |
           ((value & 0x00FF0000) >> 8)  |
           ((value & 0xFF000000) >> 24);
}

int main() {
    uint32_t val;
    scanf("%u", &val);
    printf("%u", convert_endian(val));
    return 0;
}

/*
What is Endianness?

Endianness defines the byte order in which multibyte data (e.g., int32_t) is stored in memory.

- Little-endian: LSB stored at lowest address (common in ARM, x86)
- Big-endian: MSB stored at lowest address

Why It Matters in Firmware?

- When communicating over UART, SPI, CAN, or between MCUs with different endianness, you must manually convert the byte order to match protocol or hardware expectations.

Solution Logic
- Extract each byte using masks
- Shift it to the new position
- Combine using | to form the final result
*/