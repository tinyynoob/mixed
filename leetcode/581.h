

int findUnsortedSubarray(int* nums, int numsSize)
{
    int left = -1, right = numsSize;    // interval (left, right)
    int min_from_left = 0;  // index
    for (int i = 0; i < numsSize; i++) {
        int repeat = i;
        int cut_flag = 0;   // lock update of repeat
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] < nums[i]) {
                min_from_left = j;
                goto calcmax;
            } else if (nums[j] == nums[i] && !cut_flag) {
                repeat = j;
            } else {
                cut_flag = 1;
            }
        }
        left = repeat;
    }
calcmax:;
    int bound = left > min_from_left ? left : min_from_left;
    for (int i = numsSize - 1; i > bound; i--) {
        int repeat = i;
        int cut_flag = 0;   // lock update of repeat
        for (int j = i - 1; j >= 0; j--) {
            if (nums[j] > nums[i])
                goto ret;
            else if (nums[j] == nums[i] && !cut_flag)
                repeat = j;
            else
                cut_flag = 1;
        }
        i = repeat;
        right = repeat;
    }
ret:;
    return right - left - 1;
}