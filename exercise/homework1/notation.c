#include<stdio.h>
#include<string.h>

char in[BUFSIZ];

int main()
{
    int len_i,cnt;
    char *pos,*dec;
    fgets(in,BUFSIZ,stdin);
    if(in[strlen(in)-1]=='\n') in[strlen(in)-1]='\0';//È¥³ýfgets½áÎ²µÄ'\n'

    pos=strchr(in,'.');
    pos[0]='\0';
    dec=pos+1;
    len_i=strlen(in);

    if(len_i>1)           printf("%c.%s%se%d",in[0],in+1,dec,len_i-1);
    else if(in[0]!='0')   printf("%c.%se0",in[0],dec);
    else
    {
        for(cnt=1;dec[cnt-1]=='0';cnt++);
        if(dec[cnt]=='\0') printf("%ce-%d",dec[cnt-1],cnt);
        else               printf("%c.%se-%d",dec[cnt-1],dec+cnt,cnt);
    }

    return 0;
}
