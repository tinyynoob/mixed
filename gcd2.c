#include<stdio.h>
#include<stdlib.h>

int gcd(int a, int b);

int main()
{
    int a,b,ans;
    printf("input:");
    scanf("%d%d",&a,&b);
    printf("%d\n",gcd(a,b));

    system("pause");
    return 0;
}

int gcd(int a, int b)
{
    if(a==0)
        return b;
    else if (b==0)
        return a;

    if(a>b)
        return gcd(a%b,b);
    else
        return gcd(a,b%a);
}