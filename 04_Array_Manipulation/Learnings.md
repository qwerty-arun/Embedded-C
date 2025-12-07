# What is an Array?
- An array in C is a contiguous block of memory that stores multiple elements of the same data type. It allows you to:
> - Group variables together under a single name
> - Access each item using an index
> - Efficiently perform operations like iteration, sum, reverse, etc.

# Core Array Syntax and Usage in C
## Array Declaration
```c
int numbers[10];        // Array of 10 integers
uint8_t buffer[32];     // 32-byte buffer (commonly used in firmware)
```
- Declares a fixed-size array — memory is allocated statically.

## Array Initialization
```c
int values[4] = {10, 20, 30, 40};     // full initialization
int empty[4] = {0};                   // all elements = 0
char message[] = "Hi";                // string-style init
```
- If you skip the size (like message[ ]) , the compiler counts the size automatically.


## Accessing Array Elements
```c
int arr[3] = {5, 10, 15};
printf("%d", arr[1]);     // prints 10
arr[2] = 20;               // modify element at index 2Copy
```
- The index starts from 0. Always ensure you stay within 0 to n-1.

## Array Size with sizeof()
```c
int arr[5];
int total_bytes = sizeof(arr);        // e.g., 20 if int = 4 bytes
int element_bytes = sizeof(arr[0]);  // gives size of int i.e. 4 bytes 
int element_count = sizeof(arr) / sizeof(arr[0]);  // gives 5Copy
```
- This only works within the same scope where the array is declared (not when passed to a function).

# Memory Layout (Example)
`int arr[4] = {10, 20, 30, 40};`

- Assuming the starting address is 0x2000, the memory looks like:

Address	Value
0x2000	10
0x2004	20
0x2008	30
0x200C	40

Each int = 4 bytes (on most systems).

## Where Arrays Are Used in Firmware
### In embedded systems, arrays are used for:

- Data buffers (UART, SPI, ADC)
- Sensor samples
- Circular queues
- Protocol packets/frames
- Bitmaps/lookup tables

### Relevance in Embedded
- Arrays = lightweight, deterministic memory structures
- You work without dynamic memory, so statically allocated arrays are essential
- Used in interrupt routines, communication, and data processing
 
### Common Pitfalls (Practical Tips)
- Off-by-one errors: If n = 5, then valid indices are 0 to 4 (not 5).
- Wrong type for storage: If you’re reading bytes, use uint8_t[] not int[].
- Forgetting to initialize: Especially in statically defined buffers.
- Overwriting data in fixed-size buffers — always check bounds.
- Mixing pointers and arrays incorrectly — be clear whether you’re passing array base or pointer offset.