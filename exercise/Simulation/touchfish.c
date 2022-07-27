#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *link;
} LNode, *Linklist;

void createList(int n)
{
    Linklist p,q,r;
    int i;
    for(i=0;i<n;i++)
    {
        p=(Linklist)malloc(sizeof(LNode));
        p->data=item,p->link=NULL;

        if(list==NULL) list=p;
        else r->link=p;
        r=p;
    }
}

void readInOrder()
{
    Linklist pre,p,q;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;
    p->link=NULL;

    if(list==NULL || item<list->data)
    {
        p->link=list;
        list=p;
    }
    else
    {
        q=list;
        while(q!=NULL && item>=list->data)
        {
            pre=q;
            q=q->link;
        }
    }

}
