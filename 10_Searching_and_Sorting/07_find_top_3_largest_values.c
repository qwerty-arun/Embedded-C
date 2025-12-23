// Find Top 3 Largest Values in an Array

/*
You are given an array of n unsigned 8-bit integers (uint8_t). Your task is to:
- Find the top 3 largest values from the array
- Print the values in descending order
- If n < 3, print all available values in descending order

Do not use any built-in sort functions. Use simple logic.

Example-1
Input: n = 6, arr = [10 90 20 80 70 30]
Output: 90 80 70

Example-2
Input: n = 2, arr = [5 200]
Output: 200 5

Example-3
Input: n = 3, arr = [1 2 3]
Output: 3 2 1
*/

#include <stdio.h>
#include <stdint.h>

void bubble_sort(uint8_t *arr, uint8_t n) {
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n ; j++){
            if(arr[i] <= arr[j]){
                uint8_t temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void find_top_3(uint8_t *arr, uint8_t n) {
    // Your logic here
    bubble_sort(arr, n);
    uint8_t limit = (n < 3) ? n : 3;
    for (uint8_t i = 0; i < limit; i++) {
        printf("%hhu", arr[i]);
        if(i < limit-1){
            printf(" ");
        }
    }
}

int main() {
    uint8_t n;
    scanf("%hhu", &n);
    uint8_t arr[100];

    for (uint8_t i = 0; i < n; i++) {
        scanf("%hhu", &arr[i]);
    }

    find_top_3(arr, n);
    return 0;
}