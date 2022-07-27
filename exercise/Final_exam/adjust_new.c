#include<stdio.h>
#include<stdlib.h>

typedef struct tre
{
    int no;
    int child[3];
    int layer;
} Treeplane;

Treeplane tr[300];

int crowd[500][2];
int Cnum;

int order[500];
int Onum;

void buildTree();
void getCrowdOrder();
void getTreeOrder();
void printAdj();
int cmp(const void *a,const void *b)
{
    int *aa=(int *)a;
    int *bb=(int *)b;

    if(aa[1]!=bb[1])
        return (aa[1]<bb[1])-(aa[1]>bb[1]);
    else
        return (aa[0]>bb[0])-(aa[0]<bb[0]);
}

//int cmp2(const void *a,const void *b)
//{
//    int *aa=(int *)a;
//    int *bb=(int *)b;
//    return (aa[0]>bb[0])-(aa[0]<bb[0]);
//}

int main()
{
    buildTree();
    getCrowdOrder();
    //getTreeOrder();
    //printAdj();
    return 0;
}

void buildTree()
{
    int n,a;
    while(1)
    {
        scanf("%d",&n);
        if(n==-1) break;

//        if(n==100) tr[n].layer=1; //100处高度为1
//        else tr[n].layer=tr[ tr[n] ]

        scanf("%d",&tr[n].child[0]);
        if(tr[n].child[0]<100) Cnum++;

        scanf("%d",&a);
        if(a==-1) continue;
        else
        {
            tr[n].child[1]=a;
            if(a<100) Cnum++;
        }

        scanf("%d",&a);
        if(a==-1) continue;
        else
        {
            tr[n].child[2]=a;
            if(a<100) Cnum++;
        }
        scanf("%d",&a);//最后一个-1
    }
}

void getCrowdOrder()
{
    int i;
    int start,end;
    for(i=0;i<Cnum;i++)
    {
        scanf("%d%d",&crowd[i][0],&crowd[i][1]);
    }
    qsort(crowd,Cnum,sizeof(crowd[0]),cmp);
//    for(i=0;i<Cnum-1;i++)
//    {
//        if(crowd[i][1]==crowd[i+1][1])
//        {
//            start=i;
//            while(i<Cnum && crowd[i+1][1]==crowd[start][1]) i++;
//            end=i;
//            qsort(crowd+start,end-start+1,sizeof(crowd[0]),cmp2);
//        }
//    }
//
puts("");
    for(i=0;i<Cnum;i++)
        printf("%d %d\n",crowd[i][0],crowd[i][1]);
}

void getTreeOrder()
{
    int queue[2000]={0},p=0;
    int front,rear;
    queue[0]=100;
    front=-1;
    rear=0;

    while(front<rear)
    {
        p=queue[++front];
        for(int i=0;i<3;i++)
        {
            if(tr[p].child[i]<100 && tr[p].child[i]>0) order[Onum++]=tr[p].child[i];
            else queue[++rear]=tr[p].child[i];
        }
    }
//puts("");
//    for(int i=0;i<Onum;i++)
//        printf("%d ",order[i]);
}

void printAdj()
{
    int i;
    for(i=0;i<Cnum;i++)
        printf("%d<-%d\n",order[i],crowd[i][0]);
}
