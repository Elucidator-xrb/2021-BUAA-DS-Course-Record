#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct dictory
{
    char name[30];
    char num[12];
    struct dictory *link;
} LNode,*Linklist;

Linklist list;

void printList(Linklist list)
{
    Linklist p=list;
    while(p!=NULL)
    {
        printf("%s %s\n",p->name,p->num);
        p=p->link;
    }
}

void readInOrder(int n)
{
    Linklist p,pre,q;
    int i;
    for(i=0;i<n;i++)
    {
        p=(Linklist)malloc(sizeof(LNode));
        scanf("%s%s",p->name,p->num);
        p->link=NULL;

        if(list==NULL || strcmp(p->name,list->name)<0)
        {
            p->link=list;
            list=p;
        }
        else
        {
            q=list;
            while(q!=NULL && strcmp(q->name,p->name)<=0)
            {
                pre=q;
                q=q->link;
            }
            if(strcmp(pre->name,p->name)==0 &&
               strcmp(pre->num,p->num)==0) free(p);
            else
            {
                p->link=q;
                pre->link=p;
            }
        }
    }
    return;
}

void nameDiffer(Linklist list)
{
    Linklist pre=list,p=list->link;
    int i=1;
    char tmp[3];
    while(p!=NULL)
    {
        if(strcmp(pre->name,p->name)==0)
        {
            sprintf(tmp,"_%d",i++);
            strcat(p->name,tmp);
            p=p->link;
        }
        else
        {
            pre=p;
            p=p->link;
            i=1;
        }
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    readInOrder(t);
    nameDiffer(list);
    printList(list);
    return 0;
}
