#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void swap(int *a,int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}
int cnt=0;

//1：选择排序
void select_sort(int A[ ],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            cnt++;
            if(A[i]>A[j])
                swap(A+i,A+j);
        }
    }
}
//2：冒泡排序
void bubble(int *A,int n)
{
    int i,j;
    for(i=0; i<n-1; i++)
    {
        int swaped=0;
        for(j=0; j<n-i-1; j++)
        {
            ++cnt;
            if(A[j]>A[j+1])
            {
                swaped=1;
                swap(A+j,A+j+1);
            }

        }
        if(!swaped)
            return;
    }
}
//3：堆排序
void adjust(int k[ ],int i,int n)
{
    int j,temp;
    temp=k[i];
    j=2*i+1;
    while(j<n)
    {
        if(j<n-1 && k[j]<k[j+1])
            j++;
        ++cnt;
        if(temp>=k[j])
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;
}
void dump(int *A,int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        if(i==0)
            printf("%d",A[i]);
        else
            printf(" %d",A[i]);
    }
    printf("\n");
}
void heapSort(int x[ ],int n)
{
    int i;
    for(i=n/2-1;i>=0;--i)
    {
        adjust(x,i,n);
    }
    for(i=n-1;i>0;i--)
    {
        //printf("max:%d\n",x[0]);
        //dump(x,n);
        swap(x,x+i);
        adjust(x,0,i);
    }
}


//4：二路归并排序
void merge(int x[ ],int tmp[ ],int left,int leftend,int rightend)
{
    int i=left, j=leftend+1, q=left;
    while(i<=leftend && j<=rightend)
    {
        ++cnt;
        if(x[i]<=x[j])
            tmp[q++]=x[i++];
        else
            tmp[q++]=x[j++];
    }

    while(i<=leftend)
        tmp[q++]=x[i++];

    while(j<=rightend)
        tmp[q++]=x[j++];

    for(i=left; i<=rightend; i++)
        x[i]=tmp[i];

}
void mergeSort(int x[],int tmp[],int left,int right)
{
    if(left<right)
    {
        int mid=(left+right)/2;
        mergeSort(x,tmp,left,mid);
        mergeSort(x,tmp,mid+1,right);

        merge(x,tmp,left,mid,right);
    }
}
//5：快速排序
void quickSort(int k[ ],int left,int right)
{
    int i, last;
    if(left<right)
    {
        last=left;
        for(i=left+1; i<=right; i++)
        {
            ++cnt;
            if(k[i]<k[left])
                swap(&k[++last],&k[i]);
        }
        swap(&k[left],&k[last]);
        quickSort(k,left,last-1);
        quickSort(k,last+1,right);
    }
}

int A[1000],tmp[1000];
int n,op;

int main()
{
    int i;
    scanf("%d%d",&n,&op);
    for(i=0; i<n; i++)
    {
        scanf("%d",A+i);
    }
    if(op==1)
    {
        select_sort(A,n);
    }
    else if(op==2)
    {
        bubble(A,n);
    }
    else if(op==3)
    {
        heapSort(A,n);
    }
    else if(op==4)
    {
        mergeSort(A,tmp,0,n-1);
    }
    else if(op==5)
    {
        quickSort(A,0,n-1);
    }
    for(i=0; i<n; i++)
    {
        if(i==0)
            printf("%d",A[i]);
        else
            printf(" %d",A[i]);
    }
    printf("\n");
    printf("%d\n",cnt);
    return 0;
}

