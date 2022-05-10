

int lengthOfLIS(int* nums, int numsSize)
{
    int dp[numsSize];
    dp[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        int max = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (nums[i] > nums[j] && dp[j] + 1 > max)
                max = dp[j] + 1;
        }
        dp[i] = max;
    }
    int ans = 0;
    for (int i = 0; i < numsSize; i++)
        if (dp[i] > ans)
            ans = dp[i];
    return ans;
}