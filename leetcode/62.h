

int uniquePaths(int m, int n)
{
    m = m - 1;
    n = n - 1;
    if (m < n) {
        int temp = m;
        m = n;
        n = temp;
    }
    // m >= n is guaranteed
    int ans = 1;
    for (int i = m + 1; i <= m + n; i++) {
        ans *= i;
    }
    for (int i = 2; i <= n; i++)
        ans = ans / i;
    return ans;
}