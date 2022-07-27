#define MaxN 100
#define Nodemax 50

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
} BTNode, *BTree;

BTree t;

//2.���ٶ����������������-�ݹ�
void destroyTree(BTree t)/* ����ɾ���������ɵݹ�,tΪ��������*/
{
    if(t!=NULL)
    {
        destroy(t->lchild);
        destroy(t->rchild);
        free(t);
    }
}
void clearTree()/*��Ϊ�����Ĳ�����ͬ����Ϊ���ƺ�����ʹ��֧���Եݹ�*/
{
    destroy(t);
    t=NULL;
}

//6.��Ŀ�������ڲ�Σ����������-�ǵݹ�
int layerFind(BTree t,int item)
{
    BTree nstack[Nodemax],p=t;
    int fstack[Nodemax],top=-1;
    int flag;
    do{
        while(p!=NULL)   /* �������ı��� */
        {
            nstack[++top]=p;
            fstack[top]=0;
            p=p->lchild;
        }
        p=nstack[top];
        flag=fstack[top--];
        if(flag==0) /* �������ı��� */
        {
            nstack[++top]=p;
            fstack[top]=1;
            p=p->rchild;
        }
        else        /* ����-�����и����ķ��� */
        {
            if(p->data==item) return top+2;
            p=NULL;
        }
    }while(p!=NULL || top>-1);
}

//7.ɾ��ָ�����Ϊ�����Ķ�����,���ظ��º�Ķ�����
//��Ϊ��������1�����ң�������������,�ô�ѡǰ��2��ɾ�����������
BTree delNode(BTree t,int item)
{
    BTree stack[Nodemax],p=t,q;/* q��¼����㣬Ϊ���жϷ���������p������������������ */
    int top=-1;
    if(t->data==item)/* �ܸ���㵥������ */
    {
        destroyTree(t);
        return NULL;
    }
    else
    {
        do{
            while(p!=NULL)
            {
                if(p->data==item) /* ǰ��-�ȷ��ʸ���� */
                {
                    if(q->lchild==p) q->lchild=NULL;
                    else q->rchild=NULL;
                    destroyTree(p);
                    return t;
                }
                stack[++top]=q=p;
                p=p->lchild; /* ���������� */
            }
            q=p=stack[top--];
            p=p->rchild;     /* ���������� */
        }while(p!=NULL && top>-1)
    }
}

//8.����������������λ�ã���α�����-�ǵݹ�
void exchangeTree(BTree t)
{
    BTree queue[Nodemax],p=t,tmp;
    int front=-1,rear=0;
    if(t!=NULL)
    {
        queue[rear]=t->data;
        while(front<rear)
        {
            /* ����Ϊ��������ǰ�������������� */
            p=queue[++front];
            tmp=p->lchild;
            p->lchild=p->rchild;
            p->rchild=tmp;

            if(p->lchild!=NULL) queue[++rear]=p->lchild;
            if(p->rchild!=NULL) queue[++rear]=p->rchild;
        }
    }
}
