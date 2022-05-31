#include <stdint.h>

int hammingWeight(uint32_t n)
{
    uint32_t tmp = (n & 0x88888888u) >> 3;
    tmp += (n & 0x44444444u) >> 2;
    tmp += (n & 0x22222222u) >> 1;
    tmp += (n & 0x11111111u);
    return (tmp >> 28) + ((tmp >> 24) & 0xFu)
            + ((tmp >> 20) & 0xFu) + ((tmp >> 16) & 0xFu)
            + ((tmp >> 12) & 0xFu) + ((tmp >> 8) & 0xFu)
            + ((tmp >> 4) & 0xFu) + (tmp & 0xFu);
}