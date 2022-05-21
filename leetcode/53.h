
#define max(a, b) ((a > b) ? (a) : (b))


int maxSubArray(int* nums, int numsSize){
    int dp[2];
    dp[0] = nums[0];
    int mmax = dp[0];
    for (int i = 1; i < numsSize; i++) {
        dp[i & 1] = max(nums[i], nums[i] + dp[(i & 1) ^ 1]);
        if (dp[i & 1] > mmax)
            mmax = dp[i & 1];
    }
    return mmax;
}