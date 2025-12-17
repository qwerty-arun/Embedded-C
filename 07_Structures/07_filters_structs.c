// Filter Structs by Field Value for example Sensor Threshold

/*
In real embedded systems, you often store device status or sensor data in arrays of structs. You might need to filter only the relevant records based on a field — for example, sensors above a certain threshold.

Your task is to:
- Read n sensor records (each having a name and a value)
- Print only those records whose value >= threshold

Struct Format

Each record contains:
- char name[10]
- uint8_t value

Example-1:
Input:
n = 4, threshold = 50  
Sensors:  
T1 45  
T2 67  
T3 10  
T4 90

Output:
T2 67  
T4 90

Example-2:
Input:
n = 3, threshold = 100  
Sensors:  
A1 99  
A2 100  
A3 101

Output:
A2 100  
A3 101
*/

#include <stdio.h>
#include <stdint.h>

struct Sensor {
    char name[10];
    uint8_t value;
};

void print_above_threshold(struct Sensor sensors[], uint8_t n, uint8_t threshold) {
    // Your logic here
    for(int i = 0; i < n; i++){
        if(sensors[i].value >= threshold){
            printf("%s %d\n", sensors[i].name, sensors[i].value);
        }
    }
}

int main() {
    uint8_t n, threshold;
    scanf("%hhu %hhu", &n, &threshold);

    struct Sensor sensors[100];
    for (uint8_t i = 0; i < n; i++) {
        scanf("%s %hhu", sensors[i].name, &sensors[i].value);
    }

    print_above_threshold(sensors, n, threshold);
    return 0;
}