// Convert Integer to String

/*
In embedded systems, numeric values often need to be converted into printable string format (e.g., for UART or display output), but you may not have access to standard C library functions like itoa() or sprintf().

Your task is to:
- Read a signed integer
- Convert it to its string representation and
- Print each character with a space between characters
- Do not use itoa(), sprintf() or string libraries

Example-1
Input: 123
Output: 1 2 3

Example-2
Input: -45
Output: - 4 5

Example-3
Input: 0
Output: 0
*/

#include <stdio.h>

void print_integer_as_string(int num) {
    // Your logic here
    if(num==0){
        printf("0");
        return;
    }
    int no[10];
    int i = 0;
    if(num < 0){
        printf("-");
        printf(" ");
        num *= -1;
    }
    while(num){
        no[i++] = num % 10;
        num = num / 10;
    }
    for(int j = i-1; j >= 0; j--){
        printf("%d ", no[j]);
    }
}

/*
// Convert integer to string and print each character with space
void print_integer_as_string(int num) {
    if (num == 0) {
        printf("0");
        return;
    }

    char buffer[12];  // Enough for -32768 to 32767
    int i = 0;
    int is_negative = 0;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Convert digits in reverse
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    // Print characters in reverse order with space
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", buffer[j]);
        if (j > 0) printf(" ");
    }
}
*/

int main() {
    int num;
    scanf("%d", &num);
    print_integer_as_string(num);
    return 0;
}

/*
Why It’s Important in Firmware?
- Required for displaying numbers on UART, LCD, or serial logs 
- Avoids dependency on heavy libraries in bare-metal systems 
- Builds deep understanding of integer encoding and display formatting 

Solution Logic:

- Handle Zero Case Directly
    - If the input number is 0, we immediately print "0" and return.
    - This avoids extra logic for zero inside the main loop.
 
- Check for Negative Numbers
  If the input number is negative:
    - Set a flag is_negative = 1 
    - Convert it to positive by negating (num = -num) 
    - This allows us to treat all digits uniformly in the next steps.
 
- Extract Digits from Least Significant to Most
    - Use a loop: num % 10 gives the last digit 
    - Convert digit to character: add '0' → (num % 10) + '0' 
    - Store each digit in a buffer in reverse order (from least to most significant)
 
- Append Negative Sign if Needed
    - If the original number was negative, add '-' to the buffer after digits
 
- Print Characters in Reverse
    - Since digits were stored in reverse, we loop backward through the buffer 
    - Print each character, with a space between them for clarity
*/