

int findUnsortedSubarray(int* nums, int numsSize)
{
    int right = -2;
    int max = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] >= max)
            max = nums[i];
        else
            right = i;
    }
    int left = -1;
    int min = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; i--) {
        if (nums[i] <= min)
            min = nums[i];
        else
            left = i;
    }
    // if one of left or right is changed, another must also be changed.
    return right - left + 1;
}