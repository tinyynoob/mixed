#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char s1[10], s2[5];
    int i;
    strcpy(s1,"abcdefg");
    strcpy(s2,"ab");
    for(i=0; s1[i]==s2[i]; i++)
        printf("%d\t",i);
    system("pause");
    return 0;
}