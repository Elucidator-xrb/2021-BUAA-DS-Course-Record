#include<stdio.h>
#include<string.h>
#define INF 0x3f3f3f3f

typedef struct node
{
    int type;
    int par;
    int son[8];
    int layer;
}Tree;

Tree tr[301];//为了使空结点处直接赋为0，将所有id进行+1的偏移

int Print[301];//记录打印机结点索引
char Path[301];
int Pmin=INF;
int Pnum;

int N,target;

//void getFile();

void buildTree();
void postTraverse(int cur);
void getPath(int id1,int id2);
void printPath();

int main()
{
//    getFile();
    scanf("%d%d",&N,&target);
    target++;//target_id偏移
    buildTree();
    postTraverse(1);
    printPath();
    return 0;
}

//void getFile()
//{
//    FILE *fp;
//    int i,cnt=0;
//    int a,b,c,d;
//    fp=fopen("in.txt","r");
//    do{
//        i=fscanf(fp,"%d%d%d%d",&a,&b,&c,&d);
//        cnt++;
//        printf("%-3d%-3d%-3d%-3d || ",a,b,c,d);
//        //printf("%d %d %d %d\n",a,b,c,d);
//        if(cnt%4==0) printf("\n");
//    }while(i==4);
//}

void buildTree()
{
    FILE *fp;
    int i,id,port;
    char buf[20];//丢垃圾

    fp=fopen("in.txt","r");
    fgets(buf,19,fp);
    tr[1].layer=1;
    for(i=1;i<N;i++)
    {
        fscanf(fp,"%d",&id);
        id++;//id偏移
        fscanf(fp,"%d%d%d",&tr[id].type,&tr[id].par,&port);
        tr[id].par++;//par偏移
        tr[id].layer=tr[ tr[id].par ].layer+1;
        tr[ tr[id].par ].son[port]=id;
        if(tr[id].type==2) Print[id]=1;
    }
    fclose(fp);
}

void postTraverse(int cur)
{
    int i;
    if(Print[cur])
    {
        //printf("getPath:%d->",cur);
        getPath(cur,target);
    }

    if(tr[cur].type==0)
    {
        for(i=0;i<8;i++)
            if(tr[cur].son[i])
                postTraverse(tr[cur].son[i]);
    }
    return;
}

void getPath(int id1,int id2)
{
    int cnt=0;
    int id_p=id1,id_c=id2;
    int stack[N],top=-1;//记录打印机向上的路径
    while(tr[id1].layer>tr[id2].layer)
    {
        stack[++top]=id1;
        id1=tr[id1].par,cnt++;
    }
    while(tr[id1].layer<tr[id2].layer)
        id2=tr[id2].par,cnt++;

    while(id1!=id2)
    {
        stack[++top]=id1;
        id1=tr[id1].par;
        id2=tr[id2].par;
        cnt+=2;
    }//printf("[%d %d] %d -",id_p,id_c,cnt);
    if(cnt<Pmin)
    {
        int i=0;
        Pmin=cnt; //printf(" %d %d\n",Pnum,Pmin);
        do{
            id_c=tr[id_c].par;
            Path[i++]=id_c;
        }while(id_c!=id1);
        while(top>-1)
        {
            id_p=stack[top--];
            Path[i++]=id_p;
        }
    }
}

void printPath()
{
    int j;
//    for(i=0;i<=Pnum;i++) 好傻，题目要求只打印一组
//    {
    printf("%d ",Path[Pmin-1]-1);
    for(j=0;j<Pmin-1;j++)
        printf("%d ",Path[j]-1);
//    }
}
