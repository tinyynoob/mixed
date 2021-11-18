#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap(a,b,t) {t=a; a=b; b=t;}

int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize);

int main()
{
    int i, *p;
    int a[10]={4,3,2,7,8,2,3,1};
    findDisappearedNumbers(a,8,p);
    system("pause");
    return 0;
}

int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize){
    int i, temp, counter, *ans;
    counter = 0;
    for(i=0; i<numsSize; i++){
        while(nums[i] != i+1){
            if(nums[i] == nums[nums[i]-1]){
                counter++;
                break;
            }
            swap(nums[nums[i]-1], nums[i], temp);   //swap to where it should be
        }
    }
    ans = (int*)malloc(sizeof(int)*counter);
    //*returnSize = counter;
    counter = 0;
    for(i=0; i<numsSize; i++){
        if(nums[i] != i+1)
            ans[counter++] = i+1;
    }
    return ans;
}

