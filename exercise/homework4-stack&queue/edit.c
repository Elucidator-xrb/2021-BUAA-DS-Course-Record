#include<stdio.h>
#include<string.h>

char buf[600];
struct operation
{
    int op;
    int pos;
    char str[600];
} stack[100];
int top=-1;

void loadInfo();
void insert();
void del();
void undo();

int main()
{
    int o;
    loadInfo();
    scanf("%*[\n]");  //只要是字符串读取，就一定要想清缓冲区中的情况(如'\n')
    while(scanf("%d",&o))
    {
        switch(o)
        {
        case 1:insert();break;
        case 2:del();break;
        case 3:undo();break;
        }//printf("[CURRENT]:[%d character]",strlen(buf));puts(buf);
        if(o==-1) break;
    }
    puts(buf);
    return 0;
}

void loadInfo()
{
    int n;
    gets(buf);
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d",&stack[++top].op);
        scanf("%d%s",&stack[top].pos,stack[top].str);
    }
}

void insert()
{
    char tmp[BUFSIZ]={0},*p=NULL;

    stack[++top].op=1;
    scanf("%d%s",&stack[top].pos,stack[top].str);

    p=buf+stack[top].pos;
    strcpy(tmp,p);
    p[0]='\0';
    strcat(buf, stack[top].str);
    strcat(buf, tmp);
}

void del()
{
    char *p=NULL;
    int n,len;

    stack[++top].op=2;
    scanf("%d%d",&stack[top].pos,&n);

    p=buf+stack[top].pos;
    len=strlen(p);
    if(len<n) n=len;
    strncpy(stack[top].str,p,n);
    p[0]='\0';
    strcat(buf,p+n);
}

void undo() //若设置好insert和del的接口，便可复用insert和del
{
    struct operation last;
    char *p,tmp[BUFSIZ]={0};
    int n;

    if(top>=0)
    {
        last=stack[top--];
        p=buf+last.pos;
        if(last.op==1)
        {
            n=strlen(last.str);
            p[0]='\0';
            strcat(buf,p+n);
        }
        else if(last.op==2)
        {
            strcpy(tmp,p);
            p[0]='\0';
            strcat(buf,last.str);
            strcat(buf,tmp);
        }
    }
}
