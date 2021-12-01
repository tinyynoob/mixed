
#define max(a,b) (a>b?a:b)

int rob(int* nums, int numsSize){
    int i;
    if(numsSize == 1)
        return nums[0];
    
    nums[1] = max(nums[0], nums[1]);
    if(numsSize == 2)
        return nums[1];
    
    for(i=2; i<numsSize; i++)
        nums[i] = max(nums[i-1], nums[i-2]+nums[i]);
    return nums[numsSize-1];
}