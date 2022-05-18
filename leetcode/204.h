#include <stdint.h>
#include <stdbool.h>


#include <limits.h>

int countPrimes(int n)
{
    if (n <= 1)
        return 0;
    int ans = 0;
    bool *mark = (bool *) calloc(sizeof(bool), n);
    mark[0] = true;
    mark[1] = true;
    for (int i = 2; i < n;) {
        mark[i] = true;
        if (i < INT_MAX / i + 1) { // to prevent overflow
            for (int j = i; i * j < n; j++)
                mark[i * j] = true;
        }
        ans++;
        while (i < n && mark[i])  // find next
            i++;
    }
    free(mark);
    return ans;
}

