// Convert Binary String to Integer Without strtol function or Libraries

/*
In embedded systems, you may receive data as binary strings (e.g., "1101") via UART or user input, and need to convert it to an actual integer value — without using standard functions like strtol() or atoi().

Your task is to:

- Read a string of '0' and '1' characters (max length 16)
- Convert it to an unsigned integer
- You must not use any standard string conversion functions

Example-1
Input: 1010
Output: 10

Example-2
Input: 0001
Output: 1

Example-3
Input: 11111111
Output: 255

Example-4
Input: 0
Output: 0
*/

#include <stdio.h>
#include <stdint.h>

int custom_strlen(const char *str) {
    // Your logic here
    int count = 0;
    int i = 0;
    while(str[i]!='\0'){
        count++;
        i++;
    }
    return count;
}

int power_of_2(int exp){
    int result = 1;
    for(int i = 0; i < exp; i++){
        result *= 2;
    }
    return result;
}

uint16_t binary_to_uint(const char *str) {
    // Your logic here
    int len = custom_strlen(str);
    uint16_t integer = 0;
    for(int i = 0; i < len; i++){
        integer += (str[i]-'0') * power_of_2(len-i-1);
    }
    return integer;
}

/*
// Convert binary string to uint16_t value
uint16_t binary_to_uint(const char *str) {
    uint16_t result = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        result <<= 1;  // Shift left by 1
        if (str[i] == '1') {
            result |= 1;  // Add 1 if current char is '1'
        } else if (str[i] != '0') {
            // Invalid character
            return 0xFFFF;  // Optional error handling
        }
    }

    return result;
}
*/

int main() {
    char bin[20];
    scanf("%s", bin);

    printf("%u", binary_to_uint(bin));
    return 0;
}

/*
Why This Is Useful in Firmware?
- Bit-level configuration input from CLI/UART often comes as strings
- Manually converting avoids reliance on stdlib functions
- Helps in decoding configuration commands, boot settings

Logic Summary
- Start with result = 0
- For each character:
    - Left-shift result
    - Add 1 if char is '1'
    - Ignore if '0', or error if anything else
*/