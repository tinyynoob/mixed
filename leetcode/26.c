

int removeDuplicates(int* nums, int numsSize){
    int index, current, flag, count;
    
    index = 0;
    count = 0;
    while(index<numsSize){
        current = nums[index++];
        flag = 0;
        while(!flag && index<numsSize){
            if(nums[index]==current)    //if repeated, go next
                index++;
            else
                flag = 1;
        }
        nums[count++] = current;
    }
    return count;
}