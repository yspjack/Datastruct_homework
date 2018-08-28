#include <stdio.h>
#include <string.h>
int A[100],B[100],C[100];
char buf[1000];
/*
string to bigint
*/
void buf2big(char *buf,int *A)
{
    int n=strlen(buf);
    int i;
    for(i=0; i<n; i++)
    {
        A[n-i-1]=buf[i]-'0';
    }
}
/*
suppose A>B
return len of C
*/
int dec(int *A,int *B)
{
    int i;
    for(i=0; i<100; i++)
    {
        C[i]=A[i]-B[i];
    }
    for(i=0; i<100-1; i++)
    {
        if(C[i]<0)
        {
            C[i]+=10;
            C[i+1]--;
        }
    }
    int l=100;
    while(l>1 && C[l-1]==0)
    {
        --l;
    }
    return l;
}

int cmp(int *A,int *B)
{
    int i;
    for( i=99; i>=0; --i)
    {
        if(A[i]!=B[i])
            return A[i]-B[i];
    }
    return 0;
}
void print(int n)
{
    int i;
    for(i=n-1; i>=0; --i)
    {
        printf("%d",C[i]);
    }
}

int main()
{
    scanf("%s",buf);
    buf2big(buf,A);
    scanf("%s",buf);
    buf2big(buf,B);
    int neg=0,l=0;
    int c=cmp(A,B);
    if(c>=0)
    {
        l=dec(A,B);
    }
    else if(c<0)
    {
        neg=1;
        l=dec(B,A);
    }
    if(neg)
    {
        putchar('-');
    }
    print(l);
    return 0;
}

