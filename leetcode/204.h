#include <stdint.h>
#include <stdbool.h>


int countPrimes(int n)
{
    if (n <= 1)
        return 0;
    int ans = 0;
    bool *mark = (bool *) calloc(sizeof(bool), n);
    mark[0] = true;
    mark[1] = true;
    for (int i = 2; i < n;) {
        for (int j = 1; i * j < n; j++)
            mark[i * j] = true;
        ans++;
        while (i < n && mark[i])  // find next
            i++;
    }
    free(mark);
    return ans;
}