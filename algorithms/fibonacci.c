#include<stdio.h>
#include<stdlib.h>
int fibo(int n);
int fibo_iter(int n);
int fibo_dp_bottom(int n);
int main()
{
    int x;
    scanf("%d",&x);
    printf("%d %d %d\n",fibo(x),fibo_iter(x),fibo_dp_bottom(x));
    return 0;
}
int fibo(int n)
{
    if(n==0) return 0;
    if(n==1) return 1;
    return fibo(n-1)+fibo(n-2);
}
int fibo_iter(int n)
{
    if(n<=1) return n; 
    int result =1,tmp=0;
    for(int i=2; i<=n; i++)
    {
        result = result + tmp;
        tmp = result-tmp;
    }
    return result;
}
int fibo_dp_bottom(int n)
{
    if (n <=1) return n;
    int *dp,result;
    dp = (int *)calloc(n+1,sizeof(int));
    dp[0] = 0;
    dp[1] = 1;
    for(int i=2; i<=n; i++)
    {
        dp[i] = dp[i-1] + dp[i -2];
    }
    result = dp[n];
    free(dp);
    return result;
}