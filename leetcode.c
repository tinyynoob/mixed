#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int lengthOfLongestSubstring(char*);
int maxx(int, int);

int main()
{
    char s[1000];
    strcpy(s,"aabaab!bb");
    printf("%s\n",s);
    printf("%d\n",lengthOfLongestSubstring(s));
    system("pause");
    return 0;
}

int lengthOfLongestSubstring(char * s){
    int i, index, ans, look_up, left_bound;
    int appeared_table[95];
    char *p;
    
    for(i=0;i<95;i++)   //use ascii code (subtract 32) as the index of the table
        appeared_table[i] = -1;
    ans = 0;
    left_bound = -1;     //is used to mark the last repeated position
    index = 0;
    for(p=s; *p; p++){
        look_up = (*p)-32;      // 32 == ' '
        if(appeared_table[look_up] == -1)
            i = index - left_bound;
        else{
            i = index - maxx(left_bound, appeared_table[look_up]);
            left_bound = appeared_table[look_up];
        }
        if(i>ans)   //if a longer substring is found
            ans = i;
        appeared_table[look_up] = index++;  //update the table
    }
    return ans;
}

int maxx(int a, int b){
    if(a>b)
        return a;
    return b;
}