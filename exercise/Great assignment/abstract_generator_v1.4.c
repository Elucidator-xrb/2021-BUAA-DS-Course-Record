#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SMAX 102451
#define WMAX 1168
#define isa(x) (65<=x && x<=90) || (97<=x && x<=122)
#define tolo(x) (x|=32)    //λ�����Ż�tolower

//һ���Կ�

typedef struct node
{
    struct node *child[26];
    int cnt;
} TNode, *Triet;

Triet root=NULL;
Triet cur;

typedef struct p
{
    char *sentence;
    int freq;
    int order;
} Position;

Position pos[SMAX];
char str[SMAX][WMAX];//Ϊ���ٽ������㣬��str��������������pos����
int Snum;
int N;

void buildTrieTree();
void cntWordFrequnency();
void readInSentences();
void printSentences();
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
    cur=(Triet)calloc(58596,sizeof(TNode));
    root=cur;
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
    fp=fopen("stopwords.txt","r");
    while(fscanf(fp,"%s",buf)==1)
    {
        for(int i=0;buf[i]!='\0';++i)
        {
            int alp=buf[i]-97;
            if(p->child[alp]!=NULL)
                p=p->child[alp];
            else
            {
                q=++cur;
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

void cntWordFrequnency()
{
    FILE *fp;
    char tmp;
    Triet p=root,q;

    fp=fopen("article.txt","r");
    while((tmp=fgetc(fp))!=EOF)
    {
        if(isa(tmp))
        {
            tmp=tolo(tmp)-97;
            if(p->child[tmp]!=NULL)
                p=p->child[tmp];
            else
            {
                q=++cur;
                p->child[tmp]=q;
                p=q;
            }
        }
        else if(p!=root) //�ʽ���
        {
            if(p->cnt!=-1) ++p->cnt;
            p=root; //��λ
        }
    }
    fclose(fp);
    return;
}

void readInSentences()
{
    FILE *fp;
    int len=0;
    char tmp;
    int f=0;
    Triet p=root;

    fp=fopen("article.txt","r");
    while((tmp=fgetc(fp))!=EOF)
    {
        str[Snum][len++]=tmp;
        if(isa(tmp))
        {
            tmp=tolo(tmp)-97;
            p=p->child[tmp];
        }
        else  //�ʽ���
        {
            if(p->cnt > 0) f+=p->cnt;
            p=root;
        }
        if(tmp=='.' || tmp=='?' || tmp=='!') //���ӽ���
        {
            //str[Snum][len]=0;
            pos[Snum].freq=f;
            pos[Snum].order=Snum;
            pos[Snum].sentence=&str[Snum][0];
            ++Snum;
            len=f=0;

            fscanf(fp,"%*[\40]");//ɾ����ǰ�ո�
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
    fp=fopen("results.txt","w");

    printf("%d %s\n",pos[0].freq,pos[0].sentence);
    printf("%d %s\n",pos[1].freq,pos[1].sentence);
    printf("%d %s\n",pos[2].freq,pos[2].sentence);
    printf("%d %s\n",pos[3].freq,pos[3].sentence);
    printf("%d %s\n",pos[4].freq,pos[4].sentence);
    for(i=0;i<N;++i)
        fprintf(fp,"%d %s\n",pos[i].freq,pos[i].sentence);

    fclose(fp);
}
