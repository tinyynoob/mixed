/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j, gap, *ans;
    //returnSize = (int*)malloc(sizeof(int));
    for(i=0; i<numsSize-1; i++){
        gap = target-nums[i];
        for(j=i+1; j<numsSize; j++){
            if(nums[j]==gap){
                ans = (int*)malloc(sizeof(int)*2);
                ans[0] = i;
                ans[1] = j;
                *returnSize = 2;
                return ans;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}