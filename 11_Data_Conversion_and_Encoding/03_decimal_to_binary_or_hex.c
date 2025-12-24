// Convert Decimal Number to Binary or Hex Without itoa function

/*
In firmware development, you might need to convert numbers to binary or hexadecimal strings manually — for instance, sending over UART or displaying on an LCD — without using standard library functions like itoa().

Your task is to:
- Read an unsigned integer num and a base (2 or 16)
- Print the number in the given base as a string
- You must not use any standard string conversion like itoa() or sprintf()
- Use only loops and arithmetic

Example-1
Input: num = 10, base = 2
Output: 1010

Example-2
Input: num = 255, base = 16
Output: FF

Example-3
Input: num = 0, base = 2
Output: 0
*/

#include <stdio.h>
#include <stdint.h>

void print_base(uint16_t num, uint8_t base) {
    // Your logic here
    if(num==0){
        printf("0");
    }

    if(base==2){
        int binary[16];
        int i = 0;
        while(num){
            int r = num % 2;
            binary[i++] = r;
            num = num / 2;
        }
        for(int j = i-1 ; j >=0 ; j--){
            printf("%d", binary[j]);
        }
    }
    if(base==16){
        char hex[10];
        int i = 0;
        while(num){
            int r = num % 16;
            if(r<10){
                hex[i]=r+'0';
            }
            if(r==10){
                hex[i]='A';
            }
            if(r==11){
                hex[i]='B';
            }
            if(r==12){
                hex[i]='C';
            }
            if(r==13){
                hex[i]='D';
            }
            if(r==14){
                hex[i]='E';
            }
            if(r==15){
                hex[i]='F';
            }
            num = num / 16;
            i++;
        }
        for(int j = i-1 ; j >=0 ; j--){
            printf("%c", hex[j]);
        }
    }
}

/*
void print_base(uint16_t num, uint8_t base) {
    if (num == 0) {
        printf("0");
        return;
    }

    char digits[17] = "0123456789ABCDEF";
    char buffer[20]; // Enough to hold result
    int i = 0;

    while (num > 0) {
        buffer[i++] = digits[num % base];
        num /= base;
    }

    // Print in reverse
    for (int j = i - 1; j >= 0; j--) {
        putchar(buffer[j]);
    }
}
*/

int main() {
    uint16_t num;
    uint8_t base;
    scanf("%hu %hhu", &num, &base);

    print_base(num, base);
    return 0;
}

/*
Why This Matters in Firmware?
- itoa()/sprintf() are often not available or waste memory
- Needed for serial data formatting (e.g. binary config display, debug logs)

Logic Summary
- Convert num % base to a digit (0–9, A–F)
- Store in buffer in reverse
- Print characters in reverse order
*/