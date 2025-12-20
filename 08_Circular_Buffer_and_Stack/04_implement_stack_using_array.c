// Implement Stack Using Array with Push and Pop Operations

/*
In embedded systems where dynamic memory is not available, stacks are typically implemented using static arrays and index tracking.

Your task is to:

- Implement a stack using a fixed-size array
- Support 2 operations:
    - push x → Push value x into the stack
    - pop → Pop and print the top value from the stack
- Print "Stack Overflow" if trying to push when full
- Print "Stack Underflow" if trying to pop when empty

Example Input Format
First line: n (number of operations)
Next n lines: push x or pop

Example-1
Input:
5  
push 10  
push 20  
pop  
pop  
pop

Output:
20  
10  
Stack Underflow

Example-2
Input:
4  
pop  
push 5  
pop  
pop

Output:
Stack Underflow  
5  
Stack Underflow
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX 10

int stack[MAX];
int top = -1;

/* Push operation */
void push(int x)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = x;
}

/* Pop operation */
void pop(void)
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", stack[top--]);
}

void process_stack(int n) {
    char command[10];
    int value;

    for (int i = 0; i < n; i++)
    {
        scanf("%s", command);

        if (strcmp(command, "push") == 0)
        {
            scanf("%d", &value);
            push(value);
        }
        else if (strcmp(command, "pop") == 0)
        {
            pop();
        }
    }

}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // Consume newline after number

    process_stack(n);
    return 0;
}