#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int reverse(int x);

int main()
{
    int n;
    n = 123;
    printf("%d\n",reverse(n));
    system("pause");
    return 0;
}

int reverse(int x){
    long n;
    char *arr, sign=0, i, digitNum;
    if(x<0){
        sign = 1;
        x*= -1;
    }
    digitNum = 1;
    for(n=x; n/10; n/=10)
        digitNum++;
    arr = (char*)malloc(sizeof(char)*digitNum);
    i=0;
    for(n=x; n/10; n/=10)      //destruct
        arr[i++] = n%10;
    arr[i] = n;
    
    i = 0;
    n = arr[i++];
    while(i<digitNum){    //construct
        n*= 10;
        n+= arr[i++];
    }
    if(sign)
        n*= -1;
    
    free(arr);
    return n;
}