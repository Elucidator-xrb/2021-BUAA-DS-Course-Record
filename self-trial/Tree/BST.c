#include<stdlib.h>
#define MaxN 100
#define NodeMax 50

//二叉排序树
//中序遍历则得有序列
//IPL; EPL=IPL+2n; ASL的计算
//n个内部结点，n+1个外部结点

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
} BNode, *BTree;

BTree T;

//1.二叉排序树的建立-插入排序
BTree buildSortTree(int k[],int n)
{
    BTree t;
    int i;
    for(i=0;i<n;i++) insertBST(t,k[i]); /* 框架函数 */
    return t;
}
//（1）递归（思路清晰）
void insertBST(BTree t,int item)
{
    if(t==NULL)
    {
        t=(BTree)malloc(sizeof(BNode));
        t->data=item;
        t->lchild=t->rchild=NULL;
    }
    else
    {
        if(item < t->data) insertBST(t->lchild,item);
        else insertBST(t->rchild,item);
    }
}
//（2）非递归
void insertBST_nr(BTree t,int item)
{
    BTree p,q=t;

    p=(BTree)malloc(sizeof(BNode));
    p->data=item;
    p->lchild=p->rchild=NULL;

    if(q==NULL) t=p;
    else
    {
        while(1)
        {
            if(item < q->data)
            {
                if(q->lchild==NULL) q=q->lchild;
                else{ q->lchild=p;break; }
            }
            else
            {
                if(q->rchild==NULL) q=q->rchild;
                else{ q->rchild=p;break; }
            }
        }
    }
}

//2.二叉排序树的删除
//删除结点位置四种情况：叶节点，只有左/右子树，左右子树都有
void deleteBST(BTree cur,BTree par)//需提供双亲结点
{
    BTree p,pre; /* p是最终要重新嫁接到par结点上的树 */
    int flag=0;

    if(cur->lchild==NULL)
    {
        if(cur==t) t=cur->rchild;
        else p=cur->rchild,flag=1;
    }
    else if(cur->rchild==NULL)
    {
        if(cur==t) t=cur->lchild;
        else p=cur->lchild,flag=1;
    }
    else
    {
        p=cur->rchild,pre=cur;
        while(p->lchild!=NULL)
        {
            pre=p;
            p=p->lchild;
        }

        p->lchild=cur->lchild;
        if(pre!=cur)
            pre->lchild=p->rchild,
            p->rchild=cur->rchild;

        if(cur==t) t=p;
        else flag=1;
    }

    if(flag)
        if(par->rchild==cur) par->rchild=p;
        else par->lchild=p;

    return 0;
}


//3.二叉排序树的查找（返回目标结点）
//（1）非递归
BTree searchBST_nr(int item)
{
    BTree p=t;
    while(p!=NULL)
    {
        if(p->data==item) return p;
        if(p->data>item) p=p->lchild;
        else p=p->rchild;
    }
    return NULL;
}
//（2）递归
BTree searchBST(int item,BTree t)
{
    if(t==NULL) return NULL;
    if(t->data==item) return t;

    if(p->data>item) searchBST(item,t->lchild);
    else searchBST(item,t->rchild);
}
