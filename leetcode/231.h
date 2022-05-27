

bool isPowerOfTwo(int n)
{
    return n && !(n >> 31) && !(n & (n - 1));
}