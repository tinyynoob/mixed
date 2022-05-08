

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    int left = 0, right = 0;
    *returnSize = numsSize - k + 1;
    int *ans = (int *) malloc(sizeof(int) * (*returnSize));
    ans[0] = nums[0];
    int max = nums[0], maxidx = 0;  // maxidx is chosen right-most
    for (int i = 1; i < k; i++) {
        right++;
        if (nums[right] >= max) {
            max = nums[right];
            maxidx = right;
        }
    }
    ans[0] = max;

    for (int i = 1; i < (*returnSize); i++) {
        right++;
        if (maxidx == left) {   // max is gone, need rescan
            max = nums[left + 1];
            for (int j = left + 1; j <= right; j++) {
                if (nums[j] >= max) {
                    max = nums[j];
                    maxidx = j;
                }
            }
        } else {
            if (nums[right] >= max) {
                max = nums[right];
                maxidx = right;
            }
        }
        ans[++left] = max;
    }
    return ans;
}