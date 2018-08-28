
#include <stdio.h>
#include <string.h>
int A[105];
int main()
{
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    int cur=q-1,no=1,left=n;
    while(1)
    {

        if(no==m)
        {
            A[cur]=1;
            no=0;

            left--;
        }
        if(left==0)
            break;
        cur=(cur+1)%n;
        if(!A[cur])
            no++;
    }printf("%d ",cur+1);
    return 0;
}
