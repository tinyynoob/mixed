#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * convert(char * s, int numRows);

int main(){
    char s[1000];
    int numRows = 1;
    strcpy(s, "ABC");
    puts(convert(s,numRows));
    system("pause");
    return 0;
}

char * convert(char * s, int numRows){
    int i, j, length, eachLength ,*idx, index;
    char **rows;
    length = strlen(s);
    if(numRows==1)
        eachLength = length+1;
    else
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
    index = 0;
    for(i=0; i<numRows&&index<length; i++){
        for(j=0; rows[i][j]!='\0'; j++)
            s[index++] = rows[i][j];
    }
    for(i=0;i<numRows;i++)
        free(rows[i]);
    free(rows);
    free(idx);
    return s;
}