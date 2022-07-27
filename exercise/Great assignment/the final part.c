#include <stdio.h>
#define N 10000005
struct sentence_ope{
	char* sentence;
	int times;
};
struct sentence_ope sentence_list[N];
char stop_word[N], end_sign[N], article[N];
int trie[N][26], frequency[N];
int valArr[N], tmpArr[N], tmp2[N], retArr[N];
int stc_num=0, val_num=-1, lip=1;

int main()
{FILE *test=fopen("test(eg).txt","w");
FILE *wt=fopen("wordtest(eg).txt","w");
	int i, j, tmp, num_sen, sgn=1, ii=0, max=0, jj=0;
	char* stcPtr;
	FILE* in = fopen("article.txt", "r");
	FILE* out = fopen("results.txt", "w");
	FILE* stop = fopen("stopwords.txt", "r");
	scanf("%d", &num_sen);
	fread(article, sizeof(char), N, in);
	sentence_list[0].sentence=article;
	for (i=0; article[i]; ++i) {
		if ((article[i] >= 'a' && article[i] <= 'z') || (article[i] >= 'A' && article[i] <= 'Z'))
		{
			tmp = (article[i] <= 'Z') ? article[i] + 32 : article[i];
			if (trie[sgn][tmp]==0)
				trie[sgn][tmp] = ++lip;
			sgn = trie[sgn][tmp];
		}
		else if (article[i] == '.' || article[i] == '?' || article[i] == '!') {
			++frequency[sgn];
			valArr[++val_num] = sgn;
			valArr[++val_num] = -1;
			sgn = 1;
			end_sign[stc_num] = article[i];
			article[i] = '\0';
			sentence_list[++stc_num].sentence = &article[i + 1];
		}
		else if(sgn!=1){
			++frequency[sgn];
			valArr[++val_num] = sgn;
			sgn = 1;
		}
	}for(i=0;i<val_num;i++) fprintf(wt,"[%d]%d\n",i,valArr[i]);
	while (fscanf(stop,"%s", stop_word) != EOF) {
		sgn = 1;
		for (i = 0; stop_word[i]; ++i) {
			sgn = trie[sgn][stop_word[i]];
		}
		frequency[sgn] = 0;
	}
	frequency[1] = 0; //for(i=0;i<val_num;++i) printf("[%d]%d %d\n",i,valArr[i],frequency[valArr[i]]);
	for (i = 0; i < stc_num; ++i) {
		for (; valArr[jj]!= -1; ++jj) {
			sentence_list[i].times += frequency[ valArr[jj] ];
		}
		++tmpArr[sentence_list[i].times];
		++jj; fprintf(test,"[%d]%d %s\n",i,sentence_list[i].times,sentence_list[i].sentence);
	}

	for (ii=0; ii<stc_num; ++ii) {
		if (sentence_list[ii].times > max)
			max = sentence_list[ii].times;
	}
	tmp2[0] = tmpArr[0];
	for (ii = 1; ii <= max; ++ii) tmp2[ii] = tmpArr[ii] + tmp2[ii - 1];
	for (ii = 0; ii < stc_num; ++ii)  retArr[--tmp2[ sentence_list[ii].times] ] = ii;
	--stc_num;

	for (i = 0; i < 5; ++i) {
		j = stc_num - i;
		stcPtr = sentence_list[retArr[j]].sentence;
		while (*stcPtr == ' ') ++stcPtr;
		printf("%d %s%c\n", sentence_list[retArr[j]].times, stcPtr, end_sign[retArr[j]]);
	}
	for (i = 0; i < num_sen; ++i) {
		j = stc_num - i;
		stcPtr = sentence_list[retArr[j]].sentence;
		while (*stcPtr == ' ') ++stcPtr;
		fprintf(out,"%d %s%c\n", sentence_list[retArr[j]].times, stcPtr, end_sign[retArr[j]]);
	}
	return 0;
}

