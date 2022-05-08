#include "46.h"

int main()
{
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int size;
    int *retColSize;
    int **y = permute(nums, sizeof(nums)/sizeof(int), &size, &retColSize);
    for (int i = 0; i < size; i++)
        free(y[i]);
    free(y);
    free(retColSize);
    return 0;
}