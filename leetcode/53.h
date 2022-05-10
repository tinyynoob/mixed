
#define max(a,b) ((a > b) ? (a) : (b))


int maxSubArray(int* nums, int numsSize){
    int dp[numsSize];
    dp[0] = nums[0];
    int mmax = dp[0];
    for (int i = 1; i < numsSize; i++) {
        dp[i] = max(nums[i], nums[i] + dp[i - 1]);
        if (dp[i] > mmax)
            mmax = dp[i];
    }
    return mmax;
}