#include<stdio.h>
#include<stdlib.h>

typedef int QElemtype;
typedef struct node
{
    QElemtype data;
    struct node link;
} QNode, *Qlink;

Qlink front,rear;

void initialQueue(Qlink front,Qlink rear){ front=rear=NULL; }

int isEmpty(Qlink front){ return front==NULL; }

int addQueue(Qlink front,Qlink rear,QElemtype item) //从rear接(front乱入是考虑空队)
{
    Qlink p;
    if(!(p=(Qlink)malloc(sizeof(QNode)))) return 0; //申请链结失败，没有空间了
    p->data=item;
    p->link=NULL;

    if(front==NULL) front=p;
    else rear->link=p;
    rear=p;
    return 1;
}

int delQueue(Qlink front,QElemtype item) //从front删
{
    Qlink p;

    if(isEmpty(front)) return 0;
    p=front, item=p->data;
    front=front->link;
    free(p);
    return 1;
}

int desQueue(Qlink front)
{
    Qlink p;
    while(front)
    {
        p=front;
        front=front->link;
        free(p);
    }
}
