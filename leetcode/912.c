//implement by quicksort mixing insertion sort

#define swap(a,b,temp) {temp=a; a=b; b=temp;}

void quicksort(int *nums, const int left, const int right);
void insertionSort(int *nums, const int left, const int right);

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

void quicksort(int *nums, const int left, const int right){
    int temp, i, j, mid, pivotIndex;
    if(left>=right)
        return;
    else if(right-left <= 20)   //if too few elements, change to insertion sort
        insertionSort(nums, left, right);
    else{
        /*select the median of {nums[left], nums[mid], nums[right]} as pivot*/
        mid = (left+right)/2;
        if(nums[left]>nums[mid]&&nums[mid]>nums[right])
            pivotIndex = mid;
        else if(nums[right]>nums[mid]&&nums[mid]>nums[left])
            pivotIndex = mid;
        else if(nums[right]>nums[left]&&nums[left]>nums[mid])
            pivotIndex = left;
        else if(nums[mid]>nums[left]&&nums[left]>nums[right])
            pivotIndex = left;
        else
            pivotIndex = right;
        swap(nums[pivotIndex], nums[right], temp);     //put pivot on right
        /*end selecting pivot*/
        
        /*
        i<=j always
        i will stay at bigger num, and j keeps moving right to find a smaller num, if find, swap(nums[i],nums[j])
        At the end, swap(nums[i],nums[right])
        */
        i = left;
        for(j=left; j<right; j++){
            if(nums[j]<=nums[right]){
                swap(nums[i], nums[j], temp);
                i++;
            }
        }
        swap(nums[i], nums[right], temp);
        quicksort(nums, left, i-1);
        quicksort(nums, i+1, right);
    }
}

void insertionSort(int *nums, const int left, const int right){
    int i, j, smallerNum;
    if(left>=right)
        return;
    for(i=left+1; i<=right; i++){
        if(nums[i]<nums[i-1]){
            smallerNum = nums[i];
            for(j=i-1; j>=left&&smallerNum<nums[j]; j--)
                nums[j+1] = nums[j];
            nums[j+1] = smallerNum;
        }
    }
}

