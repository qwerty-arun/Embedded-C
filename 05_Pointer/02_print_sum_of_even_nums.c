// Print Sum of Even Numbers

/*
You are given an array of integers and its size. Using only pointer arithmetic:

- Traverse the array
- Find the sum of all even numbers
- Print the sum 

❌ Do not use arr[ i ] indexing.
✅ Use only pointer movement and dereferencing.
 

Example-1
Input: n = 5, arr = [10 21 32 43 50]
Output: Sum = 92

Example-2
Input: n = 4, arr = [11 13 15 17]
Output: Sum = 0

Example-3
Input: n = 6, arr = [2 4 6 8 10 12]
Output: Sum = 42
*/

#include <stdio.h>

int sum_even_numbers(int *ptr, int n) {
    // Your logic here
    int sum = 0;
    for(int i = 0; i < n; i++){
        if(*ptr %2 == 0){
            sum += *ptr;
        }
        ptr++;
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

    int result = sum_even_numbers(arr, n);

    printf("Sum = %d", result);

    return 0;
}