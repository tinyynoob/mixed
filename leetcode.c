#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * longestCommonPrefix(char ** strs, int strsSize);

int main()
{
    int i;
    char **s;
    s = (char**)malloc(sizeof(char*)*3);
    for(i=0; i<3; i++)
        s[i] = (char*)malloc(sizeof(char)*8);
    strcpy(s[0],"flower");
    strcpy(s[1],"flow");
    strcpy(s[2],"flight");
    printf("%s\n",longestCommonPrefix(s,3));
    system("pause");
    return 0;
}

char * longestCommonPrefix(char ** strs, int strsSize){
    int i, j, n, flag;
    char *ans;

    if(strsSize==1){
        ans = (char*)malloc(sizeof(char)*(strlen(strs[0])+1));
        strcpy(ans,strs[0]);
        return ans;
    }
    
    i = 0;
    n = -1;
    flag = 0;
    while(1){
        for(j=0; j<strsSize&&!flag; j++){
            if(!strs[i][j]){
                flag = 1;
                break;
            }
            else if(strs[i][j]!=strs[i][0])    //not common char
                flag = 1;
        }
        if(flag)
            break;
        n = i++;
    }
    //n is now denoted the last index that keeps prefix common
    
    ans = (char*)malloc(sizeof(char)*(n+2));
    ans[n+1] = '\0';
    ans[n] = 'A';
    for(i=0; i<=n; i++)
        ans[i] = strs[0][i];
    return ans;
}