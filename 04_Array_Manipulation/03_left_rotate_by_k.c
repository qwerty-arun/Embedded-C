// Left Rotate Array by K Positions

/*
You are given an array of size n and an integer k. Rotate the array left by k positions, in-place (without using any extra array).

This means the elements that go beyond the first k positions should wrap around to the end.


Example-1:
Input: n = 5, k = 2, arr = [1 2 3 4 5]
Output:[3  4  5  1  2]

Example-2:
Input: n = 4, k = 1, arr = [10 20 30 40]
Output:[20  30  40  10]
*/

#include <stdio.h>

void rotate_left(int arr[], int n, int k) {
    // Your logic here
    for(int i = 0; i < k; i++){
        arr[n+i] = arr[i];
    }
    for(int i = 0; i < n; i++){
        arr[i] = arr[i+k];
    }
    for(int i = 0; i < k; i++){
        arr[n+i] = 0;
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int arr[100];

    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Rotate the array
    rotate_left(arr, n, k);

    // Print the rotated array
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if(i < n-1){
        	printf(" ");
        }
    }

    return 0;
}

/*
#include <stdio.h>

// Helper function to reverse a section of the array
void reverse(int arr[], int start, int end) {
    while (start < end) {
        // Swap elements at positions start and end
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

// Function to rotate the array to the left by k positions
void rotate_left(int arr[], int n, int k) {
    k = k % n;  // Normalize k if it's greater than n

    // Step 1: Reverse first k elements
    reverse(arr, 0, k - 1);

    // Step 2: Reverse remaining n-k elements
    reverse(arr, k, n - 1);

    // Step 3: Reverse the whole array
    reverse(arr, 0, n - 1);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int arr[100];

    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Rotate the array
    rotate_left(arr, n, k);

    // Print the rotated array
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if(i < n-1){
        	printf(" ");
        }
    }

    return 0;
}
*/