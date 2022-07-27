#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HashNum 1001

typedef struct stu
{
    char name[21];
    int num;
    int len;
} StuUtilize;

StuUtilize stu[100];
int RecN,StuN;

typedef struct node
{
    int num;
    int place;
    struct node *link;
} LNode, *LinkList;

LinkList HT[1000];

void checkHash(StuUtilize tmp);
int hash(int num);

int cmp(const void *a,const void *b)
{
    StuUtilize *aa=(StuUtilize *)a;
    StuUtilize *bb=(StuUtilize *)b;
    if((*aa).len!=(*bb).len)
        return ( (*aa).len>(*bb).len ) - ( (*aa).len<(*bb).len );
    else
        return ( (*aa).num>(*bb).num ) - ( (*aa).num<(*bb).num );
}

int main()
{
    StuUtilize tmp;
    scanf("%d",&RecN);
    for(StuN=0;StuN<RecN;StuN++)
    {
        scanf("%s%d%d",tmp.name,&tmp.num,&tmp.len);
        checkHash(tmp);
    }
    qsort(stu,StuN,sizeof(StuUtilize),cmp);
}

void checkHash(StuUtilize tmp)
{
    LinkList p,pre;
    int key=hash(tmp.num);
    p=HT[key];
    while(p!=NULL)
    {
        if(p->num==tmp.num)
        {
            stu[p->place].len+=tmp.len;
            return;
        }
        pre=p;
        p=p->link;
    }
    p=(LinkList)malloc(sizeof(LNode));
    p->num=tmp.num;
    p->place=StuN;
    p->link=NULL;
    pre->link=p;
    return;
}

int hash(int num)
{
    return num%1000;
}
