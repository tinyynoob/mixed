

int countDigitOne(int n){
    int i, j, digits, ans, mantissa, *dp;
    if(!n)
        return 0;
    
    digits = 0;
    for(i=n; i; i/=10)
        digits++;
    dp = (int*)malloc(sizeof(int)*digits);
    /*dp[0]=ans of 9, dp[1]=ans of 99, etc*/
    dp[0] = 1;
    for(i=1; i<digits-1; i++){
        dp[i] = 1;
        for(j=0; j<i; j++)  //compute dp[i]=exp(10,i)
            dp[i]*= 10;
        dp[i]+= 10*dp[i-1];
    }
    
    i = 1;
    for(j=0; j<digits-1; j++)   //compute i=exp(10,digits-1)
        i*= 10;
    ans = 0;
    for(digits=digits-1; digits; digits--){
        mantissa = n/i;
        ans+= mantissa*dp[digits-1];
        if(mantissa > 1)
            ans+= i;
        else if(mantissa == 1)
            ans+= n%i+1;
        n = n%i;
        i/= 10;
    }
    if(n)   //last digit
        ans = ans+1;
    
    free(dp);
    return ans;
}