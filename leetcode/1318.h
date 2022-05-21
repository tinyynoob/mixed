

static inline int count_set(uint32_t x)
{
    int ans = 0;
    for (uint32_t i = 1; i; i <<= 1)
        if (x & i)
            ans++;
    return ans;
}

int minFlips(int a, int b, int c)
{
    int ans = count_set(a & b & ~c) << 1;
    ans += count_set(a & ~b & ~c);
    ans += count_set(~a & b & ~c);
    ans += count_set(~a & ~b & c);
    return ans;
}