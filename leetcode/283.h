

void moveZeroes(int* nums, int numsSize){
    int count = 0;
    for (int i = 0; i < numsSize; i++)
        if (!nums[i])
            count++;
    int index = 0;
    for (int i = 0; i < numsSize; i++)
        if (nums[i])
            nums[index++] = nums[i];
    while (index < numsSize)
        nums[index++] = 0;
}