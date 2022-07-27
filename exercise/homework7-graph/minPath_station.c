#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NodeMax 1000
#define MaxName 50
#define INF 0x3f3f3f3f

typedef struct vertex
{
    char name[MaxName];
    int ischange;
} Station;

typedef struct edge
{
    int wei;
    int lno;
} WeightMap;

Station Gv[NodeMax];
WeightMap Ge[NodeMax][NodeMax];
int Vnum;

int v1,v2;
int Spath[NodeMax];

void buildGraph();
int findVertex(char n[]);
void minPath_Dijkstra();
void printPath();

int main()
{
    buildGraph();

    char v1_n[MaxName],v2_n[MaxName];
    scanf("%s%s",v1_n,v2_n);
    v1=findVertex(v1_n);
    v2=findVertex(v2_n);

    minPath_Dijkstra();
    printPath();
    return 0;
}

void buildGraph()
{
    FILE *fp;
    int i,j,k;
    int lnum,line_no,station_num;
    int vf,vl;//前后结点，连接图时使用

    fp=fopen("bgstations.txt","r");
    fscanf(fp,"%d",&lnum); //线路总数
    for(i=0;i<lnum;i++)
    {
        fscanf(fp,"%d%d",&line_no,&station_num);
        vf=-1;
        for(j=0;j<station_num;j++)
        {
            Station tmp;
            int flag=1;

            fscanf(fp,"%s%d",tmp.name,&tmp.ischange);
/* 错误！非中转站同样可能会重复，所以下面的逻辑错误 */
//            if(tmp.ischange)//是中转站，则判断是否已存在
//            {
//                for(k=0;k<Vnum;k++)
//                {
//                    if(strcmp(tmp.name,Gv[k].name)==0)
//                    {
//                        vl=k;
//                        flag=0;
//                        break;
//                    }
//                }
//            }
//            if(flag)//不是中转站或为新的中转站，需要添加结点
//            {
//                vl=Vnum;
//                Gv[Vnum++]=tmp;
//            }
            for(k=0;k<Vnum;k++)
            {
                if(strcmp(tmp.name,Gv[k].name)==0)
                {
                    vl=k;
                    flag=0;
                    break;
                }
            }
            if(flag)
            {
                vl=Vnum;
                Gv[Vnum++]=tmp;
            }
            if(vf!=-1)//连接图
            {
                Ge[vl][vf].wei=Ge[vf][vl].wei=1; //printf("[%d]%s - [%d]%s : %d\n",vf,Gv[vf].name,vl,Gv[vl].name,Ge[vl][vf].wei);
                Ge[vl][vf].lno=Ge[vf][vl].lno=line_no;
            }
            vf=vl;
        }
    }
    fclose(fp);

    for(i=0;i<Vnum;i++)
        for(j=0;j<Vnum;j++)
            if(i!=j && Ge[i][j].wei==0) Ge[i][j].wei=INF;
    return;
}

int findVertex(char n[])
{
    int i;
    for(i=0;i<Vnum;i++)
        if(strcmp(n,Gv[i].name)==0)
            return i;
    return -1;
}

void minPath_Dijkstra()
{
    int i,j;
    int minwei,v;
    int Sweight[NodeMax]={0};
    int Sfound[NodeMax]={0};

    for(i=0;i<Vnum;i++)
    {
        Sweight[i]=Ge[v1][i].wei;
        Spath[i]=v1;
    }
    Sfound[v1]=1; //初始化

    for(i=0;i<Vnum-1;i++) //轮次：Vnum-1
    {
        minwei=INF;
        for(j=0;j<Vnum;j++) //寻找当前最短路径
        {
            if(!Sfound[j] && Sweight[j]<minwei)
            {
                v=j;
                minwei=Sweight[v];
            }
        }
        Sfound[v]=1;
        if(v==v2) return;
        for(j=0;j<Vnum;j++) //更新路径
        {
            if(!Sfound[j] && minwei+Ge[v][j].wei<Sweight[j])
            {
                Sweight[j]=minwei+Ge[v][j].wei;
                Spath[j]=v;
            }
        }
    }
}

void printPath()
{
    char path[BUFSIZ]={0},buf[BUFSIZ];
    int stack[BUFSIZ]={0},top=-1;
    int v=v2,cnt=0;
    int linef,linel;
    stack[++top]=v2;
    do{ v=Spath[v]; stack[++top]=v; }
    while(v!=v1);

    v=stack[top--];
    linef=linel=Ge[v][stack[top]].lno;
    sprintf(buf,"%s",Gv[v].name);
    strcpy(path,buf); //用此方法：项字符串中持续写入
    cnt=1;
    while(top>-1)
    {
        v=stack[top--]; //当v2弹栈后，需特殊处理
        linel= (top>-1) ? Ge[v][stack[top]].lno : -1;
        if(linef!=linel)
        {
            sprintf(buf,"-%d(%d)-%s",linef,cnt,Gv[v].name);
            strcat(path,buf);
            cnt=0;
        }
        cnt++;
        linef=linel;
    }
    puts(path);
}
