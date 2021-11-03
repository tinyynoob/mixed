

int strStr(char * haystack, char * needle){
    int ans, index, subindex, needle_length;
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
    while(needle[index]){
        subindex = 0;
        if(needle[index]!=needle[subindex]){    //if not matched, set table to 0 and go next
            KMPtable[index++] = 0;
            continue;
        }
        while(needle[index]==needle[subindex])  //if matched, loop until not matched
            KMPtable[index++] = subindex++;
        if(needle[index])
            KMPtable[index++] = subindex;
    }
    /*end----construct KMP table-------*/
    ans = -1;
    index = 0;
    subindex = 0;
    while(haystack[index]&&ans==-1){
        if(haystack[index]!=needle[subindex]){    //if not matched, reset subindex and go next
            subindex = 0;
            index++;
            continue;
        }
        while(haystack[index]==needle[subindex]){
            if(subindex==needle_length-1){    //found
                ans = index-subindex;
                break;
            }
            index++;
            subindex++;
        }
        if(needle[subindex])
            subindex = KMPtable[subindex];
    }
    free(KMPtable);
    return ans;
}
