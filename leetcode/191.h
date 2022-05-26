int hammingWeight(uint32_t n)
{
    int ans = 0;
    for (uint32_t i = 1; i; i <<= 1)
        if (n & i)
            ans++;
    return ans;
}