
//implement by KMP algorithm, which provides lower time complexity
int strStr(char * haystack, char * needle){
    int index, subindex, needle_length;
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
        if(needle[index]!=needle[subindex]){    //if not matched, write KMP table and reset subindex
            KMPtable[index++] = subindex;
            subindex = 0;
            continue;
        }
        while(needle[index]==needle[subindex])  //if matched, loop until not matched
            KMPtable[index++] = subindex++;
        if(needle[index]){  //if !='\0'     //for unmatched after continuous match
            KMPtable[index] = subindex;
            while(subindex>0){  //backward compare, if all distinct, subindex reduces to 0
                if(needle[index]==needle[KMPtable[subindex]])   
                    break;
                subindex = KMPtable[subindex];  //iteratively decrease
            }
            index++;
        }   
    }
    /*end----construct KMP table-------*/
    
    /*-------starting to find substring-------*/
    index = 0;
    subindex = 0;
    while(haystack[index]){
        if(haystack[index]!=needle[subindex]){    //if not matched, backward(needle) compare
            while(subindex>0){  //backward compare, if all distinct, subindex reduces to 0
                if(haystack[index]==needle[subindex])   
                    break;
                subindex = KMPtable[subindex];  //iteratively decrease
            }
            if(haystack[index]!=needle[subindex]){  //if subindex==0
                index++;
                continue;
            }
        }
        while(haystack[index]==needle[subindex]){
            if(subindex==needle_length-1){    //found answer
                free(KMPtable);
                return index-subindex;
            }
            index++;
            subindex++;
        }
    }
    //out of loop if no matched substring found
    free(KMPtable);
    return -1;
}
