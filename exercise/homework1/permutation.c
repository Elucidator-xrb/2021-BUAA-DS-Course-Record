#include<stdio.h>

char a[10]={1,2,3,4,5,6,7,8,9,10};

void reverse(int left,int right)
{
    int i,j;
    for(i=left,j=right;i<j;i++,j--)
    {
        a[i]^=a[j];
        a[j]^=a[i];
        a[i]^=a[j];
    }
}

int nextPermutation(int n)
{
    int i,j;
    for(i=n-1;i>0 && a[i]<a[i-1];i--);
    if(i==0) return 0;
    else
    {
        for(j=i;j<n && a[j]>a[i-1];j++);
        a[j-1]^=a[i-1],a[i-1]^=a[j-1],a[j-1]^=a[i-1];
        reverse(i,n-1);
        return 1;
    }
}

int main()
{
    int i,n;
    scanf("%d",&n);
    do
    {
        for(i=0;i<n;i++) printf("%d ",a[i]);
        puts("");
    }
    while(nextPermutation(n));

    return 0;
}
