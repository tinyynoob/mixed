

int reverse(int x){
    int i, n, digitNum, sign=0;
    char *arr;     //use char type to save memory
    if(x==-2147483648)  //which is a very special case, so I treat it independently
        return 0;
    else if(x<0){
        sign = 1;
        x*= -1;
    }
    digitNum = 1;
    for(n=x; n/10; n/=10)
        digitNum++;
    arr = (char*)malloc(sizeof(char)*digitNum);
    /*----destruct----*/
    i=0;
    for(n=x; n/10; n/=10)
        arr[i++] = n%10;
    arr[i] = n;
    
    /*----construct----*/
    i = 0;
    n = arr[i++];   
    while(i<digitNum){
        if(n > INT_MAX/10){     //if a overflow is going to occur
            sign = -1;
            break;
        }
        n*= 10;
        n+= arr[i++];
    }
    
    if(sign==-1)    //if overflow
        n = 0;
    else if(sign==1)    //if negative
        n*= -1;
    free(arr);
    return n;
}