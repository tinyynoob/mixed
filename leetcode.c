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
        eachLength = length;
    else
        eachLength = length/2 +1;
    rows = (char**)malloc(sizeof(char*)*numRows);
    idx = (int*)malloc(sizeof(int)*numRows);
    for(i=0; i<numRows; i++){
        rows[i] = (char*)malloc(sizeof(char)*eachLength);
        idx[i]=0;
    }

    //store the original string into a zigzag pattern (in #numRows string)
    index=0;
    while(1){
        for(i=0; i<numRows&&index<length; i++)  //downward
            rows[i][idx[i]++] = s[index++];
        if(index>=length)
            break;
        
        for(i=numRows-2; i>0&&index<length; i--)    //upward, work when numRows>=3
            rows[i][idx[i]++] = s[index++];
        if(index>=length)
            break;
    }

    //s = rows[0]+rows[1]+...+rows[numRows-1] is the output
    index = 0;
    for(i=0; i<numRows; i++){
        for(j=0; j<idx[i]; j++)
            s[index++] = rows[i][j];
    }
    for(i=0;i<numRows;i++)
        free(rows[i]);
    free(rows);
    free(idx);
    return s;
}