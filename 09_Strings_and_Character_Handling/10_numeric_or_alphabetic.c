// Check if String is Numberic or Alphabetic

/*
You are given a null-terminated input string. Your task is to:
- Print "NUMERIC" if the string contains only digits (0–9)
- Print "ALPHABETIC" if the string contains only letters (A–Z, a–z)
- Otherwise, print "MIXED" if it contains anything else (symbols, mix of digits and letters)

Do not use standard library functions like isdigit() or isalpha(). Use only ASCII value checks.

Example-1
Input: "123456"
Output: NUMERIC

Example-2
Input: "firmwareC"
Output: ALPHABETIC

Example-3
Input: "C99"
Output: MIXED

Example-4
Input: "Hello!"
Output: MIXED

Example-5
Input: ""
Output: MIXED (empty string is considered mixed)
*/

#include <stdio.h>
#include <stdint.h>

int custom_strlen(const char *str) {
    // Your logic here
    int count = 0;
    int i = 0;
    while(str[i]!='\0'){
        count++;
        i++;
    }
    return count;
}

void classify_string(const char *str) {
    // Your logic here
    int length = custom_strlen(str);
    int digits = 0, alpha = 0;
    if(length==0){
        printf("MIXED");
        return;
    }
    for(int i = 0; i <  length; i++){
        if((int)str[i] >= 48 && (int)str[i] <= 57){
            digits++;
        }
        if(((int)str[i] >= 65 && (int)str[i] <= 90 || ((int)str[i] >= 97 && (int)str[i] <= 122))){
            alpha++;
        }
    }
    if(digits==length){
        printf("NUMERIC");
    }
    else if(alpha==length){
        printf("ALPHABETIC");
    }else{
        printf("MIXED");
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

    classify_string(str);
    return 0;
}