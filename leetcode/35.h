

int searchInsert(int* nums, int numsSize, int target)
{
    /* [left, right] */
    int left = 0, right = numsSize - 1;
    int mid;
    while (left <= right) {
        mid = ((left ^ right) >> 1) + (left & right);
        if (nums[mid] < target)
            left = mid + 1;
        else if (nums[mid] > target)
            right = mid - 1;
        else if (nums[mid] == target)
            return mid;
    }
    if (target > nums[mid])
        return mid + 1;
    else
        return mid;
}