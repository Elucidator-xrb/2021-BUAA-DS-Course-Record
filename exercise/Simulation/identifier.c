#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node
{
    char ch[40];
    struct node *link;
} LNode, *Linklist;

Linklist list;

int isident(char ch)
{
    return isdigit(ch) || isalpha(ch) || ch=='_';
}

void readInOrder(char tmp[])
{
    Linklist p,pre,q;       //printf("%s ",tmp); putchar(tmp[0]);
    if(isdigit(tmp[0])) return;
    else
    {//printf(" imhere! ");
        p=(Linklist)malloc(sizeof(LNode));
        strcpy(p->ch,tmp);
        p->link=NULL;

        if(list==NULL || strcmp(p->ch,list->ch)>0)
        {
            p->link=list;
            list=p;
        }
        else
        {
            q=list;
            while(q!=NULL && strcmp(q->ch,p->ch)>0)
            {
                pre=q;
                q=q->link;
            }
            if(q!=NULL && strcmp(q->ch,p->ch)==0)
            {
                free(p);
                return;
            }
            p->link=q;
            pre->link=p;
        }
    }
}

void printList()
{
    Linklist p=list;
    while(p!=NULL)
    {
        printf("%s ",p->ch);
        p=p->link;
    }
}

int main()
{
    int i,j,cnt=0;
    char buf[210],tmp[40]={0};
    gets(buf);
    for(i=0;buf[i]!=';';i++)
    {//printf("[%d]",i);
        if(isident(buf[i])) tmp[cnt++]=buf[i];
        else if(cnt!=0)
        {
            tmp[cnt]='\0';
            readInOrder(tmp);，，，，
            cnt=0;
        }
//    printf("[");printList();printf("]");
//    puts("");
    }
    if(cnt!=0)
    {
        tmp[cnt]='\0';
        readInOrder(tmp);
    }
    printList();

    return 0;
}
