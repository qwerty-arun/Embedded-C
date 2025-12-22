// Implement Custom strcpy function

/*
In C, the strcpy() function copies a null-terminated string from source to destination.

Your task is to implement a custom version of strcpy() that copies one string into another without using built-in functions.

You will be given:
- A source string src
- A destination buffer dest[101] (you must copy into it)

Ensure the destination is null-terminated, just like standard strcpy.

Example-1
Input: "firmware"
Output: firmware

Example-2
Input: "abc 123"
Output: abc 123

Example-3
Input: ""
Output: ``
*/

#include <stdio.h>

void custom_strcpy(char *dest, const char *src) {
    // Your logic here
    int i = 0;
    while(src[i]!='\0'){
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0';
}

int main() {
    char src[101];
    char dest[101];
    fgets(src, sizeof(src), stdin);

    // Remove newline
    int i = 0;
    while (src[i] != '\0') {
        if (src[i] == '\n') {
            src[i] = '\0';
            break;
        }
        i++;
    }

    custom_strcpy(dest, src);
    printf("%s", dest);
    return 0;
}