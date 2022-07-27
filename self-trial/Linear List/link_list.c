#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct node{
    ElemType data;
    struct node *link;
}LNode,*Linklist;

Linklist list,r;//第一个链结点的指针link 指向链结尾的指针r

//1.建立线性链表 返回该链表指针
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
        p->link=NULL;/* 申请链结并填入内容 */

        if(list==NULL)
            list=p;
        else
            r->link=p;
        r=p;         /* 将链结连入链表 */
    }
    return list;
}


//2.求链表长度 返回长度数值
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
}//循环写法
int Lenth_r(Linklist list)
{
    if(list==NULL)  return 0;
    else return 1+Lenth(list->link);
}//递归写法


//3.判断是否为空表 返回逻辑真值
int isEmpty(Linklist list)
{
    return list==NULL;
}


//4.确定元素位置 返回item结点的地址
Linklist itemFind(Linklist list,ElemType item)
{
    Linklist p=list;/* 理解：p永远指向本结点的地址 */
    while(p->data!=item && p!=NULL)
        p=p->link;
    return p;
}


//5.插入元素 无返回值
//5.1 头插入
void insertHead(Linklist list,ElemType item)
{
    Linklist p;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    p->link=list;
    list=p;
}
//5.2 尾插入
void insertTail(Linklist list,ElemType item)
{
    Linklist p;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    r->link=p;
    p->link=NULL;
    r=r->link;
    /* 若没有全局变量r记录尾结点，则临时找到链表尾 */
}
//5.3 在指定结点地址q后插入
void insertAddress(Linklist list,ElemType item,Linklist q)
{                                      /* 注意判断q的合法性 */
    Linklist p;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    p->link=q->link;
    q->link=p;
}
//5.4 在指定结点数i后插入
void insertNum(Linklist list,ElemType item,int i)
{                                     /*  注意判断i的合法性 */
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
//5.5 在有序链中按（升）序插入
void insertOrder(Linklist list,ElemType item)
{
    Linklist p,q,pre;
    p=(Linklist)malloc(sizeof(LNode));
    p->data=item;

    if(list==NULL || item<list->data)
    {           /* 空链表或item小于链表首元素 */
        p->link=list;
        list=p;
    }
    else
    {
        q=list;/* list会更新，所以每次都得重新指向真list */
        while(q!=NULL && q->data<=item)
        { /* 记得保留前一链接的地址，因为链表无法回溯 */
            pre=q;
            q=q->link;
        }
        p->link=q;
        pre->link=p;
    }
}


//6. 删除结点
//6.1 删除q所指的指定结点
void delNode(Linklist list,Linklist pre,Linklist q)
{
//获取pre
/*
    pre=list;
    while(pre->list!=NULL && pre->link!=q) pre=pre->link;
 */

    if(q==list) list=q->link; /* q指向首位 */
    else pre->link=q->link;   /* q不指向首位 */
    free(q);
}
//6.2 删除值为item的结点
void delItem(Linklist list,ElemType item)
{
    Linklist p=list->link,pre=list;
    while(p!=NULL)
    {
        if(p->data==item)
        {
            pre->link=p->link;
            free(p);
            p=pre->link; /* 直接移到新p */
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


//7. 销毁链表
void delList(Linklist list)
{
    Linklist p=list;
    while(p!=NULL)
    {
        list=p->link; /* 每次改变头 */
        free(p);
        p=list;
    }
}


//8. 逆转线性表*
void reverList(Linklist list)
{
    Linklist r,p=NULL,q=list;/* r、p、q 分别指向 前驱点、当前点、后驱点 */
    /* 每次逆转发生在p, （在r、q保护下，信息不会丢失） */
    while(q!=NULL)
    {
        r=p,p=q,q=q->link; /* 每次向前推移，所以注意r、p、q初始化 */
        p->link=r;         /* 逆转 */
    }
    list=q;                /* 修改头 */
}


//9. 两个非空线性表按（升）序并归
Linklist mergeList(Linklist lista,Linklist listb)
{ /* 一切都是指针在鼓捣，不会有空间多出 */
    Linklist listc;
    Linklist p=lista,q=listb,r;/* p、q分别从lista和listb中取数，r指向listc结尾用于加数 */
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
    }                           /* 确定listc的头，规整循环条件 */

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
    r->link= p?p:q;         /* 谁剩接谁（NULL的值就是0） */

    return listc;
}


//10. 复制链表
Linklist copyList(Linklist list)
{
    Linklist listc;
    if(list==NULL)
        return NULL;       /* 既涵盖空表处理又是递归终止条件 */
    else
    {
        listc=(Linklist)malloc(sizeof(LNode));
        listc->data=list->data;
        listc->link=copyList(list->link);  /* 递归写法 */
    }
}

