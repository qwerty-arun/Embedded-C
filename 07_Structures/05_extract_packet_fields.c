// Extract Packet Fileds form Byte Stream

/*
You receive a 6-byte data packet from a peripheral interface (e.g., UART or I2C). The byte stream format is:

Byte Index	Field	Size
0	        start	1
1	        command	1
2–3	        data	2
4	        crc	    1
5	        end	    1

You are given the packet as an array: uint8_t buffer[6]. Your task is to extract and print each field as integer values
 
Example-1
Input: 165 1 52 18 119 90
Output:
Start: 165
Command: 1
Data: 4660
CRC: 119
End: 90

Example-2
Input: 170 255 255 0 254 85
Output:
Start: 170
Command: 255
Data: 255
CRC: 254
End: 85
*/

#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t start;
    uint8_t command;
    uint16_t data;
    uint8_t crc;
    uint8_t end;
} Packet;

void print_packet_fields(uint8_t *buffer) {
    // Overlay struct and print values
    Packet packet;
    packet.start = buffer[0];
    packet.command = buffer[1];

    packet.data = 0;
    packet.data |= buffer[2];
    packet.data |= (buffer[3] << 8);

    packet.crc = buffer[4];
    packet.end = buffer[5];

    printf("Start: %d\n", packet.start);
    printf("Command: %d\n", packet.command);
    printf("Data: %d\n", packet.data);
    printf("CRC: %d\n", packet.crc);
    printf("End: %d\n", packet.end);
}

/*
void print_packet_fields(uint8_t *buffer) {
    // Overlay buffer with Packet struct
    Packet *pkt = (Packet *)buffer;

    printf("Start: %u\n", pkt->start);
    printf("Command: %u\n", pkt->command);
    printf("Data: %u\n", pkt->data);
    printf("CRC: %u\n", pkt->crc);
    printf("End: %u", pkt->end);
}
*/

int main() {
    uint8_t buffer[6];
    for (int i = 0; i < 6; i++) {
        scanf("%hhu", &buffer[i]);
    }
    print_packet_fields(buffer);
    return 0;
}

/*
What Is Struct Overlay?

Struct overlay means interpreting raw byte memory (e.g., received UART buffer) as a structured data layout, without copying or parsing each byte manually.

Why Is It Useful in Firmware?
- Efficient — avoids per-byte parsing
- Matches register layouts or protocol frames
- Enables faster and cleaner access in memory-mapped hardware or protocol handlers

Solution Logic
- Define a struct matching the byte stream layout
- Cast buffer to Packet*
- Access fields using struct members

⚠️ This assumes compiler uses default alignment. In production firmware, #pragma pack(1) or __attribute__((packed)) may be needed.
*/