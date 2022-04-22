

bool canJump(int* nums, int numsSize){
    if (numsSize == 1)
        return true;
    int curr = 0;
    while (nums[curr] != 0) {
        int max = curr, mindex = curr;
        for (int i = 1; i <= nums[curr]; i++) {
            int sum = curr + i + nums[curr + i];
            if (sum >= max) {   // move as far as it can
                max = sum;
                if (max >= (numsSize - 1))
                    return true;
                mindex = curr + i;
            }
        }
        curr = mindex;
    }
    return false;
}