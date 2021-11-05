#define swap(a,b) {temp=a; a=b; b=temp;}

void quicksort(int *nums, int left, int right);

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int **ans;
    int left, mid, right, i, target;
    ans = NULL;
    if(numsSize<=2){
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return ans;
    }
    
    quicksort(nums, 0, numsSize-1);
    //numsSize = removeDuplicates(nums, numsSize);
    
    ans = (int**)malloc(sizeof(int*)*5*numsSize);
    for(i=0; i<3; i++)
        ans[i] = (int*)malloc(sizeof(int)*3);
    
    *returnSize = 0;
    left = 0;
    while(left<numsSize-2){ //left
        target = 0-nums[left];
        for(mid=left+1, right=numsSize-1; mid<right; mid=left+1){   //right
            if(target > 2*nums[right])
                break;
            while(mid<right){   //mid
                if(nums[mid]+nums[right]==target){      //if an answer found
                    ans[*returnSize][0] = nums[left];
                    ans[*returnSize][1] = nums[mid];
                    ans[*returnSize][2] = nums[right];
                    (*returnSize)++;
                }
                while(nums[mid]==nums[mid+1] && nums[mid+1])
                    mid++;
                mid++;
            }
            while(nums[right]==nums[right-1] && nums[right-1])
                right--;
            right--;
        }
        while(nums[left]==nums[left+1] && nums[left+1])
            left++;
        left++;
    }
    
    *returnColumnSizes = (int*)malloc(sizeof(int)*(*returnSize));
    for(i=0; i<*returnSize; i++)
        (*returnColumnSizes)[i] = 3;
    return ans;
}


void quicksort(int *nums, int left, int right){
    int temp, i, j;
    if(left>=right)
        return;

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
