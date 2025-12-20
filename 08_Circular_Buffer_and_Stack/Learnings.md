# Circular Buffer

- A circular buffer (ring buffer) is a fixed-size, first-in-first-out (FIFO) data structure where data is written at the head and read from the tail, and both wrap around when reaching the end.

- In embedded firmware, circular buffers are heavily used in:
> - UART, SPI, I2C communication buffers
> - Logging systems
> - Sensor data streams
> - Real-time sampling (ADC/DMA)
> - Interrupt-safe, memory-efficient buffering

## Struct Definition
```c
#define BUFFER_SIZE 50 
typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} CircularBuffer;
```

## Initialization
```c
void init_buffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}
```

## Insert Operation (push)
```c
bool buffer_push(CircularBuffer *cb, uint8_t data) {
    if (cb->count == BUFFER_SIZE) {
        return false;  // Buffer Full
    }

    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count++;
    return true;
}
```
- Wrap-around logic via modulus keeps head ciruclar

## Read Operation (Pop)
```c
bool buffer_pop(CircularBuffer *cb, uint8_t *data) {
    if (cb->count == 0) {
        return false;  // Buffer Empty
    }

    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count--;
    return true;
}
```

## Peek Operation
```c
bool buffer_peek(CircularBuffer *cb, uint8_t *data) {
    if (cb->count == 0) return false;
    *data = cb->buffer[cb->tail];
    return true;
}
```

## Check Full and Empty
```c
bool buffer_is_full(CircularBuffer *cb) {
    return cb->count == BUFFER_SIZE;
}

bool buffer_is_empty(CircularBuffer *cb) {
    return cb->count == 0;
}
```

## Example Usage
```c
int main() {
    CircularBuffer cb;
    init_buffer(&cb);

    // Insert elements
    for (int i = 0; i < 6; i++) {
        buffer_push(&cb, i * 10);  // 0, 10, 20, ...
    }

    // Peek
    uint8_t peek_val;
    if (buffer_peek(&cb, &peek_val)) {
        printf("Peek: %d\n", peek_val);  // Should be 0
    }

    // Pop values
    uint8_t val;
    while (buffer_pop(&cb, &val)) {
        printf("Popped: %d\n", val);
    }

    return 0;
}
```

## Buffer State After Few Push/Pop Operations
- Assume
> - BUFFER_SIZE = 8
> - After pushing 4 values: [10, 20, 30, 40, _, _, _, _]
> - head = 4, tail = 0, count = 4

- If we pop twice:
> - Buffer = [10, 20, 30, 40, _, _, _, _]
> - head = 4, tail = 2, count = 2

## Relevance in Embedded Systems
| Use Case | Where Used |
| --- | --- |
| UART Rx Buffer | Interrupt-Based Serial Read |
| ADC Sampling Buffer | DMA Circular Conversion |
| Logging or Debug Buffer | Time-Ordered Messages |
| Audio or Signal Processing | Rolling Sample Window |

## Common Pitfalls (Real-World Tips)
- ❌ Forgetting to handle wrap-around → use modulus or manual wrap
- ❌ Not checking for buffer full/empty
- ❌ Overwriting unread data
- ✅ Use count to track size reliably
- ✅ Use uint8_t for tight embedded memory
- ✅ Avoid dynamic allocation — use static fixed-size buffers