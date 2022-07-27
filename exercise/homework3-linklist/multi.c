#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int coef;
    int exp;
    struct node *link;
} PNode, *PLinklist;

PLinklist lista,listb,listc;

void printList(PLinklist list)
{
    PLinklist p=list;
    while(p!=NULL)
    {
        printf("%d %d ",p->coef,p->exp);
        p=p->link;
    }
    puts("");
}

PLinklist readPoly()
{
    PLinklist list=NULL;
    PLinklist p,r;
    do
    {
        p=(PLinklist)malloc(sizeof(PNode));
        scanf("%d%d",&p->coef,&p->exp);
        p->link=NULL;
        if(list==NULL) list=p;
        else r->link=p;
        r=p;
    }while(getchar()!='\n');//当检测到行末'\n'后结束
    return list;
}

void insertInOrder(PLinklist r)//按序插入，合并同类项
{
    PLinklist p=listc,pre;
    if(listc==NULL || listc->exp < r->exp)
    {
        r->link=listc;
        listc=r;
    }
    else
    {
        while(p!=NULL && p->exp > r->exp)
        {
            pre=p;
            p=p->link;
        }
        if(p!=NULL && p->exp == r->exp)
        {
            p->coef += r->coef;
            free(r);
        }
        else
        {
            r->link=p;
            pre->link=r;
        }
    }
}

void multiPoly()
{
    PLinklist p,q,r;
    for(p=lista;p!=NULL;p=p->link)
    {
        for(q=listb;q!=NULL;q=q->link)
        {
            r=(PLinklist)malloc(sizeof(PNode));
            r->coef = p->coef * q->coef;
            r->exp = p->exp + q->exp;
            r->link=NULL;
            insertInOrder(r);
        }
    }
}

int main()
{
    lista=readPoly(); listb=readPoly();
    multiPoly();
    printList(listc);
    return 0;
}
