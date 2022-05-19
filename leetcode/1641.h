

int countVowelStrings(int n)
{
    /* tail[ ][0] denotes the number of string which ends with a
     * tail[ ][1] denotes the number of string which ends with e
     * ans so on...
     */
    int tail[2][5];
    for (int i = 0; i < 5; i++) // for n = 1
        tail[1][i] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 5; j++) {
            tail[i & 1][j] = 0;
            for (int k = 0; k <= j; k++)
                tail[i & 1][j] += tail[(i & 1) ^ 1][k];
        }
    }
    int ans = 0;
    for (int i = 0; i < 5; i++)
        ans += tail[n & 1][i];
    return ans;
}