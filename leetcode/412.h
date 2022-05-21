

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fizzBuzz(int n, int* returnSize)
{
    char **ans = (char **) malloc(sizeof(char *) * n);
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0) {
            if (i % 5 == 0)
                ans[i - 1] = strdup("FizzBuzz");
            else
                ans[i - 1] = strdup("Fizz");
        } else if (i % 5 == 0) {
            ans[i - 1] = strdup("Buzz");
        } else {
            char str[6];
            sprintf(str, "%d", i);
            ans[i - 1] = strdup(str);
        }
    }
    *returnSize = n;
    return ans;
}