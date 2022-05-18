#include <stdint.h>
#include <stdbool.h>


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


bool isPrime (int n)
{
    for (int i = 2; i <= mySqrt(n); i++)
        if (!(n % i))
            return false;
    return true;
}

int countPrimes(int n)
{
    int ans = 0;
    if (n > 2)
        ans++;
    for (int i = 3; i < n; i += 2)
        if (isPrime(i))
            ans++;
    return ans;
}