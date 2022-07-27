#include<stdlib.h>
#define MaxN 100
#define NodeMax 50

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
    int lbit,rbit;
} TBTNode, *TBTree
//增设了标志位域

TBTree t;/* 原二叉树根结点 */
TBTree T;

//这里针对中序线索二叉树

//1.二叉树的线索化：遍历的同时线索化
//（1）递归
TBTree prior;
TBTree threading()
{
    TBTree head;
    head=(TBTree)malloc(sizeof(TBTNode));
    head->lchild=t；head->rchild=head;
    head->lbit=head->rbit=1;
    prior=head;

    inThread(t);

    prior->rchild=head;
    prior->rbit=0;

    return head;/* 我们假定让T接收了 */
}
void inThread(TBTree t)
{
    if(t!=NULL)
    {
        inThread(t->lchild); /* 左子树操作-递归 */

        if(t->lchild==NULL) /* 没有左子树 -- 即时操作，用t */
        {
            t->lbit=0;
            t->lchild=prior;
        }else t->lbit=1;

        if(prior->rchild==NULL) /* 没有右子树 -- 延后操作，用prior */
        {
            prior->rbit=0;
            prior->rchild=t;
        }else prior->rbit=1

        prior=t; /* 记录新的prior */

        inThread(t->lchild); /* 右子树操作-递归 */
    }
}
//（2）非递归
TBTree inthread()
{
    TBTree head,prior,p=t;
    TBTree stack[NodeMax];
    int top;

    head=(TBTree)malloc(sizeof(TBTNode));
    head->lchild=t;head->rchild=head;
    head->lbit=head->rbit=1;
    prior=head;

    do{
        while(p!=NULL)
        {
            stack[++top]=p;
            p=p->lchild;
        }
//是为“访问”
        p=stack[top--];
        if(p->lchild==NULL)
        {
            p->lbit=0;
            p->lchild=prior;
        }else p->lbit=1;
        if(prior->rchild==NULL)
        {
            prior->rbit=0;
            prior->rchild=p;
        }else prior->rbit=1;

        p=p->rchild;
    }while(!p && top>-1);

    prior->rbit=0;
    prior->rchild=head;

    return head;/* 假定让T接收 */
}

//2.线索二叉树（中序）确定某结点（TBTree x）的直接前驱结点
TBTree inPrior(TBTree x)
{
    TBTree s=x->lchild;
    if(x->lbit==1)//若没有线索：说明x有左子树，则找其左子树中最右边的结点
        while(s->rbit==1) s=s->rchild;
    return s;
}

//3.线索二叉树（中序）确定某结点（TBTree x）的直接后继结点
TBTree inSucc(TBTree x)
{
    TBTree s=x->rchild;
    if(x->rbit==1)
        while(s->lbit==1) s=s->lchild;
    return s;
}

//4.利用线索二叉树（中序）遍历二叉树
void inOrder(TBTree head)
{
    TBTree p=head;
    do{
        p=inSucc(p);
        visit(p) /* 非空树 */
    }while(p!=head);
}
