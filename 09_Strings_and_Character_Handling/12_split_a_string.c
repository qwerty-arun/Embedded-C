// Split a String Using Delimiter

/*
You are given a null-terminated string containing words separated by a delimiter character (like comma , or space ' ').

Your task is to:
- Split the string into individual tokens based on the delimiter
- Store the tokens in a 2D array of characters (char tokens[10][20])
- Print each token on a new line

Do not use strtok() or any string library functions.

Example-1:
Input:
str = "cmd1,cmd2,cmd3"
delimiter = ','
Output:
cmd1  
cmd2  
cmd3

Example-2:
Input:
str = "ON OFF RESET"
delimiter = ' '
Output:
ON  
OFF  
RESET
*/

#include <stdio.h>
#include <stdint.h>

void split_string(const char *str, char delimiter, char tokens[10][20], uint8_t *count) {
    // Your logic here
    int i = 0, j = 0;
    *count = 0;
    while(str[i]!='\0'){
        if(str[i]==delimiter){
            (*count)++;
            j = 0;
            i++;
        }
        tokens[*count][j] = str[i];
        j++;
        i++;
    }
    (*count)++;
}

int main() {
    char str[101];
    char delimiter;
    fgets(str, sizeof(str), stdin);
    scanf(" %c", &delimiter);

    // Remove newline
    uint8_t i = 0;
    while (str[i]) {
        if (str[i] == '\n') { str[i] = '\0'; break; }
        i++;
    }

    char tokens[10][20];
    uint8_t count = 0;

    split_string(str, delimiter, tokens, &count);

    for (uint8_t i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
    }

    return 0;
}