/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h> // qsort()

int intv_st_cmp(const void *a, const void *b)
{
    const int former = ((int *) *(__intptr_t *) a)[0];
    const int later = ((int *) *(__intptr_t *) b)[0];
    return (former < later) ? -1 :
            (former > later) ? 1 :
                0;
}

/*
int intv_en_cmp(const void *a, const void *b)
{
    const int former = ((int *) *(__intptr_t *) a)[1];
    const int later = ((int *) *(__intptr_t *) b)[1];
    return (former < later) ? -1 :
            (former > later) ? 1 :
                0;
}
*/

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes)
{
    // pre sort by start
    qsort(intervals, intervalsSize, sizeof(int) * 2, intv_st_cmp);
    /*
    int stidx = 0, stnum = intervals[stidx][0];
    for (int index = 1; index < intervalsSize; index++) {
        if (intervals[index][0] == stnum)
            continue;
        qsort(intervals + stidx, index - stidx, sizeof(int) * 2, intv_en_cmp);
        stidx = index;
        stnum = intervals[stidx][0];
    }
    qsort(intervals + stidx, intervalsSize - stidx, sizeof(int) * 2, intv_en_cmp);
    */

    // in-place
    int ansidx = 0;
    intervals[ansidx][0] = intervals[0][0];
    int right = intervals[0][1];
    for (int index = 1; index < intervalsSize; index++) {
        if (intervals[index][0] > right) {  // new segment
            intervals[ansidx][1] = right;
            intervals[++ansidx][0] = intervals[index][0];
            right = intervals[index][1];
        } else {    // merge to prev
            if (intervals[index][1] > right)  // update right bound
                right = intervals[index][1];
        }
    }
    intervals[ansidx][1] = right;
    ansidx++;

    *returnSize = ansidx;
    int **ans = (int **) malloc(sizeof(int *) * (*returnSize));
    (*returnColumnSizes) = (int *) malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        ans[i] = (int *) malloc(sizeof(int) * 2);
        (*returnColumnSizes)[i] = 2;
        ans[i][0] = intervals[i][0];
        ans[i][1] = intervals[i][1];
    }

    return ans;
}

int main()
{
#define ARRSZ 4
    int intervals[ARRSZ][2] = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    int **intv = (int **) malloc(sizeof(int *) * ARRSZ);
    for (int i = 0; i < ARRSZ; i++) {
        intv[i] = (int *) malloc(sizeof(int) * 2);
        intv[i][0] = intervals[i][0];
        intv[i][1] = intervals[i][1];
    }

    int sz, *colsz;
    int **ret = merge(intv, ARRSZ, NULL, &sz, &colsz);

    printf("\n[");
    for (int i = 0; i < sz; i++)
        printf("[%d, %d],", ret[i][0], ret[i][1]);
    printf("]\n");

    for (int i = 0; i < ARRSZ; i++)
        free(intv[i]);
    for (int i = 0; i < sz; i++)
        free(ret[i]);
    free(intv);
    free(ret);
    free(colsz);
    return 0;
}

