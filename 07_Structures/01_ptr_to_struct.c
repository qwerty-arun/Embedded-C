// Pointer to Struct with Bitfields

/*
You are given a pointer to a UART_ControlRegister struct representing a 32-bit hardware register.

The struct has the following bitfields:

struct UART_ControlRegister {
    unsigned int baudrate : 4;   // Bits 0-3
    unsigned int tx_enable : 1;  // Bit 4
    unsigned int rx_enable : 1;  // Bit 5
    unsigned int tx_irq_en : 1;  // Bit 6
    unsigned int rx_irq_en : 1;  // Bit 7
    unsigned int parity_en : 1;  // Bit 8
    unsigned int stop_bits : 1;  // Bit 9
    unsigned int reserved : 22;  // Bits 10-31
};

Your task:
- Write a function that receives a pointer to this struct.
- Set the UART configuration:
    - Baud rate = 9
    - TX & RX enable = 1
    - TX IRQ = 1, RX IRQ = 0
    - Parity = 1
    - Stop bit = 0
- Print each field’s value after configuration.

 
Example:

Output:
baudrate = 9
tx_enable = 1
rx_enable = 1
tx_irq_en = 1
rx_irq_en = 0
parity_en = 1
stop_bits = 0
*/

#include <stdio.h>

struct UART_ControlRegister {
    unsigned int baudrate : 4;
    unsigned int tx_enable : 1;
    unsigned int rx_enable : 1;
    unsigned int tx_irq_en : 1;
    unsigned int rx_irq_en : 1;
    unsigned int parity_en : 1;
    unsigned int stop_bits : 1;
    unsigned int reserved : 22;
};

void configure_uart(struct UART_ControlRegister *reg) {
    // Your logic here
    reg -> baudrate = 9;
    reg -> tx_enable = 1;
    reg -> rx_enable = 1;
    reg -> tx_irq_en = 1;
    reg -> rx_irq_en = 0;
    reg -> parity_en = 1;
    reg -> stop_bits = 0;
}

int main() {
    struct UART_ControlRegister reg = {0};

    configure_uart(&reg);

    printf("baudrate = %u\n", reg.baudrate);
    printf("tx_enable = %u\n", reg.tx_enable);
    printf("rx_enable = %u\n", reg.rx_enable);
    printf("tx_irq_en = %u\n", reg.tx_irq_en);
    printf("rx_irq_en = %u\n", reg.rx_irq_en);
    printf("parity_en = %u\n", reg.parity_en);
    printf("stop_bits = %u", reg.stop_bits);

    return 0;
}