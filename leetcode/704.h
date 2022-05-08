

int search(int* nums, int numsSize, int target)
{
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        const int mid = ((left ^ right) >> 1) + (left & right);
        if (target < nums[mid])
            right = mid - 1;
        else if (target > nums[mid])
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}