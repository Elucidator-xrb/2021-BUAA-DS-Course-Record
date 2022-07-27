#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define DEFLINE 10 /* 缺省值 */
#define MAXLINE 81
typedef struct node
{
    char *line;
    struct node *link;
} CNode, *CLinklist;

CLinklist list;

int ch_to_i(char *s);
void createList(int n);
void readIn_Print(char *fname);
void printList();

int main(int argc,char *argv[])
{
    char *filename;
    int i,n=DEFLINE;

    if(argc==3 && argv[1][0]=='-')
    {
        filename=argv[2];
        n=ch_to_i(argv[1]+1);
    }
    else if(argc==2) filename=argv[1];
    else perror("wrong format!"),exit(-1);

    createList(n);
    readIn_Print(filename);

    return 0;
}

int ch_to_i(char *s)
{
    int i,ans=0;
    for(i=0;s[i]!='\0';i++) ans=(ans<<1)+(ans<<3)+s[i]&15;
    return ans;
}

void createList(int n)
{
    int i;
    CLinklist p,r;
    for(i=0;i<n;i++)
    {
        p=(CLinklist)malloc(sizeof(CNode));
        p->line=NULL;
        p->link=NULL;
        if(list==NULL) list=p;
        else r->link=p;
        r=p;
    }
    r->link=list;
}

void readIn_Print(char *fname)
{
    FILE *fp;
    CLinklist p=list,q;
    char curline[MAXLINE];
    if((fp=fopen(fname,"r"))==NULL)
    {
        perror(fname);
        exit(-2);
    }
    while(fgets(curline,MAXLINE-1,fp)!=NULL)
    {
        if(p->line!=NULL) free(p->line);
        p->line=(char *)malloc(sizeof(char));
        strcpy(p->line,curline);
        p=p->link;
    }
    q=p;
    while(p->line==NULL) p=p->link;
    while(p->link!=q)
    {
        printf("%s",p->line);
        p=p->link;
    }
    printf("%s",p->line);    /* 好蠢，打印n个不就可以了嘛 */
}
