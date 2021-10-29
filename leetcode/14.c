

char * longestCommonPrefix(char ** strs, int strsSize){
    int i, j, n, flag;
    char *ans;
    
    j = 0;  n = -1; flag = 0;
    while(1){   //determine n
        for(i=0; i<strsSize&&!flag; i++){
            if(!strs[i][j]){    //if a string ends
                flag = 1;
                break;
            }
            else if(strs[i][j]!=strs[0][j])    //not common char
                flag = 1;
        }
        if(flag)
            break;
        n = j++;
    }
    //n is now denoted the last index that keeps prefix common
    
    ans = (char*)malloc(sizeof(char)*(n+2));
    ans[n+1] = '\0';
    for(i=0; i<=n; i++)
        ans[i] = strs[0][i];
    return ans;
}