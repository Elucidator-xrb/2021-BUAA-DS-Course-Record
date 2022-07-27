#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 210

typedef struct s
{
    char time[10];
    int no;
    int stu_n;
    char name[20];
} StuRec;

StuRec stu[MAX],abnorm[MAX];
int N,aN;

void readIn();
void selectAb();
void printAb();
int cmp(const void *a,const void *b)
{
    StuRec *aa=(StuRec *)a;
    StuRec *bb=(StuRec *)b;
    return ( (*aa).stu_n>(*bb).stu_n ) - ( (*aa).stu_n<(*bb).stu_n );
}

int main()
{
    scanf("%d",&N);
    readIn();
    selectAb();
    printAb();
    return 0;
}

void readIn()
{
    for(int i=0;i<N;i++)
        scanf("%s%d%d%s",stu[i].time,&stu[i].no,&stu[i].stu_n,stu[i].name);
    return;
}

void selectAb()
{
    int tmp;
    qsort(stu,N,sizeof(stu[0]),cmp);//puts("");
//    for(int i=0;i<N;i++)
//        printf("%s %d %d %s\n",stu[i].time,stu[i].no,stu[i].stu_n,stu[i].name);
    for(int i=0;i<N-1;i++)
    {
        if(stu[i].stu_n==stu[i+1].stu_n)
        {
            if(stu[i].no!=stu[i+1].no)
            {
                abnorm[aN++]=stu[i];
                tmp=stu[i].stu_n;
                while(i+1<N && stu[i+1].stu_n==tmp)i++;
            }
        }
    }
}

void printAb()
{//puts("");
    for(int i=0;i<aN;i++)
        printf("%d %s\n",abnorm[i].stu_n,abnorm[i].name);
}
