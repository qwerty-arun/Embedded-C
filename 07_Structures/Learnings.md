# Structures
- A struct groups different types of related data into one unit.

```c
typedef struct {
    uint8_t id;
    float temperature;
    uint16_t status;
} Sensor;
```
- This creates a custom type Sensor which holds:
> - A sensor ID
> - A temperature reading
> - A status word 

- You can then declare and use:
```c
Sensor s1 = {1, 36.5, 0x0001};
printf("ID: %d, Temp: %.1f, Status: %04X\n", s1.id, s1.temperature, s1.status);
```

## Accessing Struct Fields
```c
// Via variable:
Sensor s;
s.id = 2;

// Via pointer:
Sensor *ptr = &s;
ptr->temperature = 25.3;
```
- This is crucial in firmware, where structs often represent memory-mapped registers.

## Bitfields (Precise Bit Control)
- Used to simulate bit-level control like hardware registers:

```c
typedef struct {
    uint8_t RX_Ready : 1;
    uint8_t TX_Ready : 1;
    uint8_t Error    : 1;
    uint8_t Reserved : 5;
} UART_Status;

UART_Status status;
status.RX_Ready = 1;
```
- Only takes 8 bits in total!
- Used to model flag registers.

## Union with Bitfield Overlay
- A union lets you access the same memory in multiple ways.

```c
typedef union {
    struct {
        uint8_t EN   : 1;
        uint8_t MODE : 2;
        uint8_t INT  : 1;
        uint8_t      : 4; // reserved
    } bits;
    uint8_t value;
} ControlRegister;

ControlRegister reg;
reg.value = 0x00;
reg.bits.EN = 1;
reg.bits.MODE = 3;   // sets 2 bits
printf("CTRL: %02X\n", reg.value);  // Outputs: CTRL: 0D
```
- Helps build control registers for GPIO/UART/ADC.

## Struct Padding & Memory Layout
- Modern processors access memory faster when variables are aligned to their natural size boundaries (e.g., 4-byte variables aligned to 4-byte addresses).

- For example:
```c
typedef struct {
    char a;     // 1 byte
    int b;      // 4 bytes (aligned)
} MyStruct;
```

Even though a is 1 byte, the total size may be 8 bytes:
- a (1 byte) + 3 bytes padding
- b (4 bytes) 

Why padding(3 bytes) is added ?

- On 32-bit controllers, the CPU accesses memory in 32-bit (4-byte) chunks — aligned at addresses like 0x00, 0x04, 0x08, etc.
- If a char a is placed at 0x00 and an int b is placed immediately after at 0x01, the int spans 0x01–0x04.
- This is misaligned and would require two memory cycles to access.
- To avoid this, the compiler adds 3 padding bytes after char a, so int b starts at an aligned address 0x04.
- This ensures faster, single-cycle access — at the cost of a few extra bytes.

- Check:
```c
printf("Size = %lu\n", sizeof(MyStruct));  // Likely 8
```

- In firmware, padding matters when:
> - Designing communication packets
> - Accessing memory-mapped regions

## Packed Struct (Remove Padding)
- To avoid padding:
```c
typedef struct __attribute__((packed)) {
    char a;
    int b;
} PackedStruct;
```
- Use with caution:
> - Some compilers may not support packed
> - Can cause inefficient memory access, more CPU Cycles.

## Memory Mapping Registers with Structs
- You can define a struct to match hardware layout:
```c
typedef struct {
    uint32_t CTRL;
    uint32_t STATUS;
    uint32_t DATA;
} Peripheral;

#define PERIPH_BASE  0x40010000
#define PERIPH   ((volatile Peripheral *) PERIPH_BASE)

PERIPH->CTRL = 0x01;
```
- You now access registers using PERIPH->STATUS, etc.

### Struct Pointer Example (UART)
```c
typedef struct {
    uint32_t BAUD;
    uint8_t PARITY;
    uint8_t STOP_BITS;
} UART_Config;

UART_Config uart = {9600, 0, 1};
UART_Config *p = &uart;

printf("Baud: %d", p->BAUD);
```
- Used in drivers, initializations, and configs.

## Embedded Use Cases
| Feature | Firmware Use Case |
| ---- | ---- |
| struct | Group related config/data (e.g., sensor, GPIO) |
| Bitfield | Control or status registers |
| Union + Bitfield | Register + flag overlay |
| Packet Struct | Communication packet formatting |
| Struct Pointer | API for device driver interfact |

## Common Pitfalls & Tips
| Mistake/Tip | Details |
| ---- | ---- |
| ❌ Using . instead of -> | Use. for variable, -> for pointer |
| ❌ Assuming layout across platforms | Bitfield order is compiler-specific |
| ❌ Misaligned struct on hardware |	Leads to bus fault on some MCUs |
| ✅ Always use stdint.h types | uint8_t, uint16_t ensures exact sizes |
| ✅ Check sizeof() |	Helps verify memory layout |
| ✅ Avoid float inside hardware registers |	Use only integers for mapped structs |
