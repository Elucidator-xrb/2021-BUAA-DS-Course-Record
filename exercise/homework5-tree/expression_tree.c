#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
//后缀表达式还是极其不熟练！
typedef union content
{
    int n;
    char m;
} item;

typedef struct node
{
    int sign;
    item data;
    struct node *lchild,*rchild;
} ETNode, *ETree;

int pri[128];

ETree t;
ETree estack[100];
char mstack[100];
int mtop=-1,etop=-1;

void popCombine()
{
    ETree l,r,par;

    r=estack[etop--];
    l=estack[etop--];

    par=(ETree)malloc(sizeof(ETNode));
    par->sign=0; par->data.m=mstack[mtop--];
    par->lchild=l; par->rchild=r;

    estack[++etop]=par;
}

int getValue(ETree tree)
{
    char ch=tree->data.m;
    int l,r;

    if(tree->lchild->sign==1) l=tree->lchild->data.n;
    else l=getValue(tree->lchild);
    if(tree->rchild->sign==1) r=tree->rchild->data.n;
    else r=getValue(tree->rchild);

    switch(ch)
    {
    case '+':return l+r;
    case '-':return l-r;
    case '*':return l*r;
    case '/':return l/r;
    }
}

int main()
{
    int i,j;
    char buf[BUFSIZ];
    int tmp=0,value;
    ETree p;
    pri['+']=pri['-']=1; pri['*']=pri['/']=2; pri['(']=pri[')']=3;

    gets(buf);
    for(i=0,j=0;buf[i]!='\0';i++)
        if(buf[i]!=' ') buf[j++]=buf[i];
    buf[j]='\0';

    for(i=0;buf[i]!='\0';i++)
    {
        if(isdigit(buf[i])) tmp=(tmp<<1)+(tmp<<3)+(buf[i]&15);
        else
        {   if(i>=1 && isdigit(buf[i-1]))
            {
                p=(ETree)malloc(sizeof(ETNode));
                p->sign=1; p->data.n=tmp;
                p->lchild=p->rchild=NULL;
                estack[++etop]=p;
                tmp=0;
            }
            if(buf[i]=='=') break;

            while(mtop>-1 && mstack[mtop]!='('
                  && pri[buf[i]]<=pri[mstack[mtop]]) popCombine();
            if(buf[i]==')')
            {
                while(mstack[mtop]!='(') popCombine();
                mtop--;
            }
            else  mstack[++mtop]=buf[i];
        }
    }
    while(mtop>-1) popCombine();

    t=estack[0];
    printf(t->sign?"%d":"%c",t->data);
    if(p=t->lchild) printf(p->sign?" %d":" %c",p->data);//对于data的解释由%d或%c提供
    if(p=t->rchild) printf(p->sign?" %d":" %c",p->data);
    value=getValue(t);
    printf("\n%d",value);

    return 0;
}
