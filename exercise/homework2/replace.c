#include<stdio.h>
#include<string.h>
#include<ctype.h>

char buf[BUFSIZ];
char tmp[BUFSIZ];

char *_strstr(char *dest,char *source)
{
    int i=0,j=0;
    while(dest[i]!='\0' && source[j]!='\0')
    {
        if(tolower(dest[i])==tolower(source[j])) i++,j++;
        else i-=(j-1),j=0;
    }
    if(source[j]=='\0') return dest+i-j;
    else return NULL;
}

int main()
{
    FILE *fpi,*fpo;
    char in[BUFSIZ],out[BUFSIZ];
    char *p;
    int len_i,i;

    fpi=fopen("filein.txt","r");
    fpo=fopen("fileout.txt","w");
    gets(in),len_i=strlen(in);
    gets(out);

    while(fgets(buf,BUFSIZ,fpi)!=NULL)//怪怪，用feof本地无误，其他地方会有问题
    {//别用eof了
//        fgets(buf,BUFSIZ,fpi);
        p=_strstr(buf,in);
        while(p!=NULL)
        {
            strcpy(tmp,p+len_i);
            *p='\0';
            strcat(buf,out);
            strcat(buf,tmp);
            p=_strstr(p+len_i,in);
        }
        fputs(buf,fpo);
    }

    fclose(fpi);
    fclose(fpo);
    return 0;
}
