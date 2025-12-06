// Count Set Bits in an Integer

/*
Write a C program to count the number of set bits (1s) in the binary representation of an integer N.

Input Format
- A single integer N.

Output Format
- Print the count of set bits.

Here are the examples for Count Set Bits in an Integer:

Example-1

Input: 5
Output: 2 (Binary: 101)
Example-2

Input: 0
Output: 0 (Binary: 0000)
Example-3

Input: 15
Output: 4 (Binary: 1111)
Example-4

Input: 1023
Output: 10 (Binary: 1111111111)
*/

#include <stdio.h>

int countSetBits(unsigned int n) {
    int count = 0;
    while(n){
        count += (n & 1);
        n >>= 1;
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", countSetBits(n));
    return 0;
}