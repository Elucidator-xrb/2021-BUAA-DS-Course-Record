#define MaxN 100
#define Nodemax 50

typedef struct node
{
    int data;
    struct node *lchild,*rchild;
} BTNode, *BTree;

BTree t;

//*二叉树的遍历
//（1）前序遍历-递归
void preOrder(BTree t)/* 根-左-右 */
{
    if(t!=NULL)
    {
        visit(t);/* 表示访问该结点：遍历到该结点时，对执行一种操作 */
        preOrder(t->lchild);
        preOrder(t->rchild);
    }
}
void preOrder_nr(BTree t)//非递归（使用栈辅助实现）
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

//（2）中序遍历-递归
void inOrder(BTree t)/* 左-根-右 */
{
    if(t!=NULL)
    {
        inOrder(t->lchild);
        visit(t);
        inOrder(t->rchild);
    }
}
void inOrder_nr(BTree t)//非递归
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

//（3）后序遍历-递归
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
            flag=fstack[ftop--]; /* flag为0说明该二叉树右子树尚未访问 */

            if(flag==0)
            {
                nstack[++ntop]=p;
                fstack[++ftop]=1;
                p=p->rchild;
            }
            else
            {
                visit(p);
                p=NULL; /* 后序遍历的最后一步 */
            }
        }while(p!=NULL || top>-1)
}

//层序遍历（BFS）使用队列辅助实现
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

//2.判断相似性-递归
int isSimilar(BTree t1,BTree t2)
{
    if(!t1 && !t2) return 0; //NULL宏定义为0
    if(t1 && t2 && isSimilar(t1->lchild,t2->lchild) && isSimilar(t1->rchild,t2->rchild))
        return 1;
    return 0;
}
