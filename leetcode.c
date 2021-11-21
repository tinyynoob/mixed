#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap(a,b,t) {t=a; a=b; b=t;}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
int* sortArray(int* nums, int numsSize);
void quicksort(int *nums, const int left, const int right);
void insertionSort(int *nums, const int left, const int right);

int main()
{
    int i, *p, **pp;
    int a[10]={-1,0,1,-1,-2,-4};
    p = (int*)malloc(sizeof(int));
    pp = (int**)malloc(sizeof(int*));
    threeSum(a, 6, p, pp);
    system("pause");
    return 0;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int i, flag, left, index, right, sum;
    int **ans;

    ans = NULL;
    *returnSize = 0;
    if(!numsSize)
        return ans;
    
    nums = sortArray(nums, numsSize);

    ans = (int**)malloc(sizeof(int*)*200);  //guess a max size
    *returnColumnSizes = (int*)malloc(sizeof(int)*200);
    
    for(index=1; index<numsSize-1; index++){
        left = index-1;
        right = index+1;
        while(left>=0 && right<numsSize){
            sum = nums[left]+nums[index]+nums[right];
            if(sum>0){
                left--;
                continue;
            }
            else if(sum<0){
                right++;
                continue;
            }
            else{   // an answer is found
                // flag = 0;
                // for(i=0; i<*returnSize; i++){   //if this triplet is duplicate, skip it
                //     if(nums[left]==ans[i][0] && nums[index]==ans[i][1] && nums[right]==ans[i][2]){
                //         flag = 1;
                //         break;
                //     }
                // }
                // if(flag)
                //     continue;
                (*returnColumnSizes)[*returnSize] =  3;
                ans[*returnSize] = (int*)malloc(sizeof(int)*3);
                ans[*returnSize][0] = nums[left];
                ans[*returnSize][1] = nums[index];
                ans[*returnSize][2] = nums[right];
                (*returnSize)++;
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


