#include<stdio.h>
#include<stdlib.h>
#define MaxNode 500
#define INF 0x3f3f3f3f

typedef struct edge
{
    int id;
    int wei;
} Etype;

Etype GE[MaxNode][MaxNode];
int Nnum,Enum;
int Seleted_id[MaxNode];
int Snum,total;

int lowcost[MaxNode]; //lowcost[k]记录k点到树中最短边
int teend[MaxNode];   //teend[k]记录k点到树种最短边的另一在树中的端点

void buildGraph();
void minSpan_Prim();
int compar(const void *a,const void *b)
{
    const int *aa=a;
    const int *bb=b;
    return (*aa > *bb)-(*aa < *bb);
}

int main()
{
    int i;
    scanf("%d%d",&Nnum,&Enum);
    buildGraph();
    minSpan_Prim();
    qsort(Seleted_id,Snum,sizeof(int),compar);
    printf("%d\n",total);
    for(i=0;i<Snum;i++)
        printf("%d ",Seleted_id[i]);
    return 0;
}

void buildGraph()
{
    int i,id,v1,v2,w;
    for(i=0;i<Nnum;i++)
        for(w=0;w<Nnum;w++)
            GE[i][w].wei=INF;
    for(i=0;i<Enum;i++)
    {
        scanf("%d%d%d%d",&id,&v1,&v2,&w);
        GE[v1][v2].id=id;
        GE[v1][v2].wei=w;
        GE[v2][v1]=GE[v1][v2];
    }
}

void minSpan_Prim()
{
    int i,j,k,mincost;
    int lowcost[Nnum]; //lowcost[k]记录k点到树中最短边
    int teend[Nnum];   //teend[k]记录k点到树种最短边的另一在树中的端点

    lowcost[0]=teend[0]=0;
    for(j=1;j<Nnum;j++)
        teend[j]=0,lowcost[j]=GE[0][j].wei;//初始化
    for(i=1;i<Nnum;i++)
    {
        mincost=INF;
        for(j=1;j<Nnum;j++)
        {
            if(lowcost[j]>0 && mincost>lowcost[j])
            {
                mincost=lowcost[j];
                k=j;
            }
        }
        Seleted_id[Snum++]=GE[teend[k]][k].id;
        total+=GE[teend[k]][k].wei;
        lowcost[k]=0;
        for(j=1;j<Nnum;j++)
        {
            if(GE[k][j].wei<lowcost[j])
            {
                lowcost[j]=GE[k][j].wei;
                teend[j]=k;
            }
        }
    }
}
