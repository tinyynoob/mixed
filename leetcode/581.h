

int findUnsortedSubarray(int* nums, int numsSize)
{
    int left = -1, right = numsSize;    // interval (left, right)
    int min_from_left = 0;  // index
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] <= nums[i]) {
                min_from_left = j;
                goto calcmax;
            }
        }
        left++;
    }
calcmax:;
    int max_from_right = numsSize - 1;  // index
    int bound = left > min_from_left ? left : min_from_left;
    for (int i = numsSize - 1; i > bound; i--) {
        for (int j = i - 1; j; j--) {
            if (nums[j] >= nums[i]) {
                max_from_right = j;
                goto ret;
            }
        }
        right--;
    }
ret:;
    return right - left - 1;
}