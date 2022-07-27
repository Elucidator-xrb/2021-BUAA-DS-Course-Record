#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int coef;
    int exp;
    struct node *link;
} PNode, *PLinklist;

PLinklist lista,listb,listc;

PLinklist readPoly()
{
    PLinklist list; printf("[List_ADDRESS_before]:\t%p\n",list);
    PLinklist p,r; printf("[r_ADDRESS_before]:\t%p\n",r);
    do
    {
        p=(PLinklist)malloc(sizeof(PNode));
        scanf("%d%d",&p->coef,&p->exp);
        p->link=NULL;
        if(list==NULL) list=p;
        else r->link=p;
        r=p;                      printf("1 ");
    }while(getchar()!='\n');//当检测到行末'\n'后结束

printf("\n[List_ADSRESS_after]:\t%p\n",list);
printf("[r_ADDRESS_after]:\t%p\n\n",r);
    return list;
}

void printList(PLinklist list)
{
    PLinklist p=list;
    int cnt=0;
    while(p!=NULL)
    {
        cnt++;
        printf("%d\t%d\t[ADDRESS:%p]\n",p->coef,p->exp,p);
        p=p->link;
    }
    printf(" %d in total\n\n",cnt);
}



int main()
{
    lista=readPoly();
printf("sf");
    printList(lista);  listb=readPoly();
//    multiPoly();
//    printList(listc);
     printList(listb);
    return 0;
}
