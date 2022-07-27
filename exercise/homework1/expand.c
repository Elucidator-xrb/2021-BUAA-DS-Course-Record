#include<stdio.h>
#include<string.h>
#include<ctype.h>

char in[BUFSIZ];

int isok(int pos)
{
    int k=0;
    in[pos-1]<in[pos+1] && islower(in[pos-1]) && islower(in[pos+1]) && (k=1);
    in[pos-1]<in[pos+1] && isupper(in[pos-1]) && isupper(in[pos+1]) && (k=1);
    in[pos-1]<in[pos+1] && isdigit(in[pos-1]) && isdigit(in[pos+1]) && (k=1);
    return k;
}

int main()
{
    int len,i;
    char ch;
    fgets(in,BUFSIZ,stdin);
    len=strlen(in);
    for(i=0;i<len;i++)
    {
        if(in[i]=='-' && isok(i))
        {
            for(ch=in[i-1]+1;ch<in[i+1];ch++)
                putchar(ch);
        }
        else putchar(in[i]);
    }

    return 0;
}
