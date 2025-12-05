// Bit Toggle

/*
Write a C program to toggle the 5th bit (0-based index) of a given integer.

- The program should take an integer N as input.
- It should toggle the 5th bit of N (i.e., flip the bit at position 5: if 0, make it 1; if 1, make it 0).

Note: The 5th bit is at position 5(0-based indexing). For example, in the binary number 100100, the 5th bit is 1.

*/

#include <stdio.h>

int toggleFifthBit(int n) {
    n ^= (1 << 5);
    return n;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", toggleFifthBit(n));
    return 0;
}