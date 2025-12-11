// Control Register Using Nested Bitfields

/*
You are given a control register represented using nested struct bitfields. The register is 8-bit wide and divided into the following layout:

Bits	Field	Description
0	enable	1 = ON, 0 = OFF
1	mode	0 = Normal, 1 = Sleep
2–3	priority	2-bit value (0–3)
4–7	reserved	Reserved (must be 0)

Your task is to:

- Simulate this register using nested struct and bitfields
- Implement a function that takes a pointer to the register and validates:
  - enable must be 1
  - priority must be less than or equal to 2
  - reserved must be all 0s

Return 1 if valid, else return 0.

Example-1
Input: 0x05 → 00000101
Output: 1
(enable=1, mode=0, priority=1, reserved=0)


Example-2
Input: 0x0F → 00001111
Output: 0
(priority=3, reserved=0)


Example-3
Input: 0x95 → 10010101
Output: 0
(reserved ≠ 0)
*/

#include <stdio.h>

typedef union {
    unsigned char reg;
    struct {
        unsigned char enable : 1;
        unsigned char mode : 1;
        unsigned char priority : 2;
        unsigned char reserved : 4;
    } bits;
} ControlRegister;

// Write your logic here
int validate_register(ControlRegister *ctrl) {
    if( ctrl->bits.enable == 1 && ctrl->bits.priority <= 2 && ctrl->bits.reserved == 0){
        return 1;
    }
    return 0;
}

int main() {
    ControlRegister ctrl;
    scanf("%hhx", &ctrl.reg);

    int result = validate_register(&ctrl);
    printf("%d", result);

    return 0;
}

/*
Bitfields allow you to map hardware register layouts to individual fields cleanly.

Using a union lets you both access the entire register (reg) and its bitwise parts (bits) — common in peripheral access.

Solution Logic:

Check if enable bit is set to 1
Check if priority field is ≤ 2 (0–2 valid)
Check if all reserved bits (bits 4–7) are 0
Use pointer access (-> or (*p).) to validate each field
*/