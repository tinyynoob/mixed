

bool canJump(int *nums, int numsSize)
{
    if (numsSize == 1)
        return true;
    int curr = 0, going = 1;
    while (nums[curr] != 0) {
        int reachable = curr, rindex = curr;
        for (; going <= curr + nums[curr]; going++) {
            int sum = going + nums[going];
            if (sum >= reachable) {  // move as far as it can
                reachable = sum;
                rindex = going;
                if (reachable >= (numsSize - 1))
                    return true;
            }
        }
        curr = rindex;
    }
    return false;
}