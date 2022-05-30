
int divide(int dividend, int divisor)
{
    const int sign = dividend >> 31 ^ divisor >> 31;
    // assume divisor != 0
    uint32_t dvd = (dividend < 0) ? ~(uint32_t) dividend + 1 : dividend;
    const uint32_t dvs = (divisor < 0) ? ~(uint32_t) divisor + 1 : divisor;
    
    int shift = 0;
    while (dvd > (dvs << shift) && (dvs << shift) < (1u << 31))
        shift++;
    uint32_t ans = 0;
    while (dvd >= dvs) {
        if (dvd >= (dvs << shift)) {
            ans |= 1u << shift;
            dvd -= dvs << shift;
        }
        shift--;
    }
    if (!sign && ans >= 1u << 31)
        return INT_MAX;
    return sign ? ~ans + 1 : ans;
}