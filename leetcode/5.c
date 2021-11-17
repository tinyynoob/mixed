
#define max(a,b) (a>b)?a:b

/*----implement by Manacher's algorithm----*/
char * longestPalindrome(char * s){
    int i, j, offset, length, longestIndex, *LPS;
    char *extended_s, *ans;
    
    length = 0;
    for(i=0; s[i]; i++)
        length++;
    length = 2*length+1;    //length of extended_s
    LPS = (int*)malloc(sizeof(int)*(length));   //store length of longest palindrome centered at i
    extended_s = (char*)malloc(sizeof(char)*(length+1));    //+1 space for '\0'
    for(i=0; i<length/2; i++){
        extended_s[2*i] = '_';    //padding, to make string of even length easy to procoess
        extended_s[2*i+1] = s[i];
    }
    extended_s[length-1] = '_';
    extended_s[length] = '\0';
    
    i = 0;
    longestIndex = 0;
    while(i<length){    //build LPS table
        j = 0;  //used as flag
        offset = 1;
        while(i-offset>=0 && i+offset<length && extended_s[i-offset]==extended_s[i+offset]) //if not exceed bound and be palindromic
            offset++;
        LPS[i] = offset;
        if(LPS[i]>LPS[longestIndex])
            longestIndex = i;
        for(offset=1; i-offset>=0&&offset<LPS[i]; offset++){
            if(offset+LPS[i-offset] < LPS[i])
                LPS[i+offset] = LPS[i-offset];
            else if(offset+LPS[i-offset] > LPS[i])
                LPS[i+offset] = LPS[i]-offset;
            else if(offset+LPS[i-offset] == LPS[i]){
                i+= offset;    //determine the distance to skip
                j = 1;
                break;
            }
        }
        if(!j)
            i+= max(1, offset-1);   //determine the distance to skip
    }
    ans = (char*)malloc(sizeof(char)*LPS[longestIndex]);
    j = 0;
    for(i=longestIndex-LPS[longestIndex]+1; i<longestIndex+LPS[longestIndex]; i++)  //store the substring to ans
        if(extended_s[i]!='_')
            ans[j++] = extended_s[i];
    ans[j] = '\0';
    free(LPS);
    free(extended_s);
    return ans;
}