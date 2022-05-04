//#include <stdio.h>


int findUnsortedSubarray(int* nums, int numsSize)
{
    int stop_increasing = -1;   // from left to right
    int min = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] <= min)
            min = nums[i];
        if (nums[i] < nums[i - 1] && stop_increasing == -1)
            stop_increasing = i;
    }
    //printf("stop_increasing is nums[%d] = %d\n", stop_increasing, nums[stop_increasing]);
    if (stop_increasing == -1)
        return 0;
    int rmin = nums[stop_increasing];
    for (int i = stop_increasing + 1; i < numsSize; i++) {
        if (nums[i] < rmin)
            rmin = nums[i];
    }
    int left = -1;
    if (min == nums[0]) {
        left = 0;
        for (int i = stop_increasing - 1; i >= 0; i--) {
            if (nums[i] <= rmin) {
                left = i;
                //printf("left = %d\n", left);
                break;
            }
        }
    }

    int stop_decreasing = -1;   // from right to left
    int max = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; i--) {
        if (nums[i] >= max)
            max = nums[i];
        if (nums[i] > nums[i + 1] && stop_decreasing == -1)
            stop_decreasing = i;
    }
    //printf("stop_decreasing is nums[%d] = %d\n", stop_decreasing, nums[stop_decreasing]);
    // stop_decreasing is impossible to be -1
    int lmax = nums[stop_decreasing];
    for (int i = stop_decreasing - 1; i >= 0; i--) {
        if (nums[i] > lmax)
            lmax = nums[i];
    }
    int right = numsSize;
    if (max == nums[numsSize - 1]) {
        right = numsSize - 1;
        for (int i = stop_decreasing + 1; i < numsSize; i++) {
            if (nums[i] >= lmax) {
                right = i;
                //printf("right = %d\n", right);
                break;
            }
        }
    }
    return right - left - 1;
}