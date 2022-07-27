#include<stdio.h>
#include<string.h>
#define max(x,y) (x>=y ? x : y)

char num1[100],num2[100];
char dif[100];

int main()
{
    int i,set;
    int len,len1,len2,sign=1;
    gets(num1),len1=strlen(num1);
    gets(num2),len2=strlen(num2);
    len=max(len1,len2);

    if(len1>len2)
    {
        for(i=len2-1;i>=0;i--) num2[i+len-len2]=num2[i];
        memset(num2,0,(len-len2)*sizeof(char));
    }
    else if(len1<len2)
    {
        for(i=len1-1;i>=0;i--) num1[i+len-len1]=num1[i];
        memset(num1,0,(len-len1)*sizeof(char));
    }
    for(i=0;i<len;i++)
    {
        num1[i]!=0 && (num1[i]-=48);
        num2[i]!=0 && (num2[i]-=48);
        dif[i]=num1[i]-num2[i];
    }

    for(i=0;dif[i]==0 && i<len;i++);
    if(dif[i]<0)
    {
        sign=-1;
        for(i=0;i<len;i++) dif[i]=-dif[i];
    }
    else if(i==len) sign=0;

    if(sign==0) printf("0");//特殊情况：0
    else
    {
        for(i=len-1;i>=0;i--)//高精度减法
        {
            if(dif[i]<0)
            {
                dif[i]+=10;
                dif[i-1]--;
            }
        }
        sign==-1 && printf("-");
        for(set=0;dif[set]==0;set++);
        for(i=set;i<len;i++) printf("%d",dif[i]);
    }
    return 0;
}
