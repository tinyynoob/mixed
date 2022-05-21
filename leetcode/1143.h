#include <string.h>

#define max(a, b) ((a > b) ? (a) : (b))

int longestCommonSubsequence(char * text1, char * text2)
{
    int len1 = strlen(text1), len2 = strlen(text2);
    int **dp = (int **) malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++) {
        dp[i] = (int *) malloc(sizeof(int) * (len2 + 1));
        dp[i][0] = 0;
    }
    for (int i = 0; i <= len2; i++)
        dp[0][i] = 0;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (text1[i - 1] == text2[j - 1])
                dp[i & 1][j] = dp[(i & 1) ^ 1][j - 1] + 1;
            else
                dp[i & 1][j] = max(dp[(i & 1) ^ 1][j], dp[i & 1][j - 1]);
        }
    }
    int ans = dp[len1 & 1][len2];
    free(dp[0]);
    free(dp[1]);
    free(dp);
    return ans;
}