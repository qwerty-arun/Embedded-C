// Struct Padding

/*
You are given a struct with the following fields in order:
- char a
- int b
- short c

Your task is to:
- Declare a variable of this struct
- Compute the offset (in bytes) of each field from the base address of the struct (i.e., &s)

- Print:
    - Offset of a
    - Offset of b
    - Offset of c
    - Total size of the struct

Example Output
Offset of a: 0  
Offset of b: 4  
Offset of c: 8  
Size: 12
*/

#include <stdio.h>

typedef struct {
    char a;
    int b;
    short c;
} MyStruct;

void print_offsets() {
    MyStruct s;
    printf("Offset of a: %d\n", (&(s.a) - (char *)&s) * 4);
    printf("Offset of b: %d\n", (&(s.b) - (int *)&(s.a)) * 4);
    printf("Offset of c: %d\n", (&(s.c) - (short *)&(s.b)) * 4);
    printf("Size: %d", sizeof(s));
}

int main() {
    print_offsets();
    return 0;
}

/*
Padding is extra unused memory automatically inserted by the compiler between structure members to ensure data alignment as per the CPU’s architecture requirements.

Why It Matters:

In embedded systems (e.g., 32-bit ARM Cortex-M controllers), as it has 32bit address and data buse, memory is usually word-aligned, which means it can fetch 32 bits (4-bytes) as a time.

It helps to fetch Intiger variable in one-signle cycle, increasing read/ write & execution speed.

— meaning a 4-byte int should be stored at a memory address divisible by 4.

Real Impact in Firmware

Let’s say you define this structure:

struct SensorData {
    char status;   // 1 byte
    int reading;   // 4 bytes
};

On a 32-bit microcontroller:

- char status is at offset 0
- Compiler inserts 3 bytes of padding
- int reading starts at offset 4 (aligned)

Total size = 8 bytes

If padding is not added (e.g., using packed structs), the int may fall at an unaligned address (e.g., 1, 2, or 3), which causes:

- Unaligned access
- Extra memory fetch cycles for int variable.

Above code manual inspection of memory layout, which is a common low-level debugging or optimization practice.

Solution Logic:
- Cast addresses to char* for byte-level pointer arithmetic
- Subtract field address from base address to get offset
- Print total size with sizeof()
*/

#include <stdio.h>
#include <stddef.h>

typedef struct {
    char a;
    int b;
    short c;
} MyStruct;

void print_offsets() {
    printf("Offset of a: %lu\n", offsetof(MyStruct, a));
    printf("Offset of b: %lu\n", offsetof(MyStruct, b));
    printf("Offset of c: %lu\n", offsetof(MyStruct, c));
    printf("Size: %lu", sizeof(MyStruct));
}

/* my solution
void print_offsets() {
    MyStruct s;
    printf("Offset of a: %d\n", (&(s.a) - (char *)&s) * 4);
    printf("Offset of b: %d\n", (&(s.b) - (int *)&(s.a)) * 4);
    printf("Offset of c: %d\n", (&(s.c) - (short *)&(s.b)) * 4);
    printf("Size: %d", sizeof(s));
}
*/

int main() {
    print_offsets();
    return 0;
}