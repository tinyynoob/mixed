
/*-- according to https://leetcode.com/problems/single-element-in-a-sorted-array/discuss/1587588 --*/

int singleNonDuplicate(int* nums, int numsSize){
    int left, right, index;
    left = 0;
    right = numsSize-2;
    while(left <= right){
        index = (left+right)/2;
        if(nums[index] == nums[index^1])
            left = index+1;   //go right
        else
            right = index-1;  //go left
    }
    return nums[left];
}

