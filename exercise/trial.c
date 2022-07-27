#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#define NUM 100
#define MOD 1234354534

char ch1[5];
char ch2[5];
int *a[3][3];

typedef struct tr
{
    char ch[2];
    int i;
} abel;

int main()
{
    int M=-7;
    a[2][2]=M;
    M=-5;
    printf("%d",a[2][2]);
    return 0;
}



long long quickPower(long long base,long long power)
{
    long long result=1;
    while(power>0)
    {
        if(power&1) result=result*base%MOD;
        power>>=1;
        base=base*base%MOD; //必要时每乘一次取一次模
    }
    return result;
}

long long quickMulti(long long a,long long b)
{
    long long result=0;
    while(b>0)
    {
        if(b&1) result=(result+a)%MOD;
        b>>=1;
        a=(a+a)%MOD;
    }
    return result;
}
