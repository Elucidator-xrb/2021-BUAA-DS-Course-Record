#include<stdio.h>
#include<stdlib.h>
#define MAX 5

//cmp�������Ƚ���ָ����ֵָ�Ĵ�С��ǰ�ߴ���Ϊ����

//�������ָ�������,�����˶�ָ������

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
    //����qsort�е�1��������ָ��ͷ&��3�����������࣬aa��bbָ�붼��ָ�ڲ�ͬ�е��׵�ַ
    //aa[i]��ָ������е�i�����鲢�����ã��൱��*(aa+i)
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
