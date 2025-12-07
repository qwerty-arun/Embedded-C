// Find Duplicate in Range 0 and n-1

/*
You are given an array of n integers. Each number is guaranteed to be in the range [0, n-1], and exactly one number is repeated once. Write a program to find and print the repeated number.

You cannot modify the array and cannot use extra memory (O(1) space).

Example-1
Input: n = 5 , arr = [0 1 2 3 2]
Output: 2

Example-2
Input: n = 6, arr = [5 4 3 2 1 3]
Output: 3
 
Example-3
Input: n = 4, arr = [1 0 2 0]
Output: 0
*/

#include <stdio.h>

int find_duplicate(int arr[], int n) {
    // Brute force: compare each element with every other (O(n^2))
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                return arr[i]; // Duplicate found
            }
        }
    }

    return -1; // Should never happen based on problem guarantee
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[100];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int result = find_duplicate(arr, n);
    printf("%d", result);
    return 0;
}