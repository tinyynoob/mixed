#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * convert(char * s, int numRows);

int main(){
    char s[1000];
    int numRows = 1;
    strcpy(s, "A");
    puts(convert(s,numRows));
    system("pause");
    return 0;
}

char * convert(char * s, int numRows){
    int i, j, length, eachLength ,*idx, index;
    char **rows, *ans;
    length = strlen(s);
    eachLength = length/2 +2;
    rows = (char**)malloc(sizeof(char*)*numRows);
    idx = (int*)malloc(sizeof(int)*numRows);
    for(i=0; i<numRows; i++){
        rows[i] = (char*)malloc(sizeof(char)*eachLength);
        memset(rows[i],'\0',eachLength);
        idx[i]=0;
    }
    i=0;
    while(1){
        for(j=0; j<numRows&&i<length; j++)  //downward
            rows[j][idx[j]++] = s[i++];
        if(i>=length)
            break;
        
        for(j=numRows-2; j>0&&i<length; j--)    //upward
            rows[j][idx[j]++] = s[i++];
        if(i>=length)
            break;
    }
    ans = (char*)malloc(sizeof(char)*length);
    index = 0;
    for(i=0;i<numRows;i++){
        for(j=0; rows[i][j]!='\0'; j++)
            ans[index++] = rows[i][j];
    }
    ans[index] = '\0';
    for(i=0;i<numRows;i++)
        free(rows[i]);
    free(rows);
    free(idx);
    return ans;
}