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
    ptr[0]->rchild=NULL;                   //���������
    for(i=0;i<MaxN;i++)
    {
        if(bt[i]!=0) //˵���˽�����
        {
            ptr[i]=(BTree)malloc(sizeof(BTNode));
            ptr[i]->data=bt[i];
            ptr[i]->lchild=NULL;
            ptr[i]->rchild=NULL;           //�����½��

            j=(i-1)/2;//Ѱ��˫�׽��λ������
            if(i-2*j-1==0) ptr[j]->lchild=ptr[i];
            else ptr[j]->rchild=ptr[i];    //���½����������
        }
    }
    return tlist;
}
