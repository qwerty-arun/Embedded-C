// Data Transmission

/*
You are preparing a 32-bit value to send over a communication bus. To ensure compatibility across platforms, you must convert the value into 4 bytes (big-endian order) and store them into a byte array.

 
Example 1

Input: value = 0x12345678
Output: arr[0] = 0x12, arr[1] = 0x34, arr[2] = 0x56, arr[3] = 0x78
 
Example 2 

Input: value = 0x01020304
Output: arr[0] = 1, arr[1] = 2, arr[2] = 3, arr[3] = 4
 
*/

#include <stdio.h>
#include <stdint.h>

void convert_to_big_endian(uint32_t value, uint8_t arr[4]) {
    uint32_t value_copy = value;
    for(uint32_t i = 0; i < 4; i++){
        arr[3-i] = (value >> (i * 8)) & ((1U << 8) - 1);
    }
}

/*
void convert_to_big_endian(uint32_t value, uint8_t arr[4]) {
    // Your code here
    arr[0] = (value >> 24) & 0xFF;   // MSB
    arr[1] = (value >> 16) & 0xFF;
    arr[2] = (value >> 8)  & 0xFF;
    arr[3] = value & 0xFF;
}
*/

/*
void convert_to_big_endian(uint32_t value, uint8_t arr[4]) {
    // Store most significant byte first
    arr[0] = (value >> 24) & 0xFF;
    arr[1] = (value >> 16) & 0xFF;
    arr[2] = (value >> 8) & 0xFF;
    arr[3] = value & 0xFF;
}
*/

int main() {
    uint32_t value;
    uint8_t arr[4];
    scanf("%u", &value);
    convert_to_big_endian(value, arr);
    for (int i = 0; i < 4; i++) {
        printf("%u", arr[i]);
        if(i<3){
            printf(" ");
        }
    }
    return 0;
}

/*
Big-endian transmission means the most significant byte is sent first.
This format is common in network protocols and cross-platform embedded communications.

Also note: when you pass an array to a function, you’re actually passing a pointer to its first element. So any modification made to arr inside the function will reflect in the main() function — because both refer to the same memory.
*/