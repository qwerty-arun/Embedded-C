// Reverse a String In-Place

/*
You are given a null-terminated string (maximum 100 characters). Your task is to reverse the string in-place without using any additional array or library functions like strrev().

You must swap characters from both ends until the string is reversed. The null-terminator must remain at the end.

Example-1
Input: "firmware"
Output: erawmrif

Example-2
Input: "abc 123"
Output: 321 cba

Example-3
Input: ""
Output: ``
*/

#include <stdio.h>

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

void reverse_string(char *str) {
    // Your logic here
    int length = custom_strlen(str);
    int l = 0, r = length-1;
    while(l<=r){
        char temp = str[l];
        str[l] = str[r];
        str[r] = temp;
        l++;
        r--;
    }
}

int main() {
    char str[101];
    fgets(str, sizeof(str), stdin);

    // Remove newline
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }

    reverse_string(str);
    printf("%s", str);
    return 0;
}

/*
What is this about?

This problem uses pointer-based logic (or index swaps) to reverse characters in the same array, without extra memory.

Why it matters in firmware?

- Low-level buffer manipulation often needs reversal (e.g., endian swap)
- Memory is limited; in-place logic avoids extra allocation
- Good practice for boundary indexing and pointer logic

Solution Logic
- Find end of string
- Swap characters from start ↔ end
- Move pointers inward until they meet
*/