#include<stdio.h>


void sstrcat(char *s,char *t)
{
    int n;
    n=strlen(s);
    while(*(s+n)=*t) s++,t++;
}

int main()
{
    char s[]="abcd",t[]="efgh";
    sstrcat(s,t);
    puts(s);
    return 0;
}


/*

1.从线性表中删除数据信息为item的元素，O（n）算法


*/
