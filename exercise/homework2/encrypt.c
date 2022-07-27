#include<stdio.h>
#include<string.h>
#include<ctype.h>
int alpha[26];

int main()
{
    FILE *fpi,*fpo;
    char key[BUFSIZ]={0},ch;
    int i,j;

    gets(key);
    for(i=0,j=0;key[i]!='\0';i++)
    {
        if(alpha[key[i]-97]==0)
        {
            alpha[key[i]-97]=1;
            key[j++]=key[i];
        }
    }
    for(i=25;i>=0;i--)
    {
        if(alpha[i]==0) key[j++]=97+i;
    }                                    //√‹‘ø…˙≥…

    fpi=fopen("encrypt.txt","r");
    fpo=fopen("output.txt","w");
    while((ch=fgetc(fpi))!=EOF)
    {
        if(islower(ch)) ch=key[ch-97];
        fputc(ch,fpo);
    }
    fclose(fpi);
    fclose(fpo);

    return 0;
}
