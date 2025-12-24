// Add Signed and Unsigned Integers Safely

/*
You are given two inputs:

- int8_t a (signed 8-bit)
- uint8_t b (unsigned 8-bit)

Your task is to:
- Perform the addition of a + b safely, ensuring that if a is negative, the final result is still correctly signed
- Return the result as a signed 16-bit integer (int16_t) so the overflow can be observed
 
Example-1
Input: a = -10, b = 20
Output: 10

Example-2
Input: a = 10, b = 250
Output: 260

Example-3
Input: a = -128, b = 255
Output: 127
*/

#include <stdio.h>
#include <stdint.h>

int16_t signed_unsigned_sum(int8_t a, uint8_t b) {
    // Your logic here
    int16_t result = (int16_t)a + (int16_t)b;
    return result;
}

int main() {
    int8_t a;
    uint8_t b;
    scanf("%hhd %hhu", &a, &b);
    printf("%d", signed_unsigned_sum(a, b));
    return 0;
}

/*
What’s the issue?
- In C, if a is negative and b is unsigned, a gets promoted to unsigned before addition, leading to unexpected results.

Example: -1 (int8_t) + 1 (uint8_t) becomes 255 + 1 = 256 if promoted incorrectly.

Why it matters in firmware?
- Timers, buffer indexes, counters — mixing signed and unsigned is common
- Avoiding implicit conversion bugs is critical for reliability

Solution Logic
- Cast both a and b to int16_t explicitly before adding
- Prevents unsigned overflow from negative signed values
*/