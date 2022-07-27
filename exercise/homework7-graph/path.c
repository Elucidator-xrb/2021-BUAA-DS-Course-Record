#include<stdio.h>
#include<stdlib.h>
#define MaxNode 1010

typedef struct edge
{
    int eno;
    int adjvex;
    struct edge *next;
} ENode, *ELink;

int node_n,edge_n;
ELink G[MaxNode];
int visited[MaxNode];
int path[MaxNode];

void buildGraph();
void insertInOrder(int v,int e,int adjv);
void eDFS(int v,int layer);
void printPath(int layer);

int main()
{int i;
    scanf("%d%d",&node_n,&edge_n);
    buildGraph();
    eDFS(0,0);
    return 0;
}

void buildGraph()
{
    int i,v1,v2,e;
    for(i=0;i<edge_n;i++)
    {
        scanf("%d%d%d",&e,&v1,&v2);
        insertInOrder(v1,e,v2);
        insertInOrder(v2,e,v1);
    }
}

void insertInOrder(int v,int e,int adjv)
{
    ELink p,q,pre;
    p=(ELink)malloc(sizeof(ENode));
    p->eno=e;p->adjvex=adjv;
    p->next=NULL;

    if(G[v]==NULL || G[v]->eno > p->eno)
        p->next=G[v],
        G[v]=p;
    else
    {
        q=G[v];
        while(q!=NULL && q->eno < p->eno)
        {
            pre=q;
            q=q->next;
        }
        p->next=q;
        pre->next=p;
    }
}

void eDFS(int v,int layer)
{
    ELink p;
    visited[v]=1;
    if(v==node_n-1)
    {
        printPath(layer);
        return;
    }
    for(p=G[v];p!=NULL;p=p->next)
    {
        if(!visited[p->adjvex])
        {
            path[layer]=p->eno;
            eDFS(p->adjvex,layer+1);
            visited[p->adjvex]=0;
        }
    }
}

void printPath(int layer)
{
    int i;
    for(i=0;i<layer;i++)
        printf("%d ",path[i]);
    puts("");
}
