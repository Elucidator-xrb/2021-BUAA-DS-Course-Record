#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node
{
    char word[50];
    int cnt;
    struct node *lchild,*rchild;
} BTNode, *BTree;

BTree t;

void insertBST(char *tmp)
{
    BTree p,q=t;

    p=(BTree)malloc(sizeof(BTNode));
    strcpy(p->word,tmp);
    p->cnt=1;
    p->lchild=p->rchild=NULL;

    if(t==NULL) t=p;
    else
    {
        while(1)
        {
            if(strcmp(q->word,tmp)==0)
            {
                q->cnt++;
                free(p);
                break;
            }
            else if(strcmp(q->word,tmp)>0)
            {
                if(q->lchild!=NULL) q=q->lchild;
                else { q->lchild=p;break; }
            }
            else
            {
                if(q->rchild!=NULL) q=q->rchild;
                else { q->rchild=p;break; }
            }
        }
    }
}

void inPrintTree()//选择非递归中序遍历
{
    BTree stack[200],p=t;
    int top=-1;
    do{
        while(p!=NULL)
        {
            stack[++top]=p;
            p=p->lchild;
        }

        p=stack[top--];
        printf("%s %d\n",p->word,p->cnt);

        p=p->rchild;
    }while(p!=NULL || top>-1);
}

int main()
{
    FILE *fp;
    char buf[BUFSIZ];
    char tmp[50];
    int len,i,j=0;
    BTree p;

    fp=fopen("article.txt","r");
    while(fgets(buf,BUFSIZ,fp)!=NULL)
    {
        len=strlen(buf);
        for(i=0;i<len;i++)
        {
            if(isalpha(buf[i])) tmp[j++]=tolower(buf[i]);
            else
            {
                tmp[j]='\0';
                if(tmp[0]) insertBST(tmp);
                j=0;
            }
        }
    }
    fclose(fp);

    printf("%s",t->word);
    for(i=1,p=t->rchild; p && i<3; i++)
    {
        printf(" %s",p->word);
        p=p->rchild;
    }
    puts("");

    inPrintTree();
    return 0;
}
