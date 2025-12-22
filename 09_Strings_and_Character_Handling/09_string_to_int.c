// Convert String to Integer

/*
You are given a null-terminated string that may contain:
- An optional sign (+ or -) at the beginning
- A numeric part made of digits
- Other non-digit characters (e.g., letters, symbols) that should be ignored once they appear

Your task is to:
- Convert the initial numeric part of the string to an integer
- Stop parsing when a non-digit character is encountered
- Return the result with the correct sign

Do not use atoi(), strtol(), or similar built-in functions.

Example-1
Input: "123abc"
Output: 123

Example-2
Input: "-45!"
Output: -45

Example-3
Input: "42@#"
Output: 42

Example-4
Input: "abc123"
Output: 0

Example-5
Input: "+78x90"
Output: 78
*/

#include <stdio.h>
#include <stdint.h>

int custom_atoi(const char *str) {
    // Your logic here
    int num = 0, i = 0;
    while(str[i]!='\0'){
        if(((int)str[i] >= 65 && (int)str[i] <= 90) || ((int)str[i] >= 97 && (int)str[i] <= 122)){
            break;
        }
        if((int)str[i] >= 48 && (int)str[i] <= 57){
            num = num * 10 + (str[i] - '0');
        }
        if(str[i]==45){
            ++i;
            while((int)str[i] >= 48 && (int)str[i] <= 57){
            num = num * 10 + (str[i] - '0');
            i++;
            }
            num = num * -1;
            return num;
        }
        i++;
    }
    return num;
}

/* Alternate solution
int custom_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    uint8_t i = 0;

    // Skip leading non-numeric characters (optional)
    // We'll keep this strict — valid parsing starts with digit or sign

    // Handle optional sign
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    // Start reading digits
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}
*/

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

    printf("%d", custom_atoi(str));
    return 0;
}