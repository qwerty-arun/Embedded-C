// Scan Memory for Three Consecutive Increasing Values

/*
You are given a block of memory (as an integer array) of size n.

Your task is to write a function that scans the memory using pointers and detects the first occurrence of three consecutive increasing integers — for example: [4, 5, 6] or [10, 11, 12].

Return the starting index of the first such pattern. If no such pattern is found, return -1.You must use pointer logic only, not array indexing.
 

Example-1
Input: n = 8, memory = [2, 4, 5, 6, 9, 11, 12, 14]
Output: 1

Example-2
Input: n = 6, memory = [10, 20, 30, 40, 50, 60]
Output: -1

Example-3
Input: n = 7, memory = [1, 2, 3, 5, 6, 7, 8]
Output: 0
*/

#include <stdio.h>

int find_pattern(int *mem, int n) {
    // Write your pointer-based logic here
    for(int i = 0; i < n - 3; i++){
        int* ptr = mem + i;
        if((*(ptr + 1) == (*ptr + 1)) && (*(ptr + 2) == (*ptr + 2))){
            return i;
        }
    }
    return -1;
}

int main() {
    int n, arr[100];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int res = find_pattern(arr, n);
    printf("%d", res);

    return 0;
}