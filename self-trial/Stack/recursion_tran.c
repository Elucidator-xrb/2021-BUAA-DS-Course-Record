#include<stdio.h>
#include<stdlib.h>

/*
f(m,n)=m+n+1  m*n=0;
f(m,n)=f(m-1,f(m,n-1)) m*n!=0;
*/

#define MAX 1000

int fNoneRecursive(int m,int n)
{
    int Stack[MAX],top=-1;
    do
    {
        if(m*n!=0)
        {
            Stack[++top]=m-1;
            n--;
        }
        else
        {
            n=m+n+1;
            if(top>=0) m=Stack[top];
            top--;
        }
    }while(top>=-1);
    return n;
}

int main()
{
    int m,n,f;
    scanf("%d%d",&m,&n);
    f=fNoneRecursive(m,n);
    printf("%d",f);
    return 0;
}
