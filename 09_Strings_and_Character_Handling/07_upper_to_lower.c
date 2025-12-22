// Convert Uppercase Letters to Lowercase

/*
You are given a null-terminated string of up to 100 characters. Your task is to:
- Convert all uppercase letters (A–Z) to lowercase (a–z)
- Leave all other characters unchanged (lowercase, digits, symbols, spaces)
- Perform the conversion in-place, using only basic character logic
- Do not use standard functions like tolower()

Example-1
Input: "Hello Embedded"
Output: hello embedded

Example-2
Input: "C99 IS POWERFUL!"
Output: c99 is powerful!
 
Example-3
Input: "test123"
Output: test123
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

void to_lowercase(char *str) {
    int length = custom_strlen(str);
    for(int i = 0; i < length; i++){
        if(str[i] >= 65 && str[i] <= 90){
            str[i] = str[i] + 32;
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

    to_lowercase(str);
    printf("%s", str);
    return 0;
}