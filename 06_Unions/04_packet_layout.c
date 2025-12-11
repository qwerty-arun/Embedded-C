// Packet Layout Using Union with Struct

/*
You’re implementing a communication packet for transmission. Each packet is 6 bytes structured as follows:

Field	    Size (bytes)
Start Byte	1
Command	    1
Data (2B)	2
CRC	        1
End Byte	1
 

Your task is to:

- Define a union that overlays:
    - a struct view of these fields, and
    - a uint8_t[6] array view
- Accept values for start, command, data (16-bit), CRC, and end
- Fill the packet struct
- Print the raw 6-byte array using the byte array view
 
Example-1
Input: start = 0xA5, cmd = 0x01, data = 0x1234, crc = 0x77, end = 0x5A
Output: 165 1 52 18 119 90
 
Example-2
Input: start = 0xAA, cmd = 0xFF, data = 0x00FF, crc = 0xFE, end = 0x55
Output: 170 255 255 0 254 85
*/

#include <stdio.h>
#include <stdint.h>

typedef union {
    struct {
        uint8_t start;
        uint8_t command;
        uint16_t data;
        uint8_t crc;
        uint8_t end;
    } fields;
    uint8_t raw[6];
} Packet;

// Fill struct fields and print raw bytes
void build_and_print_packet(uint8_t s, uint8_t c, uint16_t d, uint8_t crc, uint8_t e) {
    // Your logic here
    Packet packet;
    packet.fields.start = s;
    packet.fields.command = c;
    packet.fields.data = d;
    packet.fields.crc = crc;
    packet.fields.end = e;
    for(int i = 0; i < 6; i++){
        printf("%u ", packet.raw[i]);
    }
}

int main() {
    uint8_t s, c, crc, e;
    uint16_t d;
    scanf("%hhu %hhu %hu %hhu %hhu", &s, &c, &d, &crc, &e);
    build_and_print_packet(s, c, d, crc, e);
    return 0;
}