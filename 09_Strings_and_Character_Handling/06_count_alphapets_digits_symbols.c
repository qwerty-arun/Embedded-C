// Count Alphabets Digits and Symbols in a String

/*
You are given a null-terminated string containing alphabets, digits, symbols, and spaces. Your task is to:

- Count the number of:
    - Alphabets (A–Z, a–z)
    - Digits (0–9)
    - Other symbols (anything that is not alphabet, digit, or space)

Avoid using standard library functions like isalpha(), isdigit().

Example-1
Input: "C99_Firmware!"
Output:
Alphabets = 9  
Digits = 2  
Symbols = 2

Example-2
Input: "123@hello#"
Output:
Alphabets = 5  
Digits = 3  
Symbols = 2
*/

#include <stdio.h>
#include <stdint.h>

int custom_strlen(const char *str) {
    int count = 0;
    int i = 0;
    while(str[i]!='\0'){
        count++;
        i++;
    }
    return count;
}

void classify_chars(const char *str, uint8_t *alpha, uint8_t *digit, uint8_t *symbol) {
    int length = custom_strlen(str);
    for(int i = 0; i < length; i++){
        if((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)){
            (*alpha)++;
        }else if(str[i] >= 48 && str[i] <= 57){
            (*digit)++;
        }else{
            if(str[i] != 32)
            (*symbol)++;
        }  
    }
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

    uint8_t alpha = 0, digit = 0, symbol = 0;
    classify_chars(str, &alpha, &digit, &symbol);
    printf("Alphabets = %u\nDigits = %u\nSymbols = %u", alpha, digit, symbol);
    return 0;
}