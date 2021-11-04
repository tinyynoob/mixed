#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int strStr(char * haystack, char * needle);

int main()
{
    char s1[25], s2[25];
    strcpy(s1,"hello");
    strcpy(s2,"ll");
    printf("%d\n",strStr(s1, s2));
    system("pause");
    return 0;
}



int strStr(char * haystack, char * needle){
    int ans, index, subindex, needle_length, backward_search;
    int *KMPtable;
    needle_length = 0;
    for(index=0; needle[index]; index++)
        needle_length++;
    if(needle_length==0)
        return 0;
    /*-------construct KMP table-------*/
    KMPtable = (int*)malloc(sizeof(int)*needle_length);
    KMPtable[0] = -1;
    index = 1;
    subindex = 0;
    while(needle[index]){
        if(needle[index]!=needle[subindex]){    //if not matched, 
            KMPtable[index++] = subindex;
            subindex = 0;
            continue;
        }
        while(needle[index]==needle[subindex])  //if matched, loop until not matched
            KMPtable[index++] = subindex++;
        if(needle[index]){  //if !='\0' //for unmatched after continuous matching
            KMPtable[index] = subindex;
            while(subindex>0){
                if(needle[index]==needle[KMPtable[subindex]])   //backward compare
                    break;
                subindex = KMPtable[subindex];
            }
            index++;
        }   
    }
    /*end----construct KMP table-------*/
    
    ans = -1;
    index = 0;
    subindex = 0;
    while(haystack[index]&&ans==-1){
        if(haystack[index]!=needle[subindex]){    //if not matched,
            while(subindex>0){
                if(haystack[index]==needle[subindex])
                    break;
                subindex = KMPtable[subindex];
            }
            index++;
            subindex++;
            continue;
        }
        while(haystack[index]==needle[subindex]){
            if(subindex==needle_length-1){    //found answer
                ans = index-subindex;
                break;
            }
            index++;
            subindex++;
        }
    }
    free(KMPtable);
    return ans;
}


