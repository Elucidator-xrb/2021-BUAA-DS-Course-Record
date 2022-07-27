#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define WMAX 1500

typedef struct node
{
    struct node *child[26];
    int cnt;
    int isfinal;
} TNode, *Triet;

Triet root=NULL;

typedef struct p
{
    int freq;
    int order;
    char *sentence;
} Position;

Position pos[200000];
char str[200000][WMAX];//为减少交换运算，将str独立出来，仅对pos排序
int Snum;
int N;

void buildTrieTree();
void cntWordFrequnency();
void readInSentences();
void insertInOrder(char buf[],int freq);
void printSentences();
int cmp(const void *a,const void *b)
{
    Position *aa=(Position *)a;
    Position *bb=(Position *)b;
    if(aa->freq != bb->freq)
        return (aa->freq < bb->freq) - (aa->freq > bb->freq);
    else
        return (aa->order > bb->order) -(aa->order < bb->order);
}


int main()
{
    root=(Triet)malloc(sizeof(TNode)); //或用calloc 到时候看看时间
    memset(root,0,sizeof(TNode));
    scanf("%d",&N);

    buildTrieTree();
    cntWordFrequnency();
    readInSentences();
    printSentences();
    return 0;
}

void buildTrieTree()
{
    Triet p=root,q;
    FILE *fp;
    char buf[50];
    if((fp=fopen("stopwords.txt","r"))==NULL)
    {
        perror("stopwords.txt");
        return;
    }
    while(fscanf(fp,"%s",buf)==1)
    {
        for(int i=0;buf[i]!='\0';i++)
        {
            int alp=buf[i]-97;
            if(p->child[alp]!=NULL)
                p=p->child[alp];
            else
            {
                q=(Triet)calloc(1,sizeof(TNode));
                p->child[alp]=q;
                p=q;
            }
        }
        p->isfinal=1;
        p=root;
    }
    fclose(fp);
    return;
}

void cntWordFrequnency()
{
    FILE *fp;
    char tmp;
    Triet p=root,q;

    if((fp=fopen("article.txt","r"))==NULL)
    {
        perror("article.txt");
        return;
    }
    while((tmp=fgetc(fp))!=EOF)
    {
        if(isalpha(tmp))
        {
            tmp=tolower(tmp)-97;
            if(p->child[tmp]!=NULL)
                p=p->child[tmp];
            else
            {
                q=(Triet)calloc(1,sizeof(TNode));
                p->child[tmp]=q;
                p=q;
            }
        }
        else if(p!=root) //词结束
        {
            if(p->isfinal==0 ||
               p->isfinal==1 && p->cnt)
            {
                p->isfinal=1;
                p->cnt++;
            }
            p=root; //归位
        }
    }
    fclose(fp);
    return;
}

void readInSentences()
{
    FILE *fp;
    char buf[WMAX];int len=0;
    char tmp;
    int f=0;
    Triet p=root;

    if((fp=fopen("article.txt","r"))==NULL)
    {
        perror("article.txt");
        return;
    }
    while((tmp=fgetc(fp))!=EOF)
    {
        buf[len++]=tmp;

        if(isalpha(tmp))
        {//printf("%c",tmp);
            tmp=tolower(tmp)-97;
            p=p->child[tmp];
        }
        else  //词结束
        {
            if(p!=NULL && p->cnt) f+=p->cnt;
            p=root;
        }
        if(tmp=='.' || tmp=='?' || tmp=='!') //句子结束
        {
            buf[len]='\0';
            strcpy(str[Snum],buf);
            pos[Snum].freq=f;
            pos[Snum].order=Snum;
            pos[Snum].sentence=&str[Snum][0];
            Snum++;
            len=f=0;

            fscanf(fp,"%*[\40]");//删除句前空格
        }
    }
    qsort(pos,Snum,sizeof(pos[0]),cmp);

    fclose(fp);
    return;
}

void printSentences()
{
    int i;
    FILE *fp;
    if((fp=fopen("results.txt","w"))==NULL)
    {
        perror("results.txt");
        return;
    }
    for(i=0;i<5;i++)
        printf("%d %s\n",pos[i].freq,pos[i].sentence);
    for(i=0;i<N;i++)
        fprintf(fp,"%d %s\n",pos[i].freq,pos[i].sentence);

    fclose(fp);
}
