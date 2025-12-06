// Check if a Number is a Power of Two

/*
Write a function to check if a given positive integer is a power of 2. Do not use loops, multiplication, division, or library functions.
You must solve it using bitwise logic only.

Example-1

Input:  n = 8  
Output: YES

Example-2

Input:  n = 7  
Output: NO

Example-3

Input:  n = 1  
Output: YES
*/

#include <stdio.h>
#include <stdint.h>

const char* is_power_of_two(uint32_t n) {
    if(n == 0){
        return "NO";
    }
    if(n == 1){
        return "YES";
    }
    uint32_t shifted_right = (n >> 1);
    uint32_t shifted_left = (n << 1);
    if(shifted_right * 4 == shifted_left){
        return "YES";
    }
    return "NO";
}

/*
const char* is_power_of_two(uint32_t n) {
    // Check if exactly one bit is set
    if (n > 0 && (n & (n - 1)) == 0)
        return "YES";
    else
        return "NO";
}
*/

int main() {
    uint32_t n;
    scanf("%u", &n);

    const char* result = is_power_of_two(n);
    printf("%s", result);
    return 0;
}