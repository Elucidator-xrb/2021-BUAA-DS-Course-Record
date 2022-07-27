#include<stdio.h>
#include<string.h>
#include<ctype.h>

char in[BUFSIZ];
int numStack[BUFSIZ];
char symStack[BUFSIZ];

int main()
{
    int i,j;
    int len,numtop=0,symtop=0;//Õ»¶¥-1²ÅÊÇÕ»¶¥ÔªËØ
    int tmp,ans;
    fgets(in,BUFSIZ,stdin);
    len=strlen(in);
    for(i=0,j=0;i<len;i++)
        if(in[i]!=' ') in[j++]=in[i];
    in[j]='\0';

    for(i=0;in[i]!='=';)
    {
        if(isdigit(in[i]))
        {
            for(tmp=0;isdigit(in[i]);i++)
                tmp=tmp*10+(in[i]-48);
            numStack[numtop++]=tmp;
        }
        else if(in[i]=='+' || in[i]=='-')
        {
            symStack[symtop++]=in[i];
            i++;
        }
        else if(in[i]=='*')
        {
            i++;
            for(tmp=0;isdigit(in[i]);i++)
                tmp=tmp*10+(in[i]-48);
            numStack[numtop-1]*=tmp;
        }
        else if(in[i]=='/')
        {
            i++;
            for(tmp=0;isdigit(in[i]);i++)
                tmp=tmp*10+(in[i]-48);
            numStack[numtop-1]/=tmp;
        }
    }

    ans=numStack[0];
    if(symtop)
    {
        for(i=0;i<symtop;i++)
        {
            symStack[i]=='+' && (ans+=numStack[i+1]);
            symStack[i]=='-' && (ans-=numStack[i+1]);
        }
    }
    printf("%d",ans);
    return 0;
}
