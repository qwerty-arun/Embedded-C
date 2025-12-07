# What is a Pointer?
- A pointer is a variable that stores the memory address of another variable.

```c
int x = 10;
int *ptr = &x;   // ptr holds address of x
```
- Pointers are core to C programming — especially in firmware, where direct access to memory, registers, and hardware resources is essential.

## Why Pointers Matter in Embedded
- Access memory-mapped hardware registers
- Manage arrays and buffers efficiently
- Implement pass-by-reference in functions
- Optimize memory usage with minimal overhead
- Enable modular design using a pointer to a function and a struct

## Declaring & Using Pointers
```c
int x = 25;
int *p = &x;
printf("%d", *p);   // dereferencing → prints 25
```
- &x → “address of x”
- *p → “value at address stored in p” (dereference)

## Memory Addressing Basics
- If x is at 0x2000, and int = 4 bytes:

Variable	Address	    Value
x	        0x2000	    25
p	        0x3000	    0x2000

## Common Pointer Operations

Operation	Description
int *p	    Declare pointer to int
p = &x	    Assign address of x to p
*p = 5	    Modify value pointed to by p
p++	        Move to next int (e.g., next array cell)
*(arr + i)	Access array like pointer

## Pointers and Arrays
```c
int arr[3] = {10, 20, 30};
int *p = arr;
printf("%d", *(p + 2));  // prints 30
```
- In C, arr[i] is equivalent to *(arr + i)

## Null Pointers
- int *ptr = NULL;
- NULL pointer points to nothing
- Always check before dereferencing to avoid a crash

## Pointer to Pointer
```c
int x = 10;
int *p = &x;
int **pp = &p;
```
- Used when you want to modify the original pointer itself (e.g., inside a function).

## const and Pointers
```c
const int *p1;     // pointer to constant data (can’t modify *p1)
int *const p2;     // constant pointer (can’t change p2)
const int *const p3; // const pointer to const data
```
- Useful when: 
> - Reading from memory-mapped registers (read-only)
> - Protecting data from accidental modification

## Void Pointers (void*)
- A void* is a generic pointer - it can point to any type but must be cast before dereferencing.

```c
void *ptr;
int x = 10;
ptr = &x;

printf("%d", *(int *)ptr);  // cast required
```

- Common in:
> - Generic Buffer Handling (ex. memcpy)
> - Protocol Stacks
> - Register Abstraction Layers

## Pass by Reference (Passing Pointers)
```c
void update(int *p) {
    *p = 99;
}

int main() {
    int val = 10;
    update(&val);
    // val now = 99
}
```
- Used for: updating config, writing return values, avoiding global variables

## Function Pointers
- Function pointers let you store and call functions dynamically.
```c
void blink() { printf("LED Blink\n"); }
void (*func_ptr)() = blink;
func_ptr();  // calls blink
```

### Example
```c
#include <stdio.h>
// Normal function
int add(int a, int b) {
    return a + b;
}

int main() {
    // Declare a function pointer
    int (*fp)(int, int) = add;

    // Call function using pointer
    int result = fp(5, 3);
    printf("%d\n", result);   // Output: 8

    return 0;
}
```
- Used in: state machines, callback drivers, event handlers

---

# Pointer Arithmetic
## What is Pointer Arithmetic?
- Pointer arithmetic means performing arithmetic operations like +, -, ++, or -- on pointers, to move them through memory.

```c
int arr[3] = {10, 20, 30};
int *p = arr;

p++;   // now p points to arr[1]
```

- In embedded systems, pointer arithmetic is widely used to:
> - Walk through arrays or buffers
> - Scan memory blocks
> - Handle communication frames (UART, SPI, etc.)
> - Replace array indexing for optimization

## How It Works
- When you do p + 1, it doesn’t move 1 byte — it moves to the next element based on the pointer’s type:

Pointer Type	Bytes Jumped by p + 1
int *	        4 bytes (on 32-bit MCU)
char *	        1 byte
double *	    8 bytes

- So, p++ means: go to the next element of type (not next byte)

## Example

### int vs char
```c
int nums[3] = {1, 2, 3};
char bytes[3] = {'a', 'b', 'c'};

int *iptr = nums;
char *cptr = bytes;

iptr++;  // jumps 4 bytes → now points to nums[1]
cptr++;  // jumps 1 byte  → now points to bytes[1]
```

### Accessing via Pointer
```c
int arr[5] = {5, 10, 15, 20, 25};
int *p = arr;

printf("%d", *(p + 3));   // prints 20
```
Same as arr[3] — this works with any type.

### Pointer loop example

```c
uint8_t data[4] = {1, 2, 3, 4};
uint8_t *ptr = data;

for (int i = 0; i < 4; i++) {
    printf("%d ", *(ptr + i));  // pointer arithmetic
}
```
---

## Pointer Relevance in Firmware
- Peripheral access: Registers are accessed via pointer to fixed address
- Data buffers: Efficient traversal using pointer arithmetic
- Struct access: Dynamically organized configuration or state
- Low-level drivers: Direct hardware interactions 
---
## Common Pitfalls (Practical Tips)
- Uninitialized pointer → Can crash or corrupt memory
- Forgetting to dereference → Logic error (*ptr)
- Overstepping array bounds → Memory overwrite
- Wrong pointer type → Use correct types (uint8_t*, int32_t*, etc.)
- Confusing pointer to value vs pointer to pointer
---
## Pointer Arithmatic in Embedded
- Walk through frame buffers
- Iterate over I2C/UART/SPI data blocks
- Scan sensor values, logs, circular queues
- Implement low-level string/byte parsing 
- You often use uint8_t *ptr = (uint8_t *)base_addr for hardware access.

## Common Pitfalls (Practical Tips)
- ❌ Don’t add/subtract bytes manually — rely on type-based movement.
- ❌ Don’t mix pointer arithmetic with incorrect types (e.g., char* to int)
- ❌ Never cross array bounds → causes undefined behavior
- ✅ Use pointer arithmetic for efficient loops in memory-critical code
- ✅ Cast to uint8_t* if you need byte-wise access