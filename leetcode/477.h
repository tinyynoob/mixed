

int totalHammingDistance(int* nums, int numsSize)
{
    int ans = 0;
    for (unsigned b = 1; b; b <<= 1) {
        int count[2] = {0, 0};
        for (int i = 0; i < numsSize; i++)
            count[!!(b & nums[i])]++;
        ans += count[0] * count[1];
    }
    return ans;
}