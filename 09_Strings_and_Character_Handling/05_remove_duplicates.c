// Remove Duplicate Characters from a String

/*
You are given a null-terminated string containing lowercase and uppercase letters, digits, symbols, or spaces.

Your task is to:
- Remove all duplicate characters from the string
- Keep only the first occurrence of each character

The order of characters must be preserved.

Example-1
Input: "programming"
Output: progamin

Example-2
Input: "aabbcc"
Output: abc

Example-3
Input: "C language"
Output: C langue
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

void shift_substring(char *str, int index){
    int length = custom_strlen(str);
    for(int i = index; i < length ; i++){
        str[i] = str[i+1];
    }
}

void remove_duplicates(char *str) {
	//Your logic here
    int length = custom_strlen(str);
    for(int i = 0; i < length; i++){
        for(int j = i+1; j < length; j++){
            if(str[i]==str[j]){
                shift_substring(str, j);
            }
        }
    }
}

/*
void remove_duplicates(char *str) {
    uint8_t hash[256] = {0};  // 1-byte flags per ASCII char
    uint8_t read = 0, write = 0;

    while (str[read] != '\0') {
        uint8_t ch = (uint8_t)str[read];
        if (!hash[ch]) {
            hash[ch] = 1;
            str[write++] = str[read];
        }
        read++;
    }
    str[write] = '\0';  // Null terminate final string
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

    remove_duplicates(str);
    printf("%s", str);
    return 0;
}

/*
What is this about?
- This simulates low-level filtering logic — useful for parsing protocol fields, or cleaning up user input in command-line firmware shells.

Why it matters in firmware?
- Embedded systems often need to sanitize input without dynamic memory
- Understanding in-place filtering improves memory-efficient design
- Useful in string tokenization, config processing

Solution Logic
- Use an integer array of size 256 to track characters seen (ASCII)
- Two indices: read to iterate, write to overwrite
- Skip already-seen characters and write only first occurrences
*/