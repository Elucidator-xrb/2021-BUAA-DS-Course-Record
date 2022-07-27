#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{               /* ��¼һ�������߶�*/
    int x;
    int y;
    struct node *link;
} LNode, *Line;

typedef struct circleHead
{
    Line head;   /* ��¼ÿ�������߶�ͷ���*/
    int num;    /* ��¼�������߶ε�����߶���*/
    struct circleHead *link;
} CNode, *hCoord;

hCoord Clist;

Line readLine()
{
    Line p,q;

    p=(Line)malloc(sizeof(LNode));
    scanf("%d%d",&p->x,&p->y);
    q=(Line)malloc(sizeof(LNode));
    scanf("%d%d",&q->x,&q->y);

    q->link=NULL, p->link=q;
    return p;
}

void creClist(int t)
{
    hCoord p,r;
    int i;
    for(i=0;i<t;i++)
    {
        p=(hCoord)malloc(sizeof(CNode));
        p->num=1;
        p->head=readLine();
        p->link=NULL;

        if(Clist==NULL) Clist=p;
        else r->link=p;
        r=p;
    }
    r->link=Clist;
}

int isConnect(Line p,Line q)
{
    return (p->x==q->x) && (p->y==q->y);
}

int doConnect(int last) //�������Ե�ѭ���Ƚ�ֱ���߶μ��ϲ��ٱ䶯
{
    int i=0;
    hCoord p=Clist,q,pre;
    Line pp,rr;

    while(i<last)
    {
        pp=p->head;
        while(pp->link!=NULL) pp=pp->link;
        rr=pp;

        for(q=p->link,pre=p;q!=p;pre=q,q=q->link)
        {
            if(isConnect(q->head,rr))
            {
                rr->link=q->head->link;
                p->num+=q->num;
                pre->link=q->link;
                last--;
                i=0;
                break;
            }
        }
        if(q==p) i++;
        else
        {
            free(q);
            continue;
        }
        p=p->link;
        Clist=p;     /* ע�⵱p����Clistʱ��Clist���ܻᶪʧ*/
    }
    return last;
}

void search_Print()
{
    hCoord p,k=Clist;
    for(p=Clist->link;p!=Clist;p=p->link)
        if(p->num > k->num) k=p;
    printf("%d %d %d",k->num,k->head->x,k->head->y);
}

int main()
{
    int t,n;
    scanf("%d",&t);
    creClist(t);
    n=doConnect(t);
    search_Print(n);
    return 0;
}
