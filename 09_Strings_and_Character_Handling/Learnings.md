# What Is a String in C?
- A string in C is an array of characters terminated by a null character ('\0').
```c
char msg[ ] = "OK";  // Stored as: ['O', 'K', '\0']
```
- Strings are not a built-in type in C
- No bounds checking is done by default
- Handled as raw character arrays

##  How Are Strings Stored in Memory?
```c
char s[ ] = "Hi";
```

- Index:   0     1     2
- Value: 'H'   'i'   '\0'

- You must always account for the null terminator when allocating space.

```c
char name[10]; // Can store 9 characters + '\0'
```

## Common String Operations (In Firmware Style)

| Operation	| Description |
| --- | --- |
| strlen()	| Count length (excluding '\0') |
| strcpy()	| Copy string |
| strcmp()	| Compare two strings |
| strchr()	| Search for a character |
| strcat()	| Concatenate (⚠️ risky — can cause overrun!) |
| atoi() / strtol()	| Convert string to integer |

- In firmware, we often reimplement minimal-safe versions of these.

## Character Classification
- Useful when parsing commands, serial input, file systems, etc.

| Check	 | Function	 | ASCII Range |
| --- | --- | --- |
| Is digit?	| isdigit(c) | '0' to '9' |
| Is alpha?	| isalpha(c) | 'A'–'Z', 'a'–'z' |
| Is alphanumeric? | isalnum(c) | Digit or alpha |
| To upper/lower | toupper(c), tolower(c) | Changes case |
- You can implement these yourself using ASCII values

### Example: Custom isdigit() Implemenation
```c
int is_digit(char c) {
    return (c >= '0' && c <= '9');
}
```

## Parsing Input Strings (Firmware Use Cases)
- Firmware often receives comma-separated or command-style input via UART or SPI:
```c
char input[ ] = "SET,12,ON";
```

- You may need to :
> - Split string on delimiter (e.g., ',')
> - Convert fields to numbers
> - Validate content (only ASCII allowed?)

- Use functions like:
> - strtok()
> - Manual scanning with a for loop

## Common String Challenges in Firmware

| Problem	                    | Example / Notes |
| --- | --- |
| Null terminator missing	    | Causes garbage output, memory overread |
| Buffer overflow in strcpy()	| Common cause of firmware bugs |
| Unsafe use of strcat()	    | Overwrites adjacent memory |
| Improper parsing	       | Fails if input format changes |
| Memory-inefficient operations	| Prefer minimal parsing logic |

## Embedded Relevance
- Parsing GPS/NMEA strings
- Processing AT commands in modems
- Reading sensor configuration strings
- Displaying values on LCD/UART
- Data logging & debugging
 
## Best Practices for Embedded C
- Always limit copy lengths (strncpy, or manual copy with bounds)
- Avoid dynamic memory (malloc, strdup) — use static arrays
- Validate each character when parsing input
- Handle all strings as byte buffers, especially in communication protocols

## Common Pitfalls (Practical Tips)
| Pitfall	| What to Do  |
| --- | --- | 
| ❌ Forgetting '\0' terminator	| Always allocate +1 byte for strings |
| ❌ Using strcpy blindly	| Prefer safer copy functions with limit |
| ✅ Use sizeof(arr) wisely	| Only works for stack arrays, not pointers |
| ✅ Parse manually for safety	| Avoid strtok() if reliability matters |
| ✅ Reuse char arrays where possible | Minimize static memory usage |