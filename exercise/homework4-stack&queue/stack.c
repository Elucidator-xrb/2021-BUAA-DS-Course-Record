#include<stdio.h>
#include<string.h>

int stack[100],top=-1;

int main()
{
    int i;
    int opt,item;
    do{
        scanf("%d",&opt);
        if(opt==1)
        {
            if(top==99) printf("error ");
            else
            {
                scanf("%d",&item);
                stack[++top]=item;
            }
        }
        else if(opt==0)
        {
            if(top==-1) printf("error ");
            else
            {
                item=stack[top--];
                printf("%d ",item);
            }
        }
        else if(opt==-1) return 0;
    }while(1);
    return 0;
}
