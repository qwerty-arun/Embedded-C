// Reverse an Array Using Only Pointers

/*
You are given an array of integers and its size n.

Using only pointer arithmetic:
- Reverse the array elements in-place.
- Print the reversed array.
❌ Do not use array indexing like arr[I].
✅ Only use pointer movements and dereferencing.

Example-1
Input: n = 5, arr = [1 2 3 4 5]
Output: 5 4 3 2 1

Example-2
Input: n = 4, arr = [10 20 30 40]
Output: 40 30 20 10

Example-3
Input: n = 3, arr = [7 8 9]
Output: 9 8 7
*/

#include <stdio.h>

void reverse_array(int *ptr, int n) {
    int *left = ptr;          // points to first element
    int *right = ptr + n - 1; // points to last element

    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    reverse_array(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if(i < n-1){
            printf(" ");
        }
    }

    return 0;
}