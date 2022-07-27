#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
    int num;
    char name[25];
    int seat;
    struct node *link;
} LNode, *Linklist;

Linklist list,list2;
int N,M,Q;

void seatInOrder(Linklist p);
void repairOmit();
void repairDup();
void numInOrder();
void printList();

int main()
{
    FILE *fin;
    Linklist p;
    char buf[BUFSIZ];

    scanf("%d",&N);
    fin=fopen("in.txt","r");
    while(fgets(buf,BUFSIZ,fin)!=NULL)
    {
        p=(Linklist)malloc(sizeof(LNode));
        sscanf(buf,"%d%s%d",&p->num,p->name,&p->seat);
        p->link=NULL;
        if(M < p->seat) M=p->seat;
        seatInOrder(p);
    }
    fclose(fin);
    repairOmit();
    repairDup();
    numInOrder();
    printList();
    return 0;
}

void seatInOrder(Linklist p)
{
    Linklist pre,q;
    if(list==NULL || list->seat > p->seat)
        p->link=list,
        list=p;
    else
    {
        q=list;
        while(q!=NULL && q->seat <= p->seat)
            pre=q,
            q=q->link;
        p->link=q;
        pre->link=p;
    }
}

void repairOmit()
{
    Linklist rcd=list,rcd_pre=NULL;
    Linklist tail=NULL,pre=NULL;
    int i=1;
    Q=(M<=N)?M:N;

    while(i<=Q && rcd!=NULL)
    {
        if(rcd!=NULL && i < rcd->seat)
        {
            tail=list;
            while(tail->link!=NULL)
            {
                pre=tail;
                tail=tail->link;
            }
            pre->link=NULL;
            tail->seat=i;
            if(rcd==list)
                tail->link=list,list=tail;
            else
                tail->link=rcd,rcd_pre->link=tail;
            i++;
        }
        if(rcd!=NULL && i == rcd->seat)
        {
            i++;
            rcd_pre=rcd;
            rcd=rcd->link;
        }
        if(rcd!=NULL && i > rcd->seat)
            rcd_pre=rcd,
            rcd=rcd->link;
    }
}

void repairDup()
{
    Linklist p=list->link,pre=list;
    Linklist r=list;
    while(r->link!=NULL) r=r->link;
    M=r->seat;
    int m=M;

    while(p!=NULL && p->seat<=M)
    {//printf("%d %d ",p->seat, m);
        if(p->seat == pre->seat)
        {
            if(p==r) p->seat=m+1;
            else
            {
                pre->link=p->link;
                p->seat=++m;
                p->link=NULL;
                r->link=p;
                r=p;
            }
            p=pre->link;
        }
        pre=p;
        p=p->link;
    }
}

void numInOrder()
{
    Linklist cur=list,lat=list->link;
    Linklist p,pre;
    while(cur!=NULL)
    {
        cur->link=NULL;
        if(list2==NULL || list2->num > cur->num)
            cur->link=list2,
            list2=cur;
        else
        {
            p=list2;
            while(p!=NULL && p->num < cur->num)
                pre=p,
                p=p->link;
            cur->link=p;
            pre->link=cur;
        }
        cur=lat;
        if(lat!=NULL) lat=lat->link;
    }
}

void printList()
{
    FILE *fout;
    Linklist p=list2;

    fout=fopen("out.txt","w");
    while(p!=NULL)
    {
        fprintf(fout,"%d %s %d\n",p->num,p->name,p->seat);
        p=p->link;
    }
    fclose(fout);
}
