#include <stdlib.h>
#include <stdint.h>


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// range of n cannot be larger than UINT32_MAX
static inline int count_one(int n)
{
    int ans = 0;
    for (uint32_t x = n; x; x >>= 1)
        if (x & 1)
            ans++;
    return ans;
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 1 << numsSize;
    int **ans = (int **) malloc(sizeof(int *) * (*returnSize));
    *returnColumnSizes = (int *) malloc(sizeof(int) * (*returnSize));
    unsigned select = 0;
    for (int i = 0; i < *returnSize; i++) {
        int setbits = count_one(select);
        (*returnColumnSizes)[i] = setbits;
        ans[i] = (int *) malloc(sizeof(int) * setbits);
        int index = 0;
        for (uint32_t j = 0; j < numsSize; j++) {
            if (select & (1u << j))
                ans[i][index++] = nums[j];
        }
        select++;
    }
    return ans;
}