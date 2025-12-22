// Parse Comma-Separated Integers into an Array

/*
You are given a comma-separated string of integers (e.g., "10,20,30"). Each number is in the range 0–255.

Your task is to parse the string and extract all numbers into an array of integers.
- Use only basic string logic (do not use strtok() or standard tokenizing functions)
- Stop at the null terminator ('\0')
- Store results into an uint8_t[] array and print them

Example-1
Input: "10,20,30"
Output: 10 20 30
 
Example-2
Input: "5"
Output: 5
 
Example-3
Input: "1,2,3,4,5"
Output: 1 2 3 4 5
*/

#include <stdio.h>
#include <stdint.h>

// Parse comma-separated string and fill array with numbers
void parse_csv_to_array(const char *str, uint8_t *arr, uint8_t *count) {
    uint8_t num = 0;
    *count = 0;
    uint8_t i = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            // Build number from digits (ASCII to int)
            num = num * 10 + (str[i] - '0');
        } else if (str[i] == ',') {
            arr[(*count)++] = num;
            num = 0;
        }
        i++;
    }

    // Add last number if present
    arr[(*count)++] = num;
}

int main() {
    char str[101];
    fgets(str, sizeof(str), stdin);

    // Remove newline
    uint8_t i = 0;
    while (str[i]) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }

    uint8_t arr[20];
    uint8_t count = 0;

    parse_csv_to_array(str, arr, &count);

    for (uint8_t i = 0; i < count; i++) {
        printf("%u", arr[i]);
        if(i < count - 1){
            printf(" ");
        }
    }
    return 0;
}