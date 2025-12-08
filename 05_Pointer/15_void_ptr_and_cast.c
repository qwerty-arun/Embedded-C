// Void Pointer and Casting

/*
You are writing a utility function that adds two values — but the values can be either:
- int, or
- float

You will be given void* pointing to the first and second value and a char type specifier: 'i' for int, 'f' for float.

Your task is to:
- Cast the void* to appropriate type based on the specifier
- Perform the addition
- Print the result (as integer or float)

Use proper void* casting and dereferencing logic

Example-1
Input: type = i, a = 10, b = 20
Output: 30

Example-2
Input: type = f, a = 3.5, b = 2.5
Output: 6.0

Example-3
Input: type = i, a = -5, b = 7
Output: 2
*/

#include <stdio.h>

void add_and_print(void *a, void *b, char type) {
    // Write your logic here using type casting
    if(type == 'i'){
        printf("%d", *((int*)a) + *((int*)b));
    }
    if(type == 'f'){
        printf("%0.1f", (*(float*)a) + *((float*)b));
    }
}

int main() {
    char type;
    scanf(" %c", &type);

    if (type == 'i') {
        int x, y;
        scanf("%d %d", &x, &y);
        add_and_print(&x, &y, type);
    } else if (type == 'f') {
        float x, y;
        scanf("%f %f", &x, &y);
        add_and_print(&x, &y, type);
    }

    return 0;
}