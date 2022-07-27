#include<stdio.h>
#include<string.h>

typedef struct node
{
    char no[5];
    char destn[50];
    int dist_no;
} Train;

typedef struct place
{
    int distance;
    char name[50];
} Place;

Train tr[60];
Place pl[60];
int H[1000];//������ϣ��
int t_n,p_n;

Train stacka[60];
int topa=-1,end=-1;
Train stackb[60];
int topb=-1;
Train stackc[60];
int topc=-1;

int pop_n,push_n;

void buildHash();
int hash(char name[]);
void buildTrain();
void operateTrain();
void printInfo();

int main()
{
    scanf("%d",&p_n);
    buildHash();
    scanf("%d",&t_n);
    buildTrain();
    operateTrain();
    printInfo();
    return 0;
}

void buildHash()
{
    int i,j,total;
    char tmp[60];
    for(i=0;i<p_n;i++)
        scanf("%s%d",pl[i].name,&pl[i].distance);
    //qsort();
    for(i=0;i<p_n;i++)
    {
        total=0;
        strcpy(tmp,pl[i].name);
        for(j=0;tmp[j]!='\0';j++)
            total+=(tmp[j]-96);
        while(H[total]) total++;
        H[total]=i;
    }
}

int hash(char name[])
{
    int i,total=0;
    for(i=0;name[i]!='\0';i++)
        total+=(name[i]-96);
    return H[total]; //����Ѱַд����ȥ�ˣ���װû�г�ͻ��
}

void buildTrain()
{
    int i;
    for(i=0;i<t_n;i++)
    {
        scanf("%s%s",tr[i].no,tr[i].destn);
        tr[i].dist_no=hash(tr[i].destn);
        stacka[++top]=tr[i];
    }
}

void operateTrain()
{
    int i,j;
    int farest=p_n-1;//��¼��ǰ��Ŀ�ĵ���Զ�ı��
    Train tmp;
    while(topa>-1)
    {
        tmp=stacka[topa--];
        stackb[++topb]=tmp;
    }// ��ʼ��������b��

    while(1)
    {
        i=topb;
        while()
    }

}

void printInfo()
{

}
