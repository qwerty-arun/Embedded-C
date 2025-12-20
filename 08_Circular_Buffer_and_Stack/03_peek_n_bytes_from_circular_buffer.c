// Peek N Bytes from Circular Buffer

/*
You are given a pre-filled circular buffer of fixed size 10.

Your task is to implement a function that peeks at the next n bytes starting from the current read position (tail), without removing them or modifying the buffer state.

If n is greater than the number of available bytes (count), print "NULL" for each extra byte.

Only use pointer access (-> or (*cb).field), no dot (.) operator.

Example-1
Input: n = 4
Output: 80 90 100 10

Example-2
Input: n = 6
Output: 80 90 100 10 20 30

Example-3
Input: n = 8
Output: 80 90 100 10 20 30 NULL NULL
*/

#include <stdio.h>

typedef struct {
    int buffer[10];
    int head;
    int tail;
    int count;
    int capacity;
} CircularBuffer;

// Write your logic inside this function
void peek_bytes(CircularBuffer *cb, int n) {
    // Your code here
    for (int i = 0; i < n; i++) {
        if (cb->count == 0) {
            printf("NULL");
        } else {
            int val = cb->buffer[cb->tail];
            printf("%d", val);
            cb->tail = (cb->tail + 1) % cb->capacity;
            cb->count--;
        }
        if(i < n-1){
            printf(" ");
        }
    }
}

int main() {
    CircularBuffer cb = {
        .buffer = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
        .head = 3,
        .tail = 7,
        .count = 6,
        .capacity = 10
    };

    int n;
    scanf("%d", &n);

    peek_bytes(&cb, n);

    return 0;
}