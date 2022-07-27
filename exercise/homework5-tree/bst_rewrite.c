#include<stdio.h>
#include<stdlib.h>
#define MaxN 201

typedef struct node1
{
    int value;
    int lchild,rchild;
    int height;
} Treearray;

Treearray tr[MaxN];
int N;

void buildBST();
void printLeaf();

int main()
{
    scanf("%d",&N);
    buildBST();
    printLeaf();
    return 0;
}

void buildBST()
{
    int i,p; //使用数组，则下标即为地址
    //存储实体均存在，不过是用于指向的标志不同：数组的话用int；链表的话用指针

    scanf("%d",&tr[1].value);
    tr[1].height=1; //不使用0是为了判断叶节点带来便利;其实不用，左右子树索引相同，那必定是叶节点

    for(i=2;i<=N;i++)
    {
        scanf("%d",&tr[i].value);
        p=1;
        while(1)
        {
            if(tr[i].value<tr[p].value)
            {
                if(tr[p].lchild)
                    p=tr[p].lchild;
                else
                {
                    tr[p].lchild=i;
                    tr[i].height=tr[p].height+1;
                    break;
                }
            }
            else
            {
                if(tr[p].rchild)
                    p=tr[p].rchild;
                else
                {
                    tr[p].rchild=i;
                    tr[i].height=tr[p].height+1;
                    break;
                }
            }
        }
    }
}

void printLeaf()
{//之前是根据叶节点的特性，顺序找出后，快排解决的；现在练习遍历
    int p=1;
    int stack[N],top=-1;
    do{
        while(p!=0)
        {
            stack[++top]=p;
            p=tr[p].lchild;
        }  //for(int i=0;i<top;i++) printf("[%d]",tr[stack[i]].value);puts("");
        p=stack[top--]; //printf("%d ",tr[p].value);
        if(tr[p].lchild==tr[p].rchild)
            printf("%d %d\n",tr[p].value,tr[p].height);
        p=tr[p].rchild; //此处错打成lchild，又调试了将近1h
    }while(p!=0 || top>-1);
}
