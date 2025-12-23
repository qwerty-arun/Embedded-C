# Searching and Sorting

## Why Is It Important in Embedded?

### Even in memory-limited firmware systems, you’ll often need to: 

- Look up values from tables or buffers
- Sort a few sensor readings or logs
- Find the minimum or maximum readings
- Track top N values (e.g., highest error counts)

### In firmware, we aim for:

- In-place algorithms (no extra memory)
- Deterministic timing
- Avoiding dynamic memory

### Common Embedded Use Cases
| Task	| Example in Firmware |
| --- | --- | 
| Linear Search	| Find matching sensor ID |
| Binary Search	| Search sorted command/lookup table |
| Find Min/Max	| Peak detection in sensor array |
| Sorting	| Sort last 5 samples for filtering |
| Top-N	| Top 3 highest values in diagnostics |

## Linear Search
```c
#include <stdio.h>

int linear_search(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;  // Return index if found
    }
    return -1;  // Not found
}

int main() {
    int arr[] = {10, 25, 7, 9, 13};
    int index = linear_search(arr, 5, 9);
    printf("Index = %d", index);  // Output: Index = 3
    return 0;
}
```

## Find Min and Max
```c
#include <stdio.h>

void find_min_max(int arr[], int n, int *min, int *max) {
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

int main() {
    int data[] = {15, 22, 3, 8, 19};
    int min, max;
    find_min_max(data, 5, &min, &max);
    printf("Min = %d, Max = %d\n", min, max);  // Min = 3, Max = 22
    return 0;
}
```

## Insertion Sort
```c
#include <stdio.h>

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];  // Shift element right
            j--;
        }
        arr[j + 1] = temp;  // Insert element
    }
}

int main() {
    int arr[] = {20, 5, 12, 7, 3};
    insertion_sort(arr, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);  // Output: 3 5 7 12 20
    }
    return 0;
}
```

## Binary Search
```c
#include <stdio.h>

int binary_search(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;  // Not found
}

int main() {
    int arr[] = {3, 7, 9, 12, 20};  // Must be sorted
    int index = binary_search(arr, 5, 12);
    printf("Index = %d\n", index);  // Output: Index = 3
    return 0;
}
```

## Find Top 3 Largest Values
```c
#include <stdio.h>

void find_top3(int arr[], int n, int *a, int *b, int *c) {
    *a = *b = *c = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > *a) {
            *c = *b;
            *b = *a;
            *a = arr[i];
        } else if (arr[i] > *b) {
            *c = *b;
            *b = arr[i];
        } else if (arr[i] > *c) {
            *c = arr[i];
        }
    }
}

int main() {
    int arr[] = {12, 5, 17, 9, 3};
    int first, second, third;
    find_top3(arr, 5, &first, &second, &third);
    printf("Top 3 = %d, %d, %d\n", first, second, third);  // Output: 17, 12, 9
    return 0;
}
```

## Sort Struct Array by Field
```c
#include <stdio.h>

typedef struct {
    int id;
    int value;
} Sensor;

void sort_by_value(Sensor arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].value > arr[j + 1].value) {
                Sensor temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    Sensor sensors[] = {{1, 30}, {2, 10}, {3, 20}};
    sort_by_value(sensors, 3);
    for (int i = 0; i < 3; i++) {
        printf("ID=%d Value=%d\n", sensors[i].id, sensors[i].value);
    }
    return 0;
}
```

## Embedded Best Practices

| Do this	| Why it matters |
| --- | --- |
| Use in-place sorting algorithms	| Save memory |
| Avoid recursion	| Stack depth is limited in MCUs |
| Use fixed-length arrays	| Predictable size and behavior |
| Handle empty/small arrays safely	| Avoid crashes or garbage results |
| Limit use to small datasets	| Sorting large arrays isn’t typical in firmware |
