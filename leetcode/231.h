#include <stdbool.h>


bool isPowerOfTwo(int n)
{
    unsigned u = n;
    // need to block 0 and INT_MIN, which is 100...00
    return !(u & (u - 1)) & !(u >> 31) & !((u - 1) >> 31);
}