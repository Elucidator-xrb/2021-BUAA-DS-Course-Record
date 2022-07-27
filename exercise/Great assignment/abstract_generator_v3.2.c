#include<stdio.h>
#include<stdlib.h>
#define NMAX 7000000
#define SMAX 150000
#define WMAX 1300000

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
int word[WMAX];
int Wnum=-1,Nlip=1,thr=1;
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
    int i,j=0;
    char tmp,buf[15];
    FILE *fa=fopen("article.txt","r");
    FILE *fs=fopen("stopwords.txt","r");
    FILE *fr=fopen("results.txt","w");

    scanf("%d",&N);

    fread(article,sizeof(char),NMAX,fa);
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
        else if(thr!=1)
        {
            ++freq[thr];
            word[++Wnum]=thr;
            thr=1;
        }
        if(article[i]=='.' || article[i]=='?' || article[i]=='!')
        {
            word[++Wnum]=-1;
            article[++i]='\0';
            while(article[i+1]==32) ++i;
            stc[Snum].no=Snum;
            stc[++Snum].sentc=&article[i+1];
        }
    }

    while(fscanf(fs,"%s",buf)==1)
    {
        thr=1;
        for(i=0;buf[i];++i)
            thr=trie[thr][buf[i]-97];
        freq[thr]=0;
    }
    for(i=0;i<Snum;++i)
    {
        for(;word[j]!=-1;++j)
            stc[i].frequency += freq[word[j]];
        ++j;
    }

    qsort(stc,Snum,sizeof(stc[0]),cmp);
    printf("%d %s\n",stc[0].frequency,stc[0].sentc);
    printf("%d %s\n",stc[1].frequency,stc[1].sentc);
    printf("%d %s\n",stc[2].frequency,stc[2].sentc);
    printf("%d %s\n",stc[3].frequency,stc[3].sentc);
    printf("%d %s\n",stc[4].frequency,stc[4].sentc);
    for(i=0;i<N;++i)
        fprintf(fr,"%d %s\n",stc[i].frequency,stc[i].sentc);

    return 0;
}


