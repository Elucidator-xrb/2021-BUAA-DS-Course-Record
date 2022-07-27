#include<stdio.h>
#include<stdlib.h>
#define MaxN 100

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
} BTNode,*BTree;

int bt[MaxN];

BTree buildTreeList(int bt)
{
    BTree ptr[MaxN],tlist;
    int i,j;

    tlist=ptr[0]=(BTree)malloc(sizeof(BTNode));
    ptr[0]->data=bt[0];
    ptr[0]->lchild=NULL;
    ptr[0]->rchild=NULL;                   //建立根结点
    for(i=0;i<MaxN;i++)
    {
        if(bt[i]!=0) //说明此结点存在
        {
            ptr[i]=(BTree)malloc(sizeof(BTNode));
            ptr[i]->data=bt[i];
            ptr[i]->lchild=NULL;
            ptr[i]->rchild=NULL;           //建立新结点

            j=(i-1)/2;//寻找双亲结点位置索引
            if(i-2*j-1==0) ptr[j]->lchild=ptr[i];
            else ptr[j]->rchild=ptr[i];    //将新结点连到树中
        }
    }
    return tlist;
}
