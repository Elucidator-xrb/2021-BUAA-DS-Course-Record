#include<stdio.h>
#include<stdlib.h>
#define MaxV 101

int Vertex[MaxV];
int Edge[MaxV][MaxV];
int v_num,e_num;
int visited[MaxV];
int queue[MaxV],front=-1,rear=-1;

void buildGraph();
void delNode();
void traverseDFS();
void traverseBFS();
void dfs(int v);

int main()
{
    scanf("%d%d",&v_num,&e_num);
    buildGraph();
    traverseDFS();traverseBFS();
    delNode();
    traverseDFS();traverseBFS();
    return 0;
}

void buildGraph()
{
    int i,x,y;
    for(i=0;i<e_num;i++)
    {
        scanf("%d%d",&x,&y);
        Edge[x][y]=Edge[y][x]=1;
        Vertex[x]=Vertex[y]=1;
    }
}

void delNode()
{
    int i,d;
    scanf("%d",&d);
    for(i=0;i<v_num;i++)
        Edge[i][d]=Edge[d][i]=0;
    Vertex[d]=0;
}

void traverseDFS()
{
    int i;
    for(i=0;i<v_num;i++) visited[i]=0;

    dfs(0);
    puts("");
}

void dfs(int i)
{
    int j;
    printf("%d ",i);
    visited[i]=1;
    for(j=0;j<v_num;j++)
        if(Edge[i][j] && !visited[j]) dfs(j);
}

void traverseBFS()
{
    int i,j;int k;
    for(i=0;i<v_num;i++) visited[i]=0;

    queue[++rear]=0;
    visited[0]=1; //注意置1的位置：加入队列便安排好了遍历位置，应该置1，否则若尚未出队会有重复
    while(front!=rear)
    {
        i=queue[++front];
        printf("%d ",i);
        for(j=0;j<v_num;j++)
            if(Edge[i][j] && !visited[j])
                queue[++rear]=j,
                visited[j]=1;
    }
    puts("");
}
