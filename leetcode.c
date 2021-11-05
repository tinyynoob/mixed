#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap(a,b) {temp=a; a=b; b=temp;}

void quicksort(int *nums, int left, int right);

int main()
{
    
    int i, numsSize, *nums, *ans;
    numsSize = 2;
    nums = (int*)malloc(sizeof(int)*numsSize);
    nums[0] = 7;
    nums[1] = 6;
    ans = (int*)malloc(sizeof(int)*numsSize);
    quicksort(nums, 0, numsSize-1);
    //returnSize = (int*)malloc(sizeof(int));
    //*returnSize = numsSize;
    for(i=0; i<numsSize; i++)
        ans[i] = nums[i];
    for(i=0; i<numsSize; i++)
        printf("%d\t",ans[i]);
    system("pause");
    return 0;
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
            swap(nums[i],nums[j]);
            i++;
        }
    }
    swap(nums[i],nums[right]);
    quicksort(nums, left, i-1);
    quicksort(nums, i+1, right);
}



