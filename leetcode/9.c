

bool isPalindrome(int x){
    int i, digitNum;
    char s[32];
    if(x<0)
        return false;
    digitNum = 0;
    while(x){
        s[digitNum++] = x%10;
        x/= 10;
    }
    for(i=0; i<digitNum/2; i++)
        if(s[i] != s[digitNum-i-1])
            return false;
    return true;
}