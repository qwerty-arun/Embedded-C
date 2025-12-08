// Detect Alternating Pattern

/*
You are given a memory block as an integer array of size n. 

Your task is to check if a segment of size k starting from the beginning of the array follows an alternating pattern — e.g., 1 0 1 0 ... or 0 1 0 1 ....

Return:
    1 if the segment follows an alternating pattern
    0 if not
You must use pointer arithmetic only, not array indexing.
*/

/* IMP
Pattern detection is critical in memory validation, UART bitstreams, and protocol framing. This simulates the validation logic of expected alternating signals.

Solution Logic:
- Start with the first element’s value as the expected pattern
- Walk the pointer forward
- On each step, compare the value with the expected
- Flip expected between 1 and 0
- If all match → return 1; otherwise, return 0
*/

#include <stdio.h>

int is_alternating_pattern(int *mem, int k) {
    int *curr = mem;
    int expected = *curr;  // starting value: either 0 or 1

    for (int i = 0; i < k; i++) {
        if (*curr != expected) {
            return 0;
        }
        expected = 1 - expected;  // alternate expectation
        curr++;  // move pointer forward
    }
    return 1;
}

/*
int is_alternating_pattern(int *mem, int k) {
    for (int i = 0; i < k; i++) {
        if (*(mem + i) != (i % 2 == 0 ? *mem : 1 - *mem)) {
            return 0;
        }
    }
    return 1;
}
*/

int main() {
    int n, k, arr[100];
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int res = is_alternating_pattern(arr, k);
    printf("%d", res);

    return 0;
}