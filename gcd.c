#include<stdio.h>
#include<stdlib.h>


int main()
{
    int a,b,i,ans;
    printf("input:");
    scanf("%d%d",&a,&b);
    if(b>a){    // if b>a, swap to keep a>=b
        i=b;
        b=a;
        a=i;
    }
    ans = 1;
    for(i=2;i<b;i++){
        while(a%i==0 && b%i==0){
            ans*= i;
            a/= i;
            b/= i;
        }
    }
    printf("ans = %d\n",ans);
    return 0;
}