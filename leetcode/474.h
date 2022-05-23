
#define max(x, y) ((x) > (y) ? (x) : (y))

int findMaxForm(char ** strs, int strsSize, int m, int n)
{
    int **dp = (int **) malloc(sizeof(int *) * (m + 1));
    for (int i = 0; i <= m; i++)
        dp[i] = (int *) calloc(sizeof(int), (n + 1));
    
    for (int k = 0; k < strsSize; k++) {
        int zero = 0, one = 0;
        for (int c = 0; c < strlen(strs[k]); c++)
            strs[k][c] == '0' ? zero++ : one++;
        /* decreasing to prevent repeatedly update */
        for (int i = m; i >= zero; i--) {
            for (int j = n; j >= one; j--)
                dp[i][j] = max(dp[i][j], dp[i - zero][j - one] + 1);
        }
    }
    int ans = dp[m][n];
    for (int i = 0; i <= m; i++)
        free(dp[i]);
    free(dp);
    return ans;
}