#include<stdio.h>
#include<string.h>
#include<ctype.h>
char format[100];
char ch[110];
char dest[110];

int main()
{
    int i=1,j=0,num[2]={0};
    int tmp,len,len_d,add;
    gets(format);
    gets(ch);
    len=strlen(ch);
    if(format[i]=='-')
    {
        i++;
        while(format[i]!='\0')
        {
            if(isdigit(format[i]))
                tmp=(tmp<<1)+(tmp<<3)+(format[i]&15);
            else
            {
                num[j++]=tmp;
                tmp=0;
            }
            if(j==2) break;
            i++;
        }

        if(len<=num[0])len_d=len;
        else len_d=num[0];

        add=(num[1]>len_d)?(num[1]-len_d):0;
        for(i=0;i<add;i++) dest[i]='#';
        strncat(dest,ch,len_d);
    }
    else
    {
        while(format[i]!='\0')
        {
            if(isdigit(format[i]))
                tmp=(tmp<<1)+(tmp<<3)+(format[i]&15);
            else
            {
                num[j++]=tmp;
                tmp=0;
            }
            if(j==2) break;
            i++;
        }

        if(len<=num[0])len_d=len;
        else len_d=num[0];

        add=(num[1]>len_d)?(num[1]-len_d):0;
        strncat(dest,ch,len_d);
        for(i=0;i<add;i++) dest[i+len_d]='#';
    }
    printf("%s",dest);
    return 0;
}
