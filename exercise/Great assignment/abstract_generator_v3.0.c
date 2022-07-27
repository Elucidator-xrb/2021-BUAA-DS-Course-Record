#include<stdio.h>
#include<stdlib.h>
#define NMAX 10000005
#define SMAX 102451

#define isa(x) (65<=x && x<=90) || (97<=x && x<=122)
#define tolo(x) (x|32)

typedef struct s
{
    char *sentc;
    int frequency;
    int no;
} Sentence;

Sentence stc[SMAX];
char article[NMAX];
int Snum=0;

int trie[NMAX][26];
int freq[NMAX];
int word[NMAX];
int Wnum=-1,Nlip=0,thr=0;

int N;

void readArticle();
void removeStopword();
void sort_and_print();
int cmp(const void *a,const void *b)
{
    Sentence *aa=(Sentence *)a;
    Sentence *bb=(Sentence *)b;
    if(aa->frequency != bb->frequency)
        return bb->frequency - aa->frequency;
    else
        return aa->no - bb->no;
}


int main()
{
    scanf("%d",&N);
    readArticle();
    removeStopword();
    sort_and_print();
    return 0;
}

void readArticle()
{
    int i;
    char tmp;
    FILE *fp=fopen("article.txt","r");
    FILE *wt=fopen("wordtest.txt","w");

    fread(article,sizeof(char),NMAX,fp);
    stc[0].sentc=article;
    stc[0].no=0;
    for(i=0;article[i];++i)
    {
        if(isa(article[i]))
        {
            tmp=tolo(article[i])-97;
            if(trie[thr][tmp]==0)
                trie[thr][tmp]=++Nlip;
            thr=trie[thr][tmp];
        }
        else if(thr)
        {
            ++freq[thr];
            word[++Wnum]=thr;
            thr=0;
        }
        if(article[i]=='.' || article[i]=='?' || article[i]=='!')
        {
            word[++Wnum]=-1;
            article[++i]='\0';
            while(article[i+1]==32) ++i; //并不是所有句子都需要处理，此处可再优化，放入打印的句子中
            stc[Snum].no=Snum;
            stc[++Snum].sentc=&article[i+1];
        }
    }for(i=0;i<Wnum;i++) fprintf(wt,"[%d]%d\n",i,word[i]);
    fclose(fp);//到时候尝试不关文件
}

void removeStopword()
{
    int i,j=0;
    char buf[15];
    FILE *fp=fopen("stopwords.txt","r");
    //FILE *test=fopen("test.txt","w");

    while(fscanf(fp,"%s",buf)==1)
    {
        thr=0;
        for(i=0;buf[i];++i)
            thr=trie[thr][buf[i]-97];
        freq[thr]=0;
    }
    freq[0]=0;
    for(i=0;i<Snum;++i)
    {
        for(;word[j]!=-1;++j)
            stc[i].frequency += freq[word[j]];
        ++j;//fprintf(test,"[%d]%d %s\n",i,stc[i].frequency,stc[i].sentc);
    }
    fclose(fp);
}

void sort_and_print()
{
    int i;
    FILE *fp=fopen("results.txt","w");
    qsort(stc,Snum,sizeof(stc[0]),cmp);

    printf("%d %s\n",stc[0].frequency,stc[0].sentc);
    printf("%d %s\n",stc[1].frequency,stc[1].sentc);
    printf("%d %s\n",stc[2].frequency,stc[2].sentc);
    printf("%d %s\n",stc[3].frequency,stc[3].sentc);
    printf("%d %s\n",stc[4].frequency,stc[4].sentc);
    for(i=0;i<N;++i)
        fprintf(fp,"%d %s\n",stc[i].frequency,stc[i].sentc);
}
