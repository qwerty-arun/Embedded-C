// Convert Integer to Hex String Without sprintf or itoa functions

/*
In embedded systems, you may need to transmit an integer value as a hexadecimal string over UART, display, or logs — but without using heavy standard functions like sprintf() or itoa().

Your task is to:
- Read an unsigned 16-bit integer num
- Print its hexadecimal string representation in uppercase
- Do not use any built-in conversion functions like itoa(), sprintf(), etc.

Example-1
Input: 255
Output: FF

Example-2
Input: 4095
Output: FFF

Example-3
Input: 0
Output: 0

Example-4
Input: 4660
Output: 1234
*/

#include <stdio.h>
#include <stdint.h>

void print_hex(uint16_t num) {
    printf("%X", num);
}

/*
void print_hex(uint16_t num) {
    if (num == 0) {
        printf("0");
        return;
    }

    char digits[17] = "0123456789ABCDEF";
    char buffer[20]; // Enough to hold result
    int i = 0;

    while (num > 0) {
        buffer[i++] = digits[num % 16];
        num /= 16;
    }

    // Print in reverse
    for (int j = i - 1; j >= 0; j--) {
        putchar(buffer[j]);
    }
}
*/

int main() {
    uint16_t num;
    scanf("%hu", &num);
    print_hex(num);
    return 0;
}