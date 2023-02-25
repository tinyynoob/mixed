/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))

int** intervalIntersection(int** firstList, int firstListSize, int* firstListColSize, int** secondList, int secondListSize, int* secondListColSize, int* returnSize, int** returnColumnSizes)
{
    int sz = firstListSize + secondListSize - 1;
    int **ans = (int **) malloc(sizeof(int *) * sz);

    int ansidx = 0;    
    for (int idx1 = 0, idx2 = 0; idx1 < firstListSize && idx2 < secondListSize;) {
        const int left = max(firstList[idx1][0], secondList[idx2][0]);
        if (left > firstList[idx1][1]) {
            idx1++;
            continue;
        } else if (left > secondList[idx2][1]) {
            idx2++;
            continue;
        }
        const int right = min(firstList[idx1][1], secondList[idx2][1]);
        ans[ansidx] = (int *) malloc(sizeof(int) * 2);
        ans[ansidx][0] = left;
        ans[ansidx][1] = right;
        ansidx++;
        idx1 = (right == firstList[idx1][1]) ? idx1 + 1 : idx1;
        idx2 = (right == secondList[idx2][1]) ? idx2 + 1 : idx2;
    }
    *returnSize = ansidx;
    *returnColumnSizes = (int *) malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 2;
    return ans;
}