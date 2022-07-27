#define MaxN 100
#define Nodemax 50

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
} BTNode, *BTree;

BTree t;

//*�������ı���
//��1��ǰ�����-�ݹ�
void preOrder(BTree t)/* ��-��-�� */
{
    if(t!=NULL)
    {
        visit(t);/* ��ʾ���ʸý�㣺�������ý��ʱ����ִ��һ�ֲ��� */
        preOrder(t->lchild);
        preOrder(t->rchild);
    }
}
void preOrder_nr(BTree t)//�ǵݹ飨ʹ��ջ����ʵ�֣�
{
    BTree stack[MaxN],p=t;
    int top=-1;
    if(t!=NULL)
        do{
            while(p!=NULL)
            {
                visit(p);
                stack[++top]=p;
                p=p->lchild;
            }
            p=stack[top--];
            p=p->rchild;
        }while(p!=NULL || top>-1);
}

//��2���������-�ݹ�
void inOrder(BTree t)/* ��-��-�� */
{
    if(t!=NULL)
    {
        inOrder(t->lchild);
        visit(t);
        inOrder(t->rchild);
    }
}
void inOrder_nr(BTree t)//�ǵݹ�
{
    BTree stack[MaxN],p=t;
    int top=-1;
    if(t!=NULL)
        do{
            while(p!=NULL)
            {
                stack[++top]=p;
                p=p->lchild;
            }
            p=stack[top--];
            visit(p);
            p=p->rchild;
        }while(p!=NULL || top>-1)
}

//��3���������-�ݹ�
void postOrder(BTree t)
{
    if(t!=NULL)
    {
        postOrder(t->lchild);
        postOrder(t->rchild);
        vist(t);
    }
}
void postOrder(BTree t)
{
    BTree nstack[MaxN],p=t;
    int fstack[MaxN],ntop=-1,ftop=-1;
    int flag;
    if(t!=NULL)
        do{
            while(p!=NULL)
            {
                nstack[++ntop]=p;
                fstack[++ftop]=0;
                p=p->lchild;
            }

            p=nstack[ntop--];
            flag=fstack[ftop--]; /* flagΪ0˵���ö�������������δ���� */

            if(flag==0)
            {
                nstack[++ntop]=p;
                fstack[++ftop]=1;
                p=p->rchild;
            }
            else
            {
                visit(p);
                p=NULL; /* ������������һ�� */
            }
        }while(p!=NULL || top>-1)
}

//���������BFS��ʹ�ö��и���ʵ��
void layOrder(BTree t)
{
    BTree queue[Nodemax],p=t;
    int front=-1;rear=0;
    queue[0]=p;

    while(front<rear)
    {
        p=queue[front++];
        visit(p);
        if(p->lchild!=NULL) queue[++rear]=p->lchild;
        if(p->rchild!=NULL) queue[++rear]=p->rchild;
    }
}

//2.�ж�������-�ݹ�
int isSimilar(BTree t1,BTree t2)
{
    if(!t1 && !t2) return 0; //NULL�궨��Ϊ0
    if(t1 && t2 && isSimilar(t1->lchild,t2->lchild) && isSimilar(t1->rchild,t2->rchild))
        return 1;
    return 0;
}
