
#define swap(a,b,t) {t=a; a=b; b=t;}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize){
    int i, temp, *ans;
    for(i=0; i<numsSize; i++){
        while(nums[i] != i+1){  //if nums[i] is in wrong place, swap it to correct place
            if(nums[i] == nums[nums[i]-1])  //if cannot swap more
                break;
            swap(nums[nums[i]-1], nums[i], temp);   //the parameter should not be exchanged, or would get error because nums[i] were modified before accessing nums[nums[i]-1]
        }
    }
    *returnSize = 0;
    for(i=0; i<numsSize; i++){  //scan nums[], if there is a element in wrong place, that means the element corresponding to the place not in nums[]
        if(nums[i] != i+1)
            nums[(*returnSize)++] = i+1;    //move answer to front part of nums[]
    }
    ans = (int*)malloc(sizeof(int)*(*returnSize));
    for(i=0; i<*returnSize; i++)
        ans[i] = nums[i];
    return ans;
}