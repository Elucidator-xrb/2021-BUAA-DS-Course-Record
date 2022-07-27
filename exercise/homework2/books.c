#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
    char name[51];
    char author[21];
    char press[31];
    char date[11];
    struct node *link;
}LNode,*Linklist;

Linklist list;

void readInOrder(char *filename)
{
    FILE *fp;
    Linklist p,q,pre;
    char buf[BUFSIZ];

    fp=fopen(filename,"r");
    while(fgets(buf,BUFSIZ,fp)!=NULL)
    {
        p=(Linklist)malloc(sizeof(LNode));
        sscanf(buf,"%s%s%s%s",p->name,p->author,p->press,p->date);
        p->link=NULL;

        if(list==NULL || strcmp(list->name,p->name)>=0)
        {
            p->link=list;
            list=p;
        }
        else
        {
            q=list;
            while(q!=NULL && strcmp(q->name,p->name)<0)
            {
                pre=q;
                q=q->link;
            }
            p->link=q;
            pre->link=p;
        }
    }
    fclose(fp);
}

void insertInOrder()
{
    Linklist p,q,pre;
    p=(Linklist)malloc(sizeof(LNode));
    scanf("%s%s%s%s",p->name,p->author,p->press,p->date);
    p->link=NULL;

    if(list==NULL || strcmp(list->name,p->name)>=0)
    {
        p->link=list;
        list=p;
    }
    else
    {
        q=list;
        while(q!=NULL && strcmp(q->name,p->name)<0)
        {
            pre=q;
            q=q->link;
        }
        p->link=q;
        pre->link=p;
    }
}

void searchList()
{
    char ch[BUFSIZ];
    Linklist p=list;

//    fflush(stdin);
    getchar();
    gets(ch);
    while(p!=NULL)
    {
        if(strstr(p->name,ch)!=NULL)
            printf("%-50s%-20s%-30s%-10s\n",p->name,p->author,p->press,p->date);
        p=p->link;
    }
}

void delElement()
{
    char ch[BUFSIZ];
    Linklist p=list->link,pre=list;

//    fflush(stdin); 较差的可移植性
    getchar();
    gets(ch);
    while(p!=NULL)
    {
        if(strstr(p->name,ch)!=NULL)
        {
            pre->link=p->link;
            free(p);
            p=pre->link;
        }
        else
        {
            pre=p;
            p=p->link;
        }
    }
    if(strstr(list->name,ch)!=NULL)
    {
        p=list;
        list=list->link;
        free(p);
    }
}

void reWrite(char *filename)
{
    FILE *fp;
    Linklist p=list;
    fp=fopen(filename,"w");
    while(p!=NULL)
    {
        fprintf(fp,"%-50s%-20s%-30s%-10s\n",p->name,p->author,p->press,p->date);
        p=p->link;
    }
    fclose(fp);
}

int main()
{
    int t;
    readInOrder("books.txt");
    while(scanf("%d",&t))
    {
        if(t==0) break;
        else if(t==1) insertInOrder();
        else if(t==2) searchList();
        else if(t==3 && list!=NULL) delElement();
    }
    reWrite("ordered.txt");
    return 0;
}
