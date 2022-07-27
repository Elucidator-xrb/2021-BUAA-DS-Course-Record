#include<stdio.h>

int main()
{
    FILE *fp1=fopen("test.txt","r");
    FILE *fp2=fopen("test(eg).txt","r");
    char ch1[100],ch2[100];
    int cnt=0;
    while(fscanf(fp1,"%s",ch1)!=EOF && fgets(fp2,"%s",ch2)!=EOF)
    {
        printf("%s %s\n",ch1,ch2);
        //if(ch1!=ch2) printf("%d==[ch1]:%c [ch2]:%c\n",cnt,ch1,ch2);
    }
    printf("over!");
    return 0;
}
