#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node
{
    int name;
    int space;
    struct node *link;
} CNode, *CLinklist;

CLinklist list;
CLinklist pre,cur;

void createList(int n)
{
    CLinklist p,r;
    int i;
    for(i=1;i<=n;i++)
    {
        p=(CLinklist)malloc(sizeof(CNode));
        scanf("%d%d",&p->name,&p->space);

        if(list==NULL) list=p;
        else r->link=p;
        r=p;
    }
    r->link=list;
}

int main()
{
    int n,i;
    int demand;
    CLinklist p,q;

    scanf("%d",&n);
    createList(n);
    cur=list;
    pre=cur->link;
    while(pre->link!=cur) pre=pre->link;

    while(1)
    {
        scanf("%d",&demand);
        if(demand==-1) break;
        else
        {
            p=cur;q=pre;
            while(p->link!=cur)
            {
                if(p->space > demand) p->space-=demand;
                else(p->space == demand)
                {
                    cur=p->link;
                    pre->link=cur;
                    free(p);
                }
                else
                {

                }
            }

        }
    }



    return 0;
}
