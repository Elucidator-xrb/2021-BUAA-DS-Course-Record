#include<stdio.h>
#include<stdlib.h>
#define MAX 5

//cmp函数：比较两指针所指值的大小，前者大则为升序

//灵活运用指针的特性,巩固了对指针的理解

int arr[MAX]={9,3,10,15,3};
int arr2[MAX][2]={ {91,2},{3,1},{10,5},{15,-1},{3,0}};
struct lab
{
    int x;
    int y;
    int z;
} arr3[MAX]={ {1,9,5},
              {2,9,3},
              {5,3,2},
              {19,1,4},
              {7,9,10} };

int cmp2(const void *a,const void *b)
{
    int *aa=(int *)a;
    int *bb=(int *)b;
    return (aa[0]>bb[0])-(aa[0]<bb[0]);
}
int cmp3(const void *a,const void *b)
{
    int *aa=(int *)a;
    int *bb=(int *)b;
    return (aa[1]<bb[1])-(aa[1]>bb[1]);
    //根据qsort中第1个参数所指开头&第3个参数所设间距，aa、bb指针都会指在不同行的首地址
    //aa[i]即指向该行中第i个区块并解引用，相当于*(aa+i)
}
int cmp4(const void *a,const void *b)
{
    struct lab *aa=(struct lab *)a;
    struct lab *bb=(struct lab *)b;
    if((*aa).y!=(*bb).y)
        return ( (*aa).y>(*bb).y ) - ( (*aa).y<(*bb).y );
    else
        return ( (*aa).z>(*bb).z ) - ( (*aa).z<(*bb).z );
}

int main()
{
    int i;
    //printf("%d %d",sizeof(arr2),sizeof(arr2[0]));
    //qsort(arr2,MAX,sizeof(arr2[0]),cmp2);
    qsort(arr3,MAX,sizeof(arr3[0]),cmp4);

    for(i=0;i<MAX;i++)
        printf("%d %d\n",arr2[i][0],arr2[i][1]);
    puts("");
    for(i=0;i<MAX;i++)
        printf("%d %d %d\n",arr3[i].x,arr3[i].y,arr3[i].z);

    return 0;
}
