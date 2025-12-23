// Binary Search in Sorted Array

/*
You are given a sorted array of n unsigned 8-bit integers (uint8_t) and a key to search. Your task is to:

- Perform a binary search to find the key
- Print the index of the key if found
- If not found, print -1 

Important:
- The array is guaranteed to be sorted in ascending order
- Use only loop-based (iterative) binary search — no recursion

Example-1
Input: n = 6, arr = [5 10 15 20 25 30], key = 20
Output: 3

Example-2
Input: n = 5, arr = [2 4 6 8 10], key = 1
Output: -1

Example-3
Input: n = 4, arr = [100 150 200 250], key = 250
Output: 3
*/

#include <stdio.h>
#include <stdint.h>

int binary_search(uint8_t *arr, uint8_t n, uint8_t key) {
    int l = 0, r = n-1;
    while(l<=r){
        int mid = l + (r - l)/2;
        if(arr[mid]==key){
            return mid;
        }
        if(arr[mid] < key){
            l = mid + 1;
        }
        if(arr[mid]>key){
            r = mid - 1;
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

    int index = binary_search(arr, n, key);
    printf("%d", index);
    return 0;
}