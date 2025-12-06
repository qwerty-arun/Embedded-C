# Bit Rotation and Counting
- Bit rotation is the operation of moving bits around a fixed-size variable in a circular manner. Unlike standard shifts that discard bits, rotations wrap the bits around to the opposite end.

- Rotate Left: Move bits to the left; overflowed bits re-enter from the right.
- Rotate Right: Move bits to the right; underflowed bits wrap back to the left.
- These are cyclic operations, useful for pattern matching, compact encoding, or simulating certain hardware behaviors.


## Rotation Example (8-bit)
Start with this value: 0b11010100 (212 in decimal)

### Example 1: Rotate Left by 3

```bash
Original   : 11010100
Step 1     : Shift Left by 3    → 10100000
Step 2     : Wrap Right 3 bits  →      110
Result     : 10100000 | 00000110 = 10100110 (0xA6)
```

- C code:
```c
uint8_t val = 0b11010100;
uint8_t result = (val << 3) | (val >> (8 - 3));
result &= 0xFF;  // Ensure 8-bit result
```

### Example 2: Rotate Right by 2

```bash
Original   : 11010100
Step 1     : Shift Right by 2   → 00110101
Step 2     : Wrap Left 2 bits   →       00
Result     : 00110101 | 00000000 = 00110101 (0x35)
```

- C code:
```c
uint8_t val = 0b11010100;
uint8_t result = (val >> 2) | (val << (8 - 2));
result &= 0xFF;  // Ensure 8-bit result
```

## Pattern Detection Use Case
- If you’re scanning a byte to detect a recurring bit sequence (like 0b0101), you can rotate the byte and check each rotated value:

```c
for (int i = 0; i < 8; i++) {
    if ((byte & 0x0F) == 0x05) {
        // Match found
    }
    byte = (byte << 1) | (byte >> 7);
    byte &= 0xFF;
}
```

## Relevance in Embedded/Firmware
- Crypto algorithms use bit rotation in hashing or key schedules.
- Sensor input decoding (like rotary encoders) may need circular bit checks.
- Efficient status flag compression, binary encoding, or circular buffer indexing.
- Pattern detection in protocol parsing, bitstreams, or error codes.
- Bit rotation helps reduce logic and cycles when solving low-level tasks with tight memory and performance constraints.

---

# Bit Counting & Power-of-Two Checks
- Bit-level operations can be used not only to modify bits, but also to analyze them. This includes:

1. Counting Set Bits (1s) in a number
2. Checking if a number is a power of two
3. Identifying the position of the highest set bit
- These operations are extremely common in firmware optimization, buffer management, error detection, and bitfield analysis.

## 1. Count Set Bits (also called Hamming Weight)
What it means: Count how many 1s are present in the binary form of a number.

### Example:

`uint8_t val = 0b11010100 → There are 4 set bits → Output = 4`

- Efficient loop:

```c
int count = 0;
while (val) {
    count += (val & 1);
    val >>= 1;
}
```

## 2. Check if a Number is a Power of Two
- A number is a power of two only if it has exactly one bit set.

Decimal	Binary	Power of 2?
1	00000001	✅ Yes
2	00000010	✅ Yes
3	00000011	❌ No
8	00001000	✅ Yes

- Bit trick:

```c
if (n != 0 && (n & (n - 1)) == 0)
    // n is power of 2
```

`Explanation: (n & (n - 1)) clears the lowest set bit. If the result is 0, only one bit was set in n.`

## 3. Keep Only the Highest Set Bit
- Sometimes you want to reduce a number to just its highest set bit (like 0b10000000 for 212).

- Example:

```c
int pos = -1;
while (n > 0) {
    pos++;
    n >>= 1;
}
// 'pos' holds the position of the highest set bit
```
---

# Embedded Relevance
- These tricks are widely used in embedded systems:

> - Bitfield parsing: Count active flags </br>
> - Sensor decoding: E.g., active pin status count </br>
> - Task scheduling: Find the highest-priority task (e.g., via MSB set) </br>
> - Memory allocation/page alignment </br>
> - Buffer size optimization: Round up to nearest power-of-two size </br>
- They enable low-overhead implementations without loops or heavy library functions.