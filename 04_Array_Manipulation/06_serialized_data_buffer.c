// Serialized Data Buffer

/*
In firmware, you often need to assemble a communication packet as a byte array before sending it over UART/SPI.

You are given the following fields:

Field	    Size	    Description
Start	    1 byte	    Always 0xA5
Command	    1 byte	    User input
Value	    2 byte	    16-bit data (uint16_t)
Status	    1 byte	    Flags (0 or 1)
Checksum	4 byte	    32-bit checksum (uint32_t)
End	        1 byte	    Always 0x5A


Your task is to:
- Fill a uint8_t buffer[10] with the data in this order
- Use pointer casting or byte manipulation
- Print the entire buffer contents as space-separated integers

Example-1:
Input:
Command = 0x01
Value = 0x1234
Status = 1
Checksum = 0xAABBCCDD
Output:
165 1 52 18 1 221 204 187 170 90

Example-2:
Input:
Command = 0xFF
Value = 0x00FF
Status = 0
Checksum = 0x01020304
Output:
165 255 255 0 0 4 3 2 1 90
*/

#include <stdio.h>
#include <stdint.h>

void build_packet(uint8_t command, uint16_t value, uint8_t status, uint32_t checksum) {
    uint8_t buffer[10];

    buffer[0] = 0xA5;           // Start
    buffer[1] = command;        // Command

    buffer[2] = value & 0xFF;         // LSB of value
    buffer[3] = (value >> 8) & 0xFF;  // MSB of value

    buffer[4] = status;         // Status
    
    buffer[5] = checksum & 0xFF;
    buffer[6] = (checksum >> 8) & 0xFF;
    buffer[7] = (checksum >> 16) & 0xFF;
    buffer[8] = (checksum >> 24) & 0xFF;

    buffer[9] = 0x5A;           // End

    for (int i = 0; i < 10; i++) {
        printf("%u", buffer[i]);
        if(i < 9){
            printf(" ");
        }
    }
}

int main() {
    uint8_t cmd, status;
    uint16_t val;
    uint32_t crc;
    scanf("%hhu %hu %hhu %u", &cmd, &val, &status, &crc);
    build_packet(cmd, val, status, crc);
    return 0;
}