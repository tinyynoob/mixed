

int longestSubarray(int* nums, int numsSize)
{
    int *encode = (int *) malloc(sizeof(int) * (numsSize + 2));
    encode[0] = -1;
    int encidx = 1;
    int setcount = 0;
    for (int nidx = 0; nidx < numsSize; nidx++) {
        if (nums[nidx]) {
            setcount++;
        } else if (setcount) {
            encode[encidx++] = setcount;
            setcount = 0;
        } else if (encode[encidx - 1] != 0) {
            encode[encidx++] = 0;
        }
    }
    encode[encidx++] = setcount;
    encode[encidx] = -1;    // mark the end
    
    int max = 0;
    for (int i = 1; i <= encidx; i++) {
        int l = encode[i - 1] + encode[i];
        if (l > max)
            max = l;
    }
    free(encode);
    return max;
}