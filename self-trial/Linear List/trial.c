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

1.�����Ա���ɾ��������ϢΪitem��Ԫ�أ�O��n���㷨


*/
