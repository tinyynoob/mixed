#include <stdint.h>
#include <stdbool.h>


#include <limits.h>

int ilog(uint32_t v)
{
    int ret = v > 0;
    int m = (v > (uint32_t) 0xFFFFU) << 4;
    v >>= m;
    ret |= m;
    m = (v > 0xFFU) << 3;
    v >>= m;
    ret |= m;
    m = (v > 0xFU) << 2;
    v >>= m;
    ret |= m;
    m = (v > 0x3U) << 1;
    v >>= m;
    ret |= m;
    ret += (v > 1);
    return ret - 1;
}

int mySqrt(int x)
{
    uint32_t v = x;
    if (!v)
        return 0;
    int shift = (ilog(v) & ~1u);
    v -= (uint32_t) 1u << shift;
    int ans = 1;
    while (shift > 0) {
        shift -= 2;
        uint32_t sub = ((ans << 2) | 1) << shift;
        if (v >= sub) {
            v -= sub;
            ans = (ans << 1) + 1;
        } else {
            ans = ans << 1;
        }
    }
    return ans;
}

int countPrimes(int n)
{
    if (n <= 2)
        return 0;
    int ans = 1;    // prime 2
    bool *mark = (bool *) calloc(sizeof(bool), n >> 1); // build table only for odd numbers
    mark[0] = true;
    for (int i = 3; i <= mySqrt(n);) {
        mark[i >> 1] = true;
        if (i < INT_MAX / i + 1) { // to prevent overflow
            for (int j = i; i * j < n; j += 2)
                mark[(i * j) >> 1] = true;
        }
        ans++;
        while (i <= mySqrt(n) && mark[i >> 1])  // find next
            i += 2;
    }
    for (int i = (mySqrt(n) >> 1); i < (n >> 1); i++)
        if (!mark[i])
            ans++;
    free(mark);
    return ans;
}