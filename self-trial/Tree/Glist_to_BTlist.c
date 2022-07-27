#include<stdio.h>
#include<stdlib.h>
#define MaxN 100

/* Input:A(B(D,E(G)),C(f(,H)))@ */

typedef struct node
{
    char data;
    struct node *lchild, *rchild;
}BTNode,*BTree;

BTree T=NULL;

BTREE createTree()
{
    BTree stack[MaxN],p,tlist=NULL;
    int top=-1,op=1;
    char ch;

    while(1)
    {
        scanf("%c",&ch);
        switch(ch)
        {
            case '@':return tlist;
            case '(':
                stack[++top]=p;
                op=1;
                break;
            case ')':top--;break;
            case ',':op=2;break;
            default:
                p=(BTree)malloc(sizeof(BTNode));
                p->data=ch;
                p->lchild=NULL;
                p->rchild=NULL;
                if(tlist==NULL) T=p;
                else if(op==1) stack[top]->lchild=p;
                else if(op==2) stack[top]->rchild=p;
        }
    }
}
