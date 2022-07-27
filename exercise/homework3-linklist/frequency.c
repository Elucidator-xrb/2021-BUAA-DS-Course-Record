#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct node
{
    char word[50];
    int num;
    struct node *link;
} LNode, *Linklist;

Linklist dict;

void printDict()
{
    Linklist p=dict;
    while(p!=NULL)
    {
        printf("%s %d\n",p->word,p->num);
        p=p->link;
    }
}

void readInOrder(char *w)
{
    Linklist p,q,pre;
    p=(Linklist)malloc(sizeof(LNode));
    strcpy(p->word,w);
    p->num=1;
    p->link=NULL;
    if(dict==NULL || strcmp(w,dict->word)<0)
    {
        p->link=dict;
        dict=p;
    }
    else
    {
        q=dict;//这里放前/后都可以，若是循环，由于dict会更新，则必放此处
        while(q!=NULL && strcmp(q->word,p->word)<0)
        {
            pre=q;
            q=q->link;
        }
        if(q!=NULL && strcmp(q->word,p->word)==0)
        {     /* ATTENTION:在取值之前一定要确认是否为NULL */
            q->num+=p->num;
            free(p);
        }
        else
        {
            p->link=q;
            pre->link=p;
        }
    }
}

int main()
{
    FILE *fp;
    char buf[50]={0},ch;
    int i=0;

    fp=fopen("article.txt","r");
    while((ch=fgetc(fp))!=EOF)
    {
        if(isalpha(ch)) buf[i++]=tolower(ch);
        else
        {
            buf[i]='\0',i=0;
            if(buf[0]!='\0') readInOrder(buf);
        }
    }
    printDict();
    fclose(fp);
    return 0;
}
