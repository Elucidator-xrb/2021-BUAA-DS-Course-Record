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
    int i,p; //ʹ�����飬���±꼴Ϊ��ַ
    //�洢ʵ������ڣ�����������ָ��ı�־��ͬ������Ļ���int������Ļ���ָ��

    scanf("%d",&tr[1].value);
    tr[1].height=1; //��ʹ��0��Ϊ���ж�Ҷ�ڵ��������;��ʵ���ã���������������ͬ���Ǳض���Ҷ�ڵ�

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
{//֮ǰ�Ǹ���Ҷ�ڵ�����ԣ�˳���ҳ��󣬿��Ž���ģ�������ϰ����
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
        p=tr[p].rchild; //�˴�����lchild���ֵ����˽���1h
    }while(p!=0 || top>-1);
}
