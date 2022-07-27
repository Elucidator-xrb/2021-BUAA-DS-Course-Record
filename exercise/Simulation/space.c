#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int start;
    int end;
    struct node *next;
} LNode, *Linklist;

Linklist list;
int N;

void buildList();
void insertInOrder(Linklist p);
void mergeList();
void printList();

int main()
{
    scanf("%d",&N);
    buildList();
    mergeList();
    printList();
    return 0;
}

void buildList()
{
    int i;
    Linklist p;
    for(i=0;i<N;i++)
    {
        p=(Linklist)malloc(sizeof(LNode));
        scanf("%d%d",&p->start,&p->end);
        p->next=NULL;
        insertInOrder(p);
    }
}

void insertInOrder(Linklist p)
{
    Linklist q,pre;
    if(list==NULL || p->start < list->start)
    {
        p->next=list;
        list=p;
    }
    else
    {
        q=list;
        while(q!=NULL && p->start > q->start)
        {
            pre=q;
            q=q->next;
        }
        p->next=q;
        pre->next=p;
    }
}

void mergeList()
{
    Linklist p=list,q=NULL;
    while(p!=NULL && p->next!=NULL)
    {
        if(p->end+1 == p->next->start)
        {
            p->end=p->next->end;
            q=p->next;
            p->next=q->next;
            free(q);
        }
        else p=p->next;
    }
}

void printList()
{
    Linklist p=list;
    while(p!=NULL)
    {
        printf("%d %d\n",p->start,p->end);
        p=p->next;
    }
}
