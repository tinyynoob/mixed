

int uniquePaths(int m, int n){
    int i, temp;
    long ans;
    m--;
    n--;
    /*---ans = (m+n)!/m!/n!-----*/
    if(n>m){    //if n>m, swap to keep m>=n
        temp = m;
        m = n;
        n = temp;
    }
    ans = 1;
    for(i=m+1; i<=m+n; i++)
        ans*= i;
    for(i=2; i<=n; i++)
        ans/= i;
    return ans;
}