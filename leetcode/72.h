

int minDistance(char * word1, char * word2)
{
    int len1 = strlen(word1), len2 = strlen(word2);
    int **dp = (int **) malloc(sizeof(int *) * (len1 + 1));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int *) malloc(sizeof(int) * (len2 + 1));
        dp[i][0] = i;
    }
    for (int i = 0; i <= len2; i++)
        dp[0][i] = i;
    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            // from word1 to word2
            // insert dp[i - 1][j]
            // delete dp[i][j - 1]
            // replace dp[i - 1][j - 1]
            if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else if (dp[i - 1][j] <= dp[i][j - 1] && dp[i - 1][j] <= dp[i - 1][j - 1])
                dp[i][j] = dp[i - 1][j] + 1;
            else if (dp[i][j - 1] <= dp[i - 1][j] && dp[i][j - 1] <= dp[i - 1][j - 1])
                dp[i][j] = dp[i][j - 1] + 1;
            else
                dp[i][j] = dp[i - 1][j - 1] + 1;
        }
    }
    int ans = dp[len1][len2];
    for (int i = 0; i <= len1; i++)
        free(dp[i]);
    free(dp);
    return ans;
}