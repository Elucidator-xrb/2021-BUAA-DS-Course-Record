#include<stdlib.h>
#define MaxN 100
#define NodeMax 50

//����������
//����������������
//IPL; EPL=IPL+2n; ASL�ļ���
//n���ڲ���㣬n+1���ⲿ���

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
} BNode, *BTree;

BTree T;

//1.�����������Ľ���-��������
BTree buildSortTree(int k[],int n)
{
    BTree t;
    int i;
    for(i=0;i<n;i++) insertBST(t,k[i]); /* ��ܺ��� */
    return t;
}
//��1���ݹ飨˼·������
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
//��2���ǵݹ�
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

//2.������������ɾ��
//ɾ�����λ�����������Ҷ�ڵ㣬ֻ����/��������������������
void deleteBST(BTree cur,BTree par)//���ṩ˫�׽��
{
    BTree p,pre; /* p������Ҫ���¼޽ӵ�par����ϵ��� */
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


//3.�����������Ĳ��ң�����Ŀ���㣩
//��1���ǵݹ�
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
//��2���ݹ�
BTree searchBST(int item,BTree t)
{
    if(t==NULL) return NULL;
    if(t->data==item) return t;

    if(p->data>item) searchBST(item,t->lchild);
    else searchBST(item,t->rchild);
}
