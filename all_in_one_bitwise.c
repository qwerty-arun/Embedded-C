#include <stdio.h>
#include <stdint.h>

#define LOWER_NIBBLE(reg) ((reg) & 0x0F)
#define UPPER_NIBBLE(reg) ((reg >> 4) & 0x0F)

#define SET_BIT(reg, pos) ((reg) |= (1 << (pos)))
#define CLEAR_BIT(reg, pos) ((reg) &= ~(1 << (pos)))
#define TOGGLE_BIT(reg, pos) ((reg) ^= (1 << (pos)))
#define READ_BIT(reg, pos) (((reg) >> (pos)) & 1U)

#define SET_BIT_FIELD(reg, len, pos) ((reg) |= ((1 << (len))-1) << pos)
#define EXTRACT_BIT_FIELD(reg, len, pos) (reg >> pos) & ((1 << len)-1)
#define CLEAR_BIT_FIELD(reg, len, pos) (reg = (reg) & ~((1 << len)-1 << pos))
#define REPLACE_BIT_FIELD(reg, val, len, pos) (reg = (reg & ~(((1 << len)-1) << pos)) | (val << pos))

#define SET_ENABLE(x) ((x & 0x01) << 0) // Bit 0
#define SET_MODE(x) ((x & 0x03) << 1) // Bit 1-2
#define SET_SPEED(x) ((x & 0x05) << 3) // Bit 3-5

#define LEFT_ROTATION_8_BIT(reg, n) ((reg << n) | (reg >> (8-n)));
#define RIGHT_ROTATION_8_BIT(reg, n) ((reg >> n) | (reg << (8-n)));

#define LEFT_ROTATION_16_BIT(reg, n) ((reg << n) | (reg >> (16-n)));
#define RIGHT_ROTATION_16_BIT(reg, n) ((reg >> n) | (reg << (16-n)));

#define LEFT_ROTATION_32_BIT(reg, n) ((reg << n) | (reg >> (32-n)));
#define RIGHT_ROTATION_32_BIT(reg, n) ((reg >> n) | (reg << (32-n)));

#define POWER_OF_TWO(n) (n>0 && (n & (n-1))==0)

int count_set_bits(int n){
    int count = 0;
    while(n){
        count += (n&1);
        n >>= 1;
    }
    return count;
}

uint8_t bit_reversal(uint8_t reg){
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result <<= 1; // Shift left to make room for next bit
        result |= (reg & 1); // Take LSB and add to result
        reg >>= 1; // Shift input right and process next bit
    }
    return result;
}

int main()
{
    uint8_t reg = 3;
    printf("%d", POWER_OF_TWO(reg));
    return 0;
}