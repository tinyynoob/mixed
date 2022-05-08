#include <stdio.h>
#include <stdint.h>


static inline int ilog32(uint32_t v)
{
    uint32_t ans = v > 0;
    int m = (v > 0xFFFFU) << 4;
    v >>= m;
    ans |= m;
    m = (v > 0xFFU) << 3;
    v >>= m;
    ans |= m;
    m = (v > 0xFU) << 2;
    v >>= m;
    ans |= m;
    m = (v > 0x3u) << 1;
    v >>= m;
    ans |= m;
    ans += (v > 1);
    return ans;
}

int coinChange(int* coins, int coinsSize, int amount)
{
    int max = 0;    // max value among the coins
    for (int i = 0; i < coinsSize; i++)
        if (coins[i] > max)
            max = coins[i];
    const unsigned size = 1u << ilog32(max);
    int table[size];
    table[0] = 0;
    for (unsigned curr = 1; curr < amount + 1; curr++) {
        const unsigned curridx = curr & (size - 1);
        table[curridx] = -1;
        for (int i = 0; i < coinsSize; i++) {
            const unsigned preidx = (curr - coins[i]) & (size - 1);
            if ((int) curr - coins[i] < 0)
                continue;
            else if (table[preidx] == -1)
                continue;
            else if (table[curridx] == -1)
                table[curridx] = table[preidx] + 1;
            else if (table[preidx] + 1 < table[curridx])
                table[curridx] = table[preidx] + 1;
        }
    }
    return table[amount & (size - 1)];
}