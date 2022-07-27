#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SMAX 102451
#define AMAX 1168
#define WMAX 750
#define isa(x) (65<=x && x<=90) || (97<=x && x<=122)
#define tolo(x) (x|=32)    //位运算优化tolower

/*
1.修改了句子读入方式：在统计单词freq时一起读入；
2.修改了句子频度计算方式：实现存储单词在单词树中的位置(指针)

结果变慢了，平均0.6s
*/

typedef struct node
{
    struct node *child[26];
    int cnt;
} TNode, *Triet;

Triet root=NULL;

typedef struct p
{
    char *sentence;
    int freq;
    int order;
} Position;

Position pos[SMAX];
char str[SMAX][AMAX];//为减少交换运算，将str独立出来，仅对pos排序
int *word_pc[SMAX][WMAX];
int Wnum[SMAX];
int Snum;
int N;

void buildTrieTree();
void cntWord_and_readIn();
void sort_and_print();
int cmp(const void *a,const void *b)
{
    Position *aa=(Position *)a;
    Position *bb=(Position *)b;
    if(aa->freq != bb->freq)
        return bb->freq - aa->freq;
    else
        return aa->order - bb->order;
}

int main()
{
    root=(Triet)calloc(1,sizeof(TNode));
    scanf("%d",&N);

    buildTrieTree();
    cntWord_and_readIn();
    sort_and_print();
    return 0;
}

void buildTrieTree()
{
    Triet p=root,q;
    FILE *fp;
    char buf[50];
    fp=fopen("stopwords.txt","r");
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
        p->cnt=-1;
        p=root;
    }
    fclose(fp);
    return;
}

void cntWord_and_readIn()
{
    FILE *fp;
    char tmp;
    char buf[AMAX];int len=0;
    Triet p=root,q;

    fp=fopen("article.txt","r");
    while((tmp=fgetc(fp))!=EOF)
    {
        str[Snum][len++]=tmp;
        if(isa(tmp))
        {
            tmp=tolo(tmp)-97;
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
            if(p->cnt!=-1)
            {
                p->cnt++;
                word_pc[Snum][ Wnum[Snum]++ ]=&p->cnt;
            }
            p=root;
        }
        if(tmp=='.'||tmp=='?'||tmp=='!')//句子结束
        {
            str[Snum][len]=0;
            pos[Snum].order=Snum;
            pos[Snum].sentence=&str[Snum][0];
            Snum++;
            len=0;
            fscanf(fp,"%*[\40]");
        }
    }
    fclose(fp);
    return;
}

void sort_and_print()
{
    FILE *fp;
    int i,j,total;
    for(i=0;i<Snum;i++)
    {
        total=0;
        for(j=0;j<Wnum[i];j++)
        {
            total+=*word_pc[i][j];
        }
        pos[i].freq=total;
    }
    qsort(pos,Snum,sizeof(pos[0]),cmp);

    fp=fopen("results.txt","w");
    printf("%d %s\n",pos[0].freq,pos[0].sentence);
    printf("%d %s\n",pos[1].freq,pos[1].sentence);
    printf("%d %s\n",pos[2].freq,pos[2].sentence);
    printf("%d %s\n",pos[3].freq,pos[3].sentence);
    printf("%d %s\n",pos[4].freq,pos[4].sentence);
    for(i=0;i<N;i++)
        fprintf(fp,"%d %s\n",pos[i].freq,pos[i].sentence);
    fclose(fp);
    return;
}
