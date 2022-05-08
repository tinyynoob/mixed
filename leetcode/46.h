#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

struct perm {
    int *nums;
    int numsSize;
    int **result;
    int res_used;
    int *seq;   // seq[i] \in [0, numsSize)
    int checksum;   // \sum_i (seq[i] + 3) * (seq[i] + 3)
};
/* The equation of checksum may be choosed better to prevent conflict with wrong results.
 *
 */

static inline bool isValid(int *sequence, int seqSize, int checksum)
{
    for (int i = 0; i < seqSize; i++)
        checksum -= (sequence[i] + 3) * (sequence[i] + 3);
    return !checksum;
}

static void generate_permute(struct perm *p, int pos)
{
    if (pos == p->numsSize) {   // end recursion
        if (!isValid(p->seq, p->numsSize, p->checksum))
            return;
        ++(p->res_used);
        for (int j = 0; j < p->numsSize; j++)
            printf("%d ", p->seq[j]);
        printf("is the %d-th order\n", p->res_used);
        for (int i = 0; i < p->numsSize; i++)
            p->result[p->res_used][i] = p->nums[p->seq[i]];
        return;
    }

    for (int i = 0; i < p->numsSize; i++) {
        p->seq[pos] = i;
        generate_permute(p, pos + 1);
    }
}

static struct perm *perm_init(int *nums, int numsSize, int resSize)
{
    struct perm *p = (struct perm *) malloc(sizeof(struct perm));
    p->nums = nums;
    p->numsSize = numsSize;
    p->result = (int **) malloc(sizeof(int *) * resSize);
    for (int i = 0; i < resSize; i++)
        p->result[i] = (int *) malloc(sizeof(int) * numsSize);
    p->res_used = -1;
    p->seq = (int *) malloc(sizeof(int) * numsSize);
    p->checksum = 0;
    for (int i = 0; i < numsSize; i++) {
        p->seq[i] = 0;
        p->checksum += (i + 3) * (i + 3);
    }
    return p;
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 1;
    for (int i = 1; i <= numsSize; i++)
        (*returnSize) *= i;
    struct perm *p = perm_init(nums, numsSize, *returnSize);
    generate_permute(p, 0);
    int **ans = p->result;
    free(p->seq);
    free(p);

    (*returnColumnSizes) = (int *) malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < (*returnSize); i++)
        (*returnColumnSizes)[i] = numsSize;
    return ans;
}