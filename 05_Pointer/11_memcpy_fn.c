// Simulate memcpy function using Pointer Walk

/*
You are given two memory buffers:
- A source array of n integers
- A destination array of the same size (pre-allocated, uninitialized)

Your task:
- Implement the function simulate_memcpy() to copy all elements from the source to destination
- ✅ You must use pointer arithmetic only
- ❌ Do not use array indexing (arr[i])

Constraints
- 1 ≤ n ≤ 100
- Data type: int
 
Example-1
Input: n = 5, source = [10, 20, 30, 40, 50]
Output: dest = 10 20 30 40 50

Example-2
Input: n = 3, source = [-5, 0, 5]
Output: dest = -5 0 5
*/

#include <stdio.h>

void simulate_memcpy(int *dest, int *src, int n) {
    // Your logic here
    for(int i = 0; i < n; i++){
        *dest = *src;
        dest++;
        src++;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int src[100], dest[100];

    for (int i = 0; i < n; i++) {
        scanf("%d", &src[i]);
    }

    simulate_memcpy(dest, src, n);

    for (int i = 0; i < n; i++) {
        printf("%d", dest[i]);
        if(i < n-1){
           printf(" "); 
        }
    }

    return 0;
}