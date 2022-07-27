#include<stdio.h>

long long quickPower(long long base,long long power,int mod)
{
    long long result=1;
    while(power>0)
    {
        if(power&1) result=result*base%mod;
        power>>=1;
        base=base*base%mod;
    }
    return result;
}

int main()
{
    long long b,p,s;
    int k;
    scanf("%ld%ld%ld",&b,&p,&k);
    s=quickPower(b,p,k);
    printf("%ld^%ld mod %d=%ld",b,p,k,s);
    return 0;
}
