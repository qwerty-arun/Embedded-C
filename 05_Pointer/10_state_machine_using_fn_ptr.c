// State Machine Using Function Pointers

/*
You are simulating a system boot-up sequence using function pointers. 

There are 4 states:

void state_init()    { printf("Init"); }
void state_load()    { printf("Load"); }
void state_execute() { printf("Execute"); }
void state_exit()    { printf("Exit"); }

Your Task
- Implement the function run_state_sequence(int start)
- It should execute three states in sequence, starting from the given start index:
  - If start = 1 → print Load, Execute, Exit
  - If start = 3 → wrap around → print Exit, Init, Load
- ✅You must use a function pointer array
- ❌ Do not use if or switch-case
 
Constraints
- start ∈ [0, 3]
- Always execute exactly three states
- Output each state on a new line

Example-1:
Input: 0
Output:
Init
Load
Execute

Example-2:
Input: 2
Output:
Execute
Exit
Init

Example-3:
Input: 3
Output:
Exit
Init
Load
*/

#include <stdio.h>

void state_init()    { printf("Init"); }
void state_load()    { printf("Load"); }
void state_execute() { printf("Execute"); }
void state_exit()    { printf("Exit"); }

void run_state_sequence(int start) {
    // Function pointer array for 4 states
    void (*fsm[4])() = { state_init, state_load, state_execute, state_exit };

    // Execute 3 states in sequence starting from 'start'
    for (int i = 0; i < 3; i++) {
        int index = (start + i) % 4;  // Wrap around with modulo
        fsm[index]();
        if(i < 2){
            printf("\n");
        }
    }
}

int main() {
    int start;
    scanf("%d", &start);
    run_state_sequence(start);
    return 0;
}