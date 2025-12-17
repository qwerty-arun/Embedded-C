// Validate Configureation Register Layout

/*
You are given a ConfigRegister struct that simulates a 16-bit configuration register.
Each bit in the register has a specific meaning:

Bit Position	Meaning
0	            Enable (1 = ON)
1	            Mode (0 = Normal, 1 = Safe)
2–3	            Priority (00 = Low, 01 = Medium, 10 = High, 11 = Invalid)
4–15	        Reserved (must be 0)

Your task is to validate the register:

- Return 1 if:
    - Bit 0 is set (Enable ON)
    - Bits 2–3 contain a valid priority (not 11)
    - All bits 4–15 are 0
- Return 0 otherwise
Use pointer logic (-> or (*ptr).field) to access the data.

Example-1
Input: reg = 0x0005 (binary: 0000000000000101)
Output: 1
(Enable = 1, Mode = 0, Priority = 01 → Valid)

Example-2
Input: reg = 0x000B (binary: 0000000000001011)
Output: 1

Example-3
Input: reg = 0x0015 (binary: 0000000000010101)
Output: 0
(Bit 4 is set → Reserved violation)
*/

#include <stdio.h>

typedef struct {
    unsigned short reg;
} ConfigRegister;

int validate_config(ConfigRegister *cfg) {
    // Write logic using pointer access
    if((cfg->reg & 1) && (((cfg->reg & (1 << 2)) & (cfg->reg & (1 << 3))) != 1) && (cfg->reg & 0xFFF0) == 0)
    {
        return 1;
    }
    return 0;
}

/*
int validate_config(ConfigRegister *cfg) {
    unsigned short value = (*cfg).reg;

    // Check if Enable bit is set (bit 0)
    if ((value & 0x0001) == 0)
        return 0;

    // Extract priority (bits 2–3)
    unsigned short priority = (value >> 2) & 0x03;
    if (priority == 0x03)  // Invalid priority
        return 0;

    // Check reserved bits (bits 4–15) are all 0
    if ((value & 0xFFF0) != 0)
        return 0;

    return 1;
}
*/

int main() {
    ConfigRegister cfg;
    scanf("%hx", &cfg.reg);

    int result = validate_config(&cfg);
    printf("%d", result);

    return 0;
}