#define MaxN 100
#define Nodemax 50

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
} BTNode, *BTree;

BTree t;

//2.销毁二叉树（后序遍历）-递归
void destroyTree(BTree t)/* 具体删除操作，可递归,t为任意根结点*/
{
    if(t!=NULL)
    {
        destroy(t->lchild);
        destroy(t->rchild);
        free(t);
    }
}
void clearTree()/*因为根结点的操作不同，作为控制函数，使旁支可以递归*/
{
    destroy(t);
    t=NULL;
}

//6.求目标结点所在层次（后序遍历）-非递归
int layerFind(BTree t,int item)
{
    BTree nstack[Nodemax],p=t;
    int fstack[Nodemax],top=-1;
    int flag;
    do{
        while(p!=NULL)   /* 左子树的遍历 */
        {
            nstack[++top]=p;
            fstack[top]=0;
            p=p->lchild;
        }
        p=nstack[top];
        flag=fstack[top--];
        if(flag==0) /* 右子树的遍历 */
        {
            nstack[++top]=p;
            fstack[top]=1;
            p=p->rchild;
        }
        else        /* 后序-最后进行父结点的访问 */
        {
            if(p->data==item) return top+2;
            p=NULL;
        }
    }while(p!=NULL || top>-1);
}

//7.删除指定结点为根结点的二叉树,返回更新后的二叉树
//分为两步：（1）查找，遍历方法随意,该处选前序（2）删除，后序遍历
BTree delNode(BTree t,int item)
{
    BTree stack[Nodemax],p=t,q;/* q记录父结点，为了判断符合条件的p是左子树还是右子树 */
    int top=-1;
    if(t->data==item)/* 总根结点单独讨论 */
    {
        destroyTree(t);
        return NULL;
    }
    else
    {
        do{
            while(p!=NULL)
            {
                if(p->data==item) /* 前序-先访问父结点 */
                {
                    if(q->lchild==p) q->lchild=NULL;
                    else q->rchild=NULL;
                    destroyTree(p);
                    return t;
                }
                stack[++top]=q=p;
                p=p->lchild; /* 左子树遍历 */
            }
            q=p=stack[top--];
            p=p->rchild;     /* 右子树遍历 */
        }while(p!=NULL && top>-1)
    }
}

//8.交换所有左右子树位置（层次遍历）-非递归
void exchangeTree(BTree t)
{
    BTree queue[Nodemax],p=t,tmp;
    int front=-1,rear=0;
    if(t!=NULL)
    {
        queue[rear]=t->data;
        while(front<rear)
        {
            /* 访问为：交换当前父结点的左右子树 */
            p=queue[++front];
            tmp=p->lchild;
            p->lchild=p->rchild;
            p->rchild=tmp;

            if(p->lchild!=NULL) queue[++rear]=p->lchild;
            if(p->rchild!=NULL) queue[++rear]=p->rchild;
        }
    }
}
