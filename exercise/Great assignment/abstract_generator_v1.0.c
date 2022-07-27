#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define INF 0x3f3f3f3f
/*实现1：


*/
typedef struct node
{
    struct node *child[26];
    int cnt;
    int isfinal;
} TNode, *Triet;

Triet root=NULL;

typedef struct n
{
    int freq,order;
    char str[BUFSIZ];
} Sentence;

Sentence sentc[200000];
int Snum;

int N;

void buildTrieTree();
void cntWordFrequnency();
void readInSentences();
void insertInOrder(char buf[],int freq);
void printSentences();
int cmp(const void *a,const void *b)
{
    Sentence *aa=(Sentence *)a;
    Sentence *bb=(Sentence *)b;
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
        {//printf("%c",buf[i]);
            int alp=buf[i]-97;
            if(p->child[alp]!=NULL)
                p=p->child[alp];
            else
            {
                q=(Triet)calloc(1,sizeof(TNode)); //printf("%p == %d [%d]\n",q->child[10],q->cnt,q->isfinal);
                p->child[alp]=q; //printf("%p\n",p->child[alp]);
                p=q;
            }
        }
        p->isfinal=1; //printf("\t%5d [%d]\n",p->cnt,p->isfinal);
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
        {//printf("%c",tmp);
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
        {//printf("\t%5d [%d]  -> ",p->cnt,p->isfinal);
            if(p->isfinal==0 ||
               p->isfinal==1 && p->cnt)
            {
                p->isfinal=1;
                p->cnt++;
            }//printf("%5d [%d]\n",p->cnt,p->isfinal);
            p=root; //归位
        }
    }
    fclose(fp);
    return;
}

void readInSentences()
{
    FILE *fp;
    char buf[1000];int len=0;
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
        buf[len++]=tmp; //printf("%c",tmp);

        if(isalpha(tmp))
        {//printf("%c",tmp);
            tmp=tolower(tmp)-97;
            p=p->child[tmp];
        }
        else  //词结束
        {
            if(p!=NULL && p->cnt)
            {//printf("\t%6d [%d]\n",p->cnt,p->isfinal);
                f+=p->cnt;
            }
            p=root;
        }
        if(tmp=='.' || tmp=='?' || tmp=='!') //句子结束
        {
            buf[len]='\0';
            strcpy(sentc[Snum].str,buf);
            sentc[Snum].freq=f;
            sentc[Snum].order=Snum;
            Snum++;
            len=f=0; //printf("[%d]%d: %s\n",sentc[Snum-1].order,sentc[Snum-1].freq,sentc[Snum-1].str);

            fscanf(fp,"%*[\40]");//删除句前空格
        }
    }
//    int i;
//    for(i=0;i<Snum;i++) printf("[%d]%d: %s\n",pos[i]->order,pos[i]->freq,pos[i]->str);

//    qsort(pos,Snum,sizeof(pos[0]),cmp);
    qsort(sentc,Snum,sizeof(sentc[0]),cmp);

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
        printf("%d %s\n",sentc[i].freq,sentc[i].str);
    for(i=0;i<N;i++)
        fprintf(fp,"%d %s\n",sentc[i].freq,sentc[i].str);

    fclose(fp);
}
