//implement by quicksort algorithm

#define swap(a,b) {temp=a; a=b; b=temp;}

void quicksort(int *nums, int left, int right);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize){
    int i, *ans;
    ans = (int*)malloc(sizeof(int)*numsSize);
    for(i=0; i<numsSize; i++)
        ans[i] = nums[i];
    quicksort(ans, 0, numsSize-1);
    *returnSize = numsSize;
    return ans;
}

void quicksort(int *nums, int left, int right){
    int temp, i, j;
    if(left>=right)
        return;
    /*
    i<=j always
    i will stay at bigger num, and j keeps moving right to find a smaller num, if find, swap(nums[i],nums[j])
    At the end, swap(nums[i],nums[right])
    */
    i = left;
    for(j=left; j<right; j++){
        if(nums[j]<=nums[right]){
            swap(nums[i], nums[j]);
            i++;
        }
    }
    swap(nums[i],nums[right]);
    quicksort(nums, left, i-1);
    quicksort(nums, i+1, right);
}