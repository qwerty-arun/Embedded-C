// Event-Based Triggers Using Function Pointer Array

/*
You are building a simple event handling system where different event codes (0 to 4) trigger different actions.

Each event type corresponds to a specific function:

Event Code	Trigger Type	Function
0	        Button Press	on_button()
1	        Timer Expire	on_timer()
2	        UART Received	on_uart()
3	        Power On	    on_power()
4	        Error Detected	on_error()


You must:
- Implement a function pointer array
- Trigger the correct function based on the input event code
- If the code is outside the 0–4 range, print "Unhandled Event"

Example-1
Input: 1
Output: Timer Expired

Example-2
Input: 3
Output: Power On

Example-3
Input: 5
Output: Unhandled Event
*/

#include <stdio.h>

void on_button() {
    printf("Button Pressed");
}
void on_timer() {
    printf("Timer Expired");
}
void on_uart() {
    printf("UART Received");
}
void on_power() {
    printf("Power On");
}
void on_error() {
    printf("Error Detected");
}

// Write your event dispatcher logic here
void handle_event(int event_code) {
    // Your logic
    if(event_code > 4){
        printf("Unhandled Event");
    }
    void (*triggers[5])() = {on_button, on_timer, on_uart, on_power, on_error};
    triggers[event_code]();
}

int main() {
    int event;
    scanf("%d", &event);
    handle_event(event);
    return 0;
}