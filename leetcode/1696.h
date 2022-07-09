

int maxResult_dp(int *nums, int numsSize, int k);

int maxResult(int* nums, int numsSize, int k)
{
    int ans = nums[0], curr = 0;
loop:;
    while (curr < numsSize - 1) {
        int next = curr + 1;
        printf("curr = %d, ans = %d\n", curr, ans);
        for (; next <= curr + k; next++) {
            if (next >= numsSize) {
                ans += nums[numsSize - 1];
                goto end;
            } else if (nums[next] >= 0) {
                ans += nums[next];
                curr = next;
                goto loop;
            }
        }
        while (next < numsSize && nums[next] < 0)
            next++;
        if (next >= numsSize) {
            ans += maxResult_dp(nums + curr, next - curr, k) - nums[curr];
            goto end;
        } else {
            ans += maxResult_dp(nums + curr, next - curr + 1, k) - nums[curr];
            curr = next;
            goto loop;
        }
    }
end:
    return ans;
}

int maxResult_dp(int *nums, int numsSize, int k)
{
    int *dp = (int *) malloc(sizeof(int) * numsSize);
    dp[0] = nums[0];
    int index = 1;
    /* compute [1, k) */
    for (index = 1; index < k && index < numsSize; index++) {
        int max = dp[0];
        for (int i = 1; i < index; i++)
            if (dp[i] > max)
                max = dp[i];
        dp[index] = max + nums[index];
    }
    /* compute [k, numsSize) */
    for (index = k; index < numsSize; index++) {
        int max = dp[index - k];
        for (int i = index - k + 1; i < index; i++)
            if (dp[i] > max)
                max = dp[i];
        dp[index] = max + nums[index];
    }
    int ans = dp[numsSize - 1];
    free(dp);
    return ans;
}
