#include <string.h>

#define max(a, b) ((a > b) ? (a) : (b))

int longestCommonSubsequence(char * text1, char * text2)
{
    int len1 = strlen(text1), len2 = strlen(text2);
    int **dp = (int **) malloc(sizeof(int *) * (len1 + 1));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int *) malloc(sizeof(int) * (len2 + 1));
        dp[i][0] = 0;
    }
    for (int i = 0; i <= len2; i++)
        dp[0][i] = 0;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (text1[i - 1] == text2[j - 1])   // -1 since dp[0][x] and dp[x][0] are for empty string
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    int ans = dp[len1][len2];
    for (int i = 0; i <= len1; i++)
        free(dp[i]);
    free(dp);
    return ans;
}