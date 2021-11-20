

int singleNonDuplicate(int* nums, int numsSize){
    int left, right, index, type;
    if(numsSize == 1)
        return nums[0];
    left = 0;
    right = numsSize-1;
    while(right-left > 2){
        index = (left+right)/2;
        type = index&1; //mod 2
        if((type==0&&nums[index]==nums[index-1])||(type==1&&nums[index]==nums[index+1]))
            right = index;  //go left
        else if((type==0&&nums[index]==nums[index+1])||(type==1&&nums[index]==nums[index-1]))
            left = index;   //go right
        else
            return nums[index];    //the answer is found
    }
    
    if(right-left == 2){    // 3 numbers remain
        if(nums[left] == nums[left+1])
            return nums[right];
        else if(nums[right] == nums[right-1])
            return nums[left];
        else
            return nums[left+1];
    }
    //2 numbers remain. this case only happens at boundary.
    else if(left==0)    //the two leftmost numbers remain
        return nums[left];  //it must not be nums[left+1], or there will be two answer
    else                //the two rightmost numbers remain
        return nums[right];
}

