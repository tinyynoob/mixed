
#define max(a, b) ((a>b)?a:b) 

int maxx(int, int);

int lengthOfLongestSubstring(char * s){
    int i, index, ans, look_up, left_bound;
    int appeared_table[95];
    char *p;
    
    for(i=0;i<95;i++)   //use ascii code (subtract 32) as the index of the table
        appeared_table[i] = -1;
    ans = 0;
    left_bound = -1;     //is used to mark the rightmost repeated position
    index = 0;
    for(p=s; *p; p++){
        look_up = (*p)-32;      // 32 == ' '
        if(appeared_table[look_up] == -1)
            i = index - left_bound;
        else{
            i = index - max(left_bound, appeared_table[look_up]);
            if(appeared_table[look_up] > left_bound)    //update left_bound
                left_bound = appeared_table[look_up];
        }

        if(i>ans)   //if a longer substring is found
            ans = i;
        appeared_table[look_up] = index++;  //update the table
    }
    return ans;
}
