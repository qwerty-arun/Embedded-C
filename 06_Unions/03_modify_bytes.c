// Modify Bytes in a 32-bit Value Using Union

/*
You are given a 32-bit integer.

You must:
- Use a union to access and modify its individual bytes
- Modify the 2nd and 3rd bytes (i.e., bytes[1] and bytes[2]) with new values
- Reconstruct and print the modified 32-bit value

Only use union-based access. Do not use bitwise operations or shifts.

Example-1
Input: 
value = 305419896 (0x12345678)
new_b1 = 0xAA, new_b2 = 0xBB
Output: 314288760
(0x12BBAA78 → bytes = [0x78, 0xAA, 0xBB, 0x12])

Example-2
Input: 
value = 1
new_b1 = 255, new_b2 = 255
Output: 16776961
(0x00FFFF01)

Example-3
Input: 
value = 0
new_b1 = 1, new_b2 = 2
Output: 131328
(0x00020100)
*/

#include <stdio.h>
#include <stdint.h>

typedef union {
    uint32_t value;
    uint8_t bytes[4];
} Register;

// Write logic here using union to modify byte[1] and byte[2]
void modify_and_print(uint32_t input, uint8_t b1, uint8_t b2) {
    // Your logic here
    Register reg;
    reg.value = input;
    reg.bytes[1] = b1;
    reg.bytes[2] = b2;
    printf("%u", reg.value);
}

int main() {
    uint32_t num;
    uint8_t b1, b2;
    scanf("%u %hhu %hhu", &num, &b1, &b2);
    modify_and_print(num, b1, b2);
    return 0;
}