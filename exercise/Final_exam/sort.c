#include<stdio.h>
#include<stdlib.h>

int arr[110];
int cnt=0;

void swap(int a,int b);
void selectSort(int num);
void bubbleSort(int num);
void heapSort(int num);
void mergeSort(int num);
void quickSort(int low,int high);

void adjust(int i,int num);
void merge(int tmp[],int low,int mid,int high);
void msort_rc(int tmp[],int low,int high);

int rec;

int main()
{
    int num,opt;
    int i;
    scanf("%d%d",&num,&opt);
    for(i=0;i<num;i++)
        scanf("%d",&arr[i]);     rec=num;
    switch(opt)
    {
        case 1:selectSort(num);break;
        case 2:bubbleSort(num);break;
        case 3:heapSort(num);break;
        case 4:mergeSort(num);break;
        case 5:quickSort(0,num-1);break;
    }
    for(i=0;i<num;i++)
        printf("%d ",arr[i]);
    printf("\n%d",cnt);
    return 0;
}

void swap(int a,int b) // !异或的交换并不泛用：自己和自己/非整数 都不行
{
    int tmp;
    tmp=arr[a];
    arr[a]=arr[b];
    arr[b]=tmp;
}

void selectSort(int num)
{
    int i,j,min;
    for(i=0;i<num;i++)
    {
        min=i;
        for(j=i+1;j<num;j++)
        {
            min=(arr[j]<arr[min])?j:min;
            cnt++;
        }
        if(min!=i) swap(min,i);
    }
}

void bubbleSort(int num)
{
    int i,j,flag;
    for(i=1;i<=num-1;i++)
    {
        flag=0;
        for(j=0;j<num-i;j++)
        {
            cnt++;
            if(arr[j]>arr[j+1])
            {
                swap(j,j+1);
                flag=1;
            }
        }
        if(flag==0) break;
    }
}

void heapSort(int num)
{
    int i;
    for(i=(num-2)/2;i>=0;i--)
        adjust(i,num);
    //for(i=0;i<num;i++) printf("%d ",arr[i]); puts("");
    for(i=num-1;i>=0;i--)
    {
        swap(i,0);
        adjust(0,i);//当num都比最大数组下标大1时
    }
}

void mergeSort(int num)
{
    int *tmp;
    tmp=(int*)malloc(sizeof(int)*num);
    msort_rc(tmp,0,num-1);
    free(tmp);
}

void quickSort(int low,int high)
{
//    int i=low,j=high+1; int k;
//    int pivot=low;
//    if(low<high)
//    {
//        while(1)
//        {
//            do{cnt++;}while(arr[++i]<arr[pivot] && i!=high);
//            do{cnt++;}while(arr[--j]>arr[pivot] && j!=low);
//            if(i<j) swap(i,j);
//            else break;
//            for(k=0;k<rec;k++) printf("%-4d ",arr[k]);puts("");
//        }
//        swap(pivot,j);
//        for(k=0;k<rec;k++) printf("%-4d ",arr[k]);puts("");
//        quickSort(low,j-1);
//        quickSort(j+1,high);
//    } 会多比较——82次
    int i,last;
    if(low<high)
    {
        last=low;
        for(i=low+1;i<=high;i++)
        {
            cnt++;
            if(arr[i]<arr[low])swap(++last,i);
        }
        swap(low,last);
        quickSort(low,last-1);
        quickSort(last+1,high);
    }
}

void adjust(int i,int num)
{

    int j,tmp;
    tmp=arr[i]; j=2*i+1;//以0为头的完全二叉树
    while(j<num)
    {
        cnt++;
        if(j+1<num && arr[j]<arr[j+1]) j++;
        if(tmp>=arr[j]) break;
        arr[(j-1)/2]=arr[j];
        j=2*j+1;
    }
    arr[(j-1)/2]=tmp;
}

void merge(int tmp[],int low,int mid,int high)
{
    int i=low,j=mid+1,q=low;
    while(i<=mid && j<=high)
    {
        cnt++;
        if(arr[i]<=arr[j]) tmp[q++]=arr[i++];
        else tmp[q++]=arr[j++];
    }
    while(i<=mid)  tmp[q++]=arr[i++];
    while(j<=high) tmp[q++]=arr[j++];
    for(i=low;i<=high;i++) arr[i]=tmp[i];
}

void msort_rc(int tmp[],int low,int high)
{
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        msort_rc(tmp,low,mid);
        msort_rc(tmp,mid+1,high);
        merge(tmp,low,mid,high);
    }
}
