# Arithmetic Edge Cases

- This guide helps you understand all the tricky, often misunderstood arithmetic behaviors in C, especially relevant for firmware development where correctness and efficiency matter.

## 1. Unsigned Integer Overflow (Wraparound)

```c
uint8_t a = 250;
uint8_t b = 10;
uint8_t c = a + b;  // c = 4
```

### Why?

- uint8_t can store 0 to 255.
- 250 + 10 = 260, but 260 % 256 = 4 (wraps around).
- If we check it binary representation of 260= 1 0000 0100
- If you check last 8-bits, it's value is 4, and uint8_t can hold only last last 8 bits, so it shows the value as 4 only.

## 2. Signed Integer Overflow (Undefined Behavior)

```c
int8_t a = 120;
int8_t b = 10;
int8_t c = a + b;  // UB
```

### Why?

- int8_t max = 127. 120 + 10 = 130, which can't be represented.
- As int8_t can hold value from (0 to +127) & (-1 to -127), where MSB bit (7th-bit) defines the sign. (1= negative, 0= positive)
- C says signed overflow = undefined behavior.

## 3. Unsigned Integer Underflow (Wraparound)

```c
uint8_t a = 5;
uint8_t b = 10;
uint8_t c = a - b;  // c = 251
```

### Why?

- 5 - 10 = -5, but for unsigned: 256 - 5 = 251 (wraps backwards).

## 4. Signed Integer Underflow (Undefined Behavior)

```c
int8_t a = -120;
int8_t b = 20;
int8_t c = a - b;  // UB
```

### Why?

- -120 - 20 = -140, which is less than -128. Undefined behavior.

## 5. Signed/Unsigned Comparison Trap

```c
int a = -1;
unsigned int b = 1;
if (a < b)  // FALSE!
```

### Why?

- a is promoted to unsigned: becomes 4,294,967,295 (on 32-bit)
- So a > b is actually true!

## 6. Mixing Signed and Unsigned in Addition

```c
uint8_t a = 255;
int8_t b = -1;
int result = a + b;  // 254
```

### Why?

- Both are promoted to int: 255 + (-1) = 254.
- Safe here, but not always — be cautious.

## 7. Promotion in Arithmetic (Truncation)

```c
uint8_t a = 250, b = 10;
uint8_t sum = a + b;  // sum = 4
```

### Why?

- a + b = 260 (promoted to int), but assigned back to 8-bit → wraps to 4.

## 8. Division by Zero

```c
int a = 5, b = 0;
int c = a / b;  // Undefined
```

### Why?

- Cannot divide by zero. Causes crash or exception.

## 9. Modulo by Zero

```c
int a = 10, b = 0;
int c = a % b;  // Undefined
```

### Why?

- Same as division. Compiler may not catch it.

## 10. Negative Modulo Behavior

```c
int a = -7, b = 3;
int r = a % b;  // -1
```

### Why?

- Result follows sign of dividend (a = -7), so result = -1.

## 11. Invalid Shift Amounts

```c
int a = 1;
int b = -1;
a << b;       // Undefined
1 << 40;      // Undefined on 32-bit
```

### Why?

- Shifting by negative or >= width is undefined.

## 12. Left Shift Overflow (Signed)

```c
int8_t a = 64;
a <<= 2;  // UB
```

### Why?

- 64 << 2 = 256 → cannot be stored in 8-bit signed → UB.

## 13. Right Shift on Negative Values

```c
int8_t a = -4;
int8_t b = a >> 1;  // May be -2 or 126
```

### Why?

- Depends on whether it's arithmetic or logical shift. Implementation-defined.

## 14. Unsigned Loop Trap

```c
uint8_t i;
for (i = 3; i >= 0; i--)  // Infinite loop!
```

### Why?

- i never becomes < 0, it wraps to 255.

## 15. Pre/Post-Increment Chaos

```c
int i = 1;
int x = i++ + ++i;  // UB
```

### Why?

- Multiple writes to i without sequence point. Result is undefined.

## 16. Float to Int Precision Loss

```c
float f = 3.9;
int x = f;  // x = 3
```

### Why?

- Truncation happens — no rounding.

## 17. Integer Division Truncates

```c
int a = 5, b = 2;
int result = a / b;  // 2
```

### Why?

- Fractions are discarded (5/2 = 2.5 → 2).

## 18. Casting Negative to Unsigned

```c
int8_t a = -1;
uint8_t b = (uint8_t)a;  // 255
```

### Why?

- Two's complement conversion. -1 becomes 0xFF (255).

## 19. Float to Int Conversion

```c
float f = -2.8;
int x = f;  // x = -2
```

### Why?
- Truncates toward zero.
 

## 20. Overflow in Compound Expressions
```c
uint8_t a = 250, b = 10;
uint8_t c = (a + b) / 2;  // c = 2
```
### Why?

- a + b = 260 → wraps to 4 → 4 / 2 = 2

### ✔ Fix:
```c
uint16_t temp = a + b;
uint8_t c = temp / 2;  // Correct: 130
```