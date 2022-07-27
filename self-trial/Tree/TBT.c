#include<stdlib.h>
#define MaxN 100
#define NodeMax 50

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
    int lbit,rbit;
} TBTNode, *TBTree
//�����˱�־λ��

TBTree t;/* ԭ����������� */
TBTree T;

//���������������������

//1.����������������������ͬʱ������
//��1���ݹ�
TBTree prior;
TBTree threading()
{
    TBTree head;
    head=(TBTree)malloc(sizeof(TBTNode));
    head->lchild=t��head->rchild=head;
    head->lbit=head->rbit=1;
    prior=head;

    inThread(t);

    prior->rchild=head;
    prior->rbit=0;

    return head;/* ���Ǽٶ���T������ */
}
void inThread(TBTree t)
{
    if(t!=NULL)
    {
        inThread(t->lchild); /* ����������-�ݹ� */

        if(t->lchild==NULL) /* û�������� -- ��ʱ��������t */
        {
            t->lbit=0;
            t->lchild=prior;
        }else t->lbit=1;

        if(prior->rchild==NULL) /* û�������� -- �Ӻ��������prior */
        {
            prior->rbit=0;
            prior->rchild=t;
        }else prior->rbit=1

        prior=t; /* ��¼�µ�prior */

        inThread(t->lchild); /* ����������-�ݹ� */
    }
}
//��2���ǵݹ�
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
//��Ϊ�����ʡ�
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

    return head;/* �ٶ���T���� */
}

//2.����������������ȷ��ĳ��㣨TBTree x����ֱ��ǰ�����
TBTree inPrior(TBTree x)
{
    TBTree s=x->lchild;
    if(x->lbit==1)//��û��������˵��x���������������������������ұߵĽ��
        while(s->rbit==1) s=s->rchild;
    return s;
}

//3.����������������ȷ��ĳ��㣨TBTree x����ֱ�Ӻ�̽��
TBTree inSucc(TBTree x)
{
    TBTree s=x->rchild;
    if(x->rbit==1)
        while(s->lbit==1) s=s->lchild;
    return s;
}

//4.�������������������򣩱���������
void inOrder(TBTree head)
{
    TBTree p=head;
    do{
        p=inSucc(p);
        visit(p) /* �ǿ��� */
    }while(p!=head);
}
