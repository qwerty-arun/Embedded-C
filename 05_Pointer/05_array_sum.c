// Array Sum using pointers

/*
You are given an array of integers and its size n.

Using only pointer arithmetic:
- Traverse the array
- Find and print the sum of all elements.

❌ Do not use array indexing like arr[I].
✅ Only use pointer movements and dereferencing.

Example-1
Input: n = 5, arr = [1 2 3 4 5]
Output: 15

Example-2
Input: n = 4, arr = [10 20 30 40]
Output: 100

Example-3
Input: n = 3, arr = [-5 5 10]
Output: 10
*/

#include <stdio.h>

int calculate_sum(int *ptr, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += *(ptr + i);
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = calculate_sum(arr, n);
    printf("%d", result);

    return 0;
}