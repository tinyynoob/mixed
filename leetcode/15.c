
/*-----use the result of 912-----*/

#define swap(a,b,temp) {temp=a; a=b; b=temp;}

int* sortArray(int* nums, int numsSize);
void quicksort(int *nums, const int left, const int right);
void insertionSort(int *nums, const int left, const int right);

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int i, flag, left, index, right, sum, allocSize;
    int **ans;
    
    *returnSize = 0;
    if(numsSize < 3)
        return NULL;
    
    nums = sortArray(nums, numsSize);

    flag = 0;
    allocSize = 256;
    ans = (int**)malloc(sizeof(int*)*allocSize);
    *returnColumnSizes = (int*)malloc(sizeof(int)*allocSize);
    for(index=1; index<numsSize-1; index++){
        if(index>1 && nums[index]==nums[index-1]){
            continue;
        }
        
        left = index-1;
        right = index+1;
        while(left>=0 && right<numsSize){
            sum = nums[left]+nums[index]+nums[right];
            if(sum>0)
                left--;
            else if(sum<0)
                right++;
            else{   // an answer is found
                if(*returnSize == allocSize){   //if the allocated space is full
                    allocSize+= 256;
                    ans = (int**)realloc(ans, sizeof(int*)*allocSize);
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int)*allocSize);
                }
                (*returnColumnSizes)[*returnSize] =  3;
                ans[*returnSize] = (int*)malloc(sizeof(int)*3);
                ans[*returnSize][0] = nums[left];
                ans[*returnSize][1] = nums[index];
                ans[*returnSize][2] = nums[right];
                (*returnSize)++;
                do{
                    left--;
                }while(left>=0 && nums[left]==nums[left+1]);
                // do{
                //     right++;
                // }while(right<numsSize && nums[right]==nums[right-1]);
            }
        }
    }
    return ans;
}


/*-----the contents below is copied from 912 and modify a little-----*/

int* sortArray(int* nums, int numsSize){
    if(nums)
        quicksort(nums, 0, numsSize-1);
    return nums;
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
