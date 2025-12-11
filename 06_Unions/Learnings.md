# Union
- A union is a special data structure where all members share the same memory location.
- It allows we to store data in one form and access it in another, without conversions.

```c
union Example {
    uint32_t num;
    uint8_t bytes[4];
};
```
- In this example, num and bytes occupy the same 4 bytes of memory.

## Why Use Unions in Firmware?
| Use Case	|                                    Example |
| --- | --- |
| Access individual bytes of a register |	        Transmitting 32-bit values as 4 bytes |
| Overlay structured fields on raw buffers	|    Parse sensor or protocol frames |
| Serialize/deserialize data to/from byte streams	| UART, SPI, I2C communication |
| Interpret float as 4 raw bytes	|                Sending float over network or UART |

## Key Concept: Memory Reinterpretation
- We can write to one member of the union and read from another:
```c
union Data {
    float f;
    uint8_t bytes[4];
};

union Data d;
d.f = 3.14;

// Now d.bytes contains raw byte representation of float
```

- Important: No memory is copied. This is just a reinterpretation of the same bytes.

## Common Union Patterns in Firmware
### 1. Extract Bytes from a 32-bit Value
```c
union {
    uint32_t value;
    uint8_t bytes[4];
} reg;

reg.value = 0x12345678;
// reg.bytes[0] = 0x78 (LSB), reg.bytes[3] = 0x12 (MSB)
```

- Useful in: Sending 32-bit data over 8-bit UART, Writing data into memory-mapped buffers

### 2. Modify Specific Bytes

```c
reg.bytes[0] = 0xAB;  // Modify LSB
reg.bytes[3] = 0xCD;  // Modify MSB
```
- Updates the overall reg.value automatically.

### 3. Overlay Struct on Union (Packet Layout)

```c
union Packet {
    struct {
        uint8_t header;
        uint8_t length;
        uint8_t payload[2];
        uint8_t checksum;
    };
    uint8_t raw[5];
};
```
- we can fill fields via struct and transmit raw[ ], or receive raw[ ] and access fields via struct.

### 4. Decode Bitfields from ADC or Status Register
```c
typedef union {
    uint16_t raw;
    struct {
        uint16_t data : 12;
        uint16_t gain : 2;
        uint16_t ready : 1;
        uint16_t error : 1;
    } bits;
} ADC_Result;

ADC_Result res;
res.raw = 0x8D4E;Copy
```
- We can access res.bits.gain or res.bits.data directly, like register view.

### 5. Transmit Float as Bytes
```c
union {
    float f;
    uint8_t b[4];
} tx;

tx.f = 2.718;
// Now send tx.b[0..3] over UARTCopy
```
 
## Struct vs Union — Key Difference
- Struct: All members occupy separate memory — total size is the sum of all members (plus padding).
- Union: All members share the same memory — total size is equal to the size of the largest member.

### Example:
```c
struct S {
    uint32_t a;   // 4 bytes
    uint8_t  b;   // 1 byte
}; // Likely size = 8 (due to padding)

union U {
    uint32_t a;   // 4 bytes
    uint8_t  b;   // shares with a
}; // Size = 4
```

## Union Firmware Relevance

| Where it Helps | How |
| ----- | -----|
|  Low-level communication| Convert structured data to raw byte stream |
| Compact control register design | Access fields and bytes efficiently |
| Protocol simulation | Interpret packets by field |
| Debugging / Analysis | Byte-level inspection of float/int |
| Buffer-safe conversion | No memcpy needed |

## Common Pitfalls

| Mistake | 	Fix |
| ----| ----|
|❌ Assuming order of bytes is same across systems (endianness)|	Use endian-aware handling|
|❌ Accessing wrong member after overwrite	| Always ensure which member was last written |
| ❌ Using union across different compilers	| Compiler-specific behavior in padding/bit order (document  format) |
| ✅ Use unions for reinterpretation, not logic computation ||
| ✅ Always check sizeof(union) if using in communication	| |
