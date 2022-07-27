#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct node{
    ElemType data;
    struct node *link;
}LNode,*Linklist;

Linklist list,r;//��һ��������ָ��link ָ������β��ָ��r

//1.������������ ���ظ�����ָ��
Linklist Create(int n)
{
    Linklist p;
    ElemType a;
    int i;
    for(i=0;i<n;i++)
    {
        Read(&a);
        p=(Linklist)malloc(sizeof(LNode));
        p->data=a;
        p->link=NULL;/* �������Ტ�������� */

        if(list==NULL)
            list=p;
        else
            r->link=p;
        r=p;         /* �������������� */
    }
    return list;
}


//2.�������� ���س�����ֵ
int Lenth(Linklist list)
{
    Linklist p=list;
    int len=0;
    while(p->link!=NULL)
    {
        len++;
        p=p->link;
    }
    return len;
}//ѭ��д��
int Lenth_r(Linklist list)
{
    if(list==NULL)  return 0;
    else return 1+Lenth(list->link);
}//�ݹ�д��


//3.�ж��Ƿ�Ϊ�ձ� �����߼���ֵ
int isEmpty(Linklist list)
{
    return list==NULL;
}


//4.ȷ��Ԫ��λ�� ����item���ĵ�ַ
Linklist itemFind(Linklist list,ElemType item)
{
    Linklist p=list;/* ��⣺p��Զָ�򱾽��ĵ�ַ */
    while(p->data!=item && p!=NULL)
        p=p->link;
    return p;
}


//5.����Ԫ�� �޷���ֵ
//5.1 ͷ����
void insertHead(Linklist list,ElemType item)
{
    Linklist p;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    p->link=list;
    list=p;
}
//5.2 β����
void insertTail(Linklist list,ElemType item)
{
    Linklist p;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    r->link=p;
    p->link=NULL;
    r=r->link;
    /* ��û��ȫ�ֱ���r��¼β��㣬����ʱ�ҵ�����β */
}
//5.3 ��ָ������ַq�����
void insertAddress(Linklist list,ElemType item,Linklist q)
{                                      /* ע���ж�q�ĺϷ��� */
    Linklist p;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    p->link=q->link;
    q->link=p;
}
//5.4 ��ָ�������i�����
void insertNum(Linklist list,ElemType item,int i)
{                                     /*  ע���ж�i�ĺϷ��� */
    Linklist p,q=list;
    int cnt;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    for(cnt=1;cnt<i && q!=NULL;cnt++)
        q=q->link;
    if(cnt!=i)
    {
        perror("Invalid insert!\n");
        return -1;
    }

    p->link=q->link;
    q->link=p;
}
//5.5 ���������а������������
void insertOrder(Linklist list,ElemType item)
{
    Linklist p,q,pre;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    if(list==NULL || item<list->data)
    {           /* �������itemС��������Ԫ�� */
        p->link=list;
        list=p;
    }
    else
    {
        q=list;/* list����£�����ÿ�ζ�������ָ����list */
        while(q!=NULL && q->data<=item)
        { /* �ǵñ���ǰһ���ӵĵ�ַ����Ϊ�����޷����� */
            pre=q;
            q=q->link;
        }
        p->link=q;
        pre->link=p;
    }
}


//6. ɾ�����
//6.1 ɾ��q��ָ��ָ�����
void delNode(Linklist list,Linklist pre,Linklist q)
{
//��ȡpre
/*
    pre=list;
    while(pre->list!=NULL && pre->link!=q) pre=pre->link;
 */

    if(q==list) list=q->link; /* qָ����λ */
    else pre->link=q->link;   /* q��ָ����λ */
    free(q);
}
//6.2 ɾ��ֵΪitem�Ľ��
void delItem(Linklist list,ElemType item)
{
    Linklist p=list->link,pre=list;
    while(p!=NULL)
    {
        if(p->data==item)
        {
            pre->link=p->link;
            free(p);
            p=pre->link; /* ֱ���Ƶ���p */
        }
        else
        {
            pre=p;
            p=p->link;
        }
    }
    if(list->data==item)
    {
        p=list;
        list=list->link;
        free(p);
    }

}


//7. ��������
void delList(Linklist list)
{
    Linklist p=list;
    while(p!=NULL)
    {
        list=p->link; /* ÿ�θı�ͷ */
        free(p);
        p=list;
    }
}


//8. ��ת���Ա�*
void reverList(Linklist list)
{
    Linklist r,p=NULL,q=list;/* r��p��q �ֱ�ָ�� ǰ���㡢��ǰ�㡢������ */
    /* ÿ����ת������p, ����r��q�����£���Ϣ���ᶪʧ�� */
    while(q!=NULL)
    {
        r=p,p=q,q=q->link; /* ÿ����ǰ���ƣ�����ע��r��p��q��ʼ�� */
        p->link=r;         /* ��ת */
    }
    list=q;                /* �޸�ͷ */
}


//9. �����ǿ����Ա��������򲢹�
Linklist mergeList(Linklist lista,Linklist listb)
{ /* һ�ж���ָ���ڹĵ��������пռ��� */
    Linklist listc;
    Linklist p=lista,q=listb,r;/* p��q�ֱ��lista��listb��ȡ����rָ��listc��β���ڼ��� */
    if(lista->data <= listb->data)
    {
        listc=lista;
        p=p->link;
        r=listc;
    }
    else
    {
        listc=listb;
        q=q->link;
        r=listc;
    }                           /* ȷ��listc��ͷ������ѭ������ */

    while(p!=NULL && q!=NULL)
    {
        if(p->data >= q->data)
        {
            r->link=q;
            r=q;
            q=q->link;
        }
        else
        {
            r->link=p;
            r=p;
            p=p->link;
        }
    }
    r->link= p?p:q;         /* ˭ʣ��˭��NULL��ֵ����0�� */

    return listc;
}


//10. ��������
Linklist copyList(Linklist list)
{
    Linklist listc;
    if(list==NULL)
        return NULL;       /* �Ⱥ��ǿձ������ǵݹ���ֹ���� */
    else
    {
        listc=(Linklist)malloc(sizeof(LNode));
        listc->data=list->data;
        listc->link=copyList(list->link);  /* �ݹ�д�� */
    }
}

