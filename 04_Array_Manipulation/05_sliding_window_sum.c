// Sliding Window Sum

/*
You are given an array of integers and a window size k. Your task is to calculate the sum of each window of size k as it slides across the array from left to right.

Return all window sums in a single line, separated by space.

Example-1
Input: n = 5, k = 3,  arr = [1 2 3 4 5]
Output: 6 9 12

Example-2
Input: n = 4, k = 2 , arr = [10 20 30 40]
Output: 30 50 70
*/

#include <stdio.h>

void sliding_window_sum(int arr[], int n, int k) {
    // Your logic here
    int window_sum;
    for(int i = 0; i < n-k+1; i++){
        window_sum = 0;
        for(int j = i; j < i+k; j++){
            window_sum += arr[j];
        }
        printf("%d ", window_sum);
    }
}

int main() {
    int n, k, arr[100];
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    sliding_window_sum(arr, n, k);
    return 0;
}