// Convert Hexadecimal String to Integer Without strtol or sscanf functions

/*
In embedded systems, you often receive hex strings from serial terminals or config files, like "1A3F", and need to convert them into integers — without using strtol(), sscanf(), or other library functions.

Your task is to:
- Read a hex string of up to 4 characters (e.g., "1A3F")
- Convert it into a uint16_t integer
- Handle both uppercase and lowercase (e.g., "af" = "AF" = 175)

Example-1
Input: 1A3F
Output: 6719

Example-2
Input: AF
Output: 175

Example-3
Input: 0000
Output: 0

Example-4
Input: ffff
Output: 65535
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

uint16_t hex_to_uint(const char *str) {
    // Your logic here
    uint16_t result = 0;
    int len = custom_strlen(str);
    for(int i = 0; i < len; i++){
        uint16_t equivalent;
        if((str[i]-'0') < 10){
            equivalent = (str[i] - '0');
        }
        if(str[i]=='a' || str[i]=='A'){
            equivalent = 10;
        }
        if(str[i]=='b' || str[i]=='B'){
            equivalent = 11;
        }
        if(str[i]=='c' || str[i]=='C'){
            equivalent = 12;
        }
        if(str[i]=='d' || str[i]=='D'){
            equivalent = 13;
        }
        if(str[i]=='e' || str[i]=='E'){
            equivalent = 14;
        }
        if(str[i]=='f' || str[i]=='F'){
            equivalent = 15;
        }
        result += equivalent * (1 << (len-i-1)*4);
    }
    return result;
}

/*
// Convert a single hex char to its integer value
uint8_t hex_char_to_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    else if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    else return 0; // Invalid character, could return error
}

// Convert hex string to unsigned integer
uint16_t hex_to_uint(const char *str) {
    uint16_t result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        result <<= 4; // shift by 4 bits (hex digit)
        result |= hex_char_to_val(str[i]);
    }
    return result;
}
*/

int main() {
    char hex[10];
    scanf("%s", hex);

    printf("%u", hex_to_uint(hex));
    return 0;
}

/*
Why This is Important in Firmware?
- Used in CLI tools, bootloaders, debug utilities
- Avoids linking large libraries (stdlib, sscanf)
- Needed in parsing hex configuration values or memory dump input

Logic Summary
- For each character in hex string:
    - Convert using manual mapping
    - Left shift result by 4 bits
    - OR in the new value
*/