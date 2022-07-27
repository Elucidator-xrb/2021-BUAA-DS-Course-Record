#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int num;
    struct node *link;
} LNode,*Linklist;

Linklist mlist;

void createList(int n)
{
    Linklist p,r;
    int i;
    for(i=1;i<=n;i++)
    {
        p=(Linklist)malloc(sizeof(LNode));
        p->num=i,p->link=NULL;

        if(mlist==NULL) mlist=p;
        else r->link=p;
        r=p;
    }
    r->link=mlist;
}

int select(int m,int q)
{
    Linklist p=mlist,pre;
    int i;
    for(i=1;i<q;i++)
    {
        pre=p;
        p=p->link;
    }                     //移动到开始位置
    while(p->link!=p)
    {
        for(i=1;i<m;i++)
        {
            pre=p;
            p=p->link;
        }
        pre->link=p->link;
        free(p);
        p=pre->link;
    }
    return p->num;
}

void printList()
{
    Linklist p=mlist;
    printf("%d ",p->num);
    p=p->link;
    while(p!=mlist)
    {
        printf("%d ",p->num);
        p=p->link;
    }
}

int main()
{
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    createList(n);
    printf("%d",select(m,q));
    return 0;
}
