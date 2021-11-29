

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    int i, *fromLeft, fromRight;
    fromLeft = (int*)malloc(sizeof(int)*numsSize);
    fromLeft[0] = nums[0];
    for(i=1; i<numsSize-1; i++)
        fromLeft[i] = fromLeft[i-1]*nums[i];
    /*-- start to generate ans --*/
    fromRight = nums[numsSize-1];
    fromLeft[numsSize-1] = fromLeft[numsSize-2];
    for(i=numsSize-2; i>0; i--){
        fromLeft[i] = fromLeft[i-1]*fromRight;
        fromRight*= nums[i];
    }
    fromLeft[0] = fromRight;
    *returnSize = numsSize;
    return fromLeft;
}