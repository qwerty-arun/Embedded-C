// Linear Search in Array

/*
You are given an array of n unsigned 8-bit integers (uint8_t) and a key. Your task is to:
- Search for the key
- Print the index of its first occurrence
- If not found, print -1

Do not use standard library functions. Use only loop and index logic.

Example-1
Input: n = 5, arr = [10 20 30 40 50], key = 30
Output: 2

Example-2
Input: n = 4, arr = [5 8 12 9], key = 7
Output: -1

Example-3
Input: n = 6, arr = [1 1 2 3 1 4], key = 1
Output: 0
*/

#include <stdio.h>
#include <stdint.h>

int linear_search(uint8_t *arr, uint8_t n, uint8_t key) {
    // Your logic here
    for(int i = 0; i < n; i++){
        if(arr[i]==key){
            return i;
        }
    }
    return -1;
}

int main() {
    uint8_t n, key;
    scanf("%hhu", &n);
    uint8_t arr[100];

    for (uint8_t i = 0; i < n; i++) {
        scanf("%hhu", &arr[i]);
    }
    scanf("%hhu", &key);

    int index = linear_search(arr, n, key);
    printf("%d", index);
    return 0;
}