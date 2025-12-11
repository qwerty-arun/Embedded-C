// Transmit Float as Byte Stream Using Union

/*
In embedded systems, floating-point values are often transmitted over UART or SPI as raw bytes. You are given a float value and must simulate how it would be serialized into 4 bytes.

Your task is to:
- Define a union that contains:
    - A float variable
    - A uint8_t[4] byte array
- Read a float from input
- Use the union to access and print the 4 individual bytes in order (LSB first)

Example-1
Input: 1.0
Output:
Byte 0: 0  
Byte 1: 0  
Byte 2: 128  
Byte 3: 63

Example-2
Input: -2.5
Output (example):
Byte 0: 0  
Byte 1: 0  
Byte 2: 32  
Byte 3: 192
*/

#include <stdio.h>
#include <stdint.h>

typedef union {
    float f;
    uint8_t bytes[4];
} FloatPacket;

int main() {
    float input;
    scanf("%f", &input);

    // Fill union and print 4 bytes
    FloatPacket packet;
    packet.f = input;
    for(int i = 0; i < 4; i++){
        printf("Byte %d: %d\n", i, packet.bytes[i]);
    }
    return 0;
}