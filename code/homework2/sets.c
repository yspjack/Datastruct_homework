#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int A[1000003],B[1000003],vis[1000003];

int main()
{
    int x,p1=0,p2=0;
    while(scanf("%d",&x)==1)
    {
        if(x==-1)break;
        A[p1++]=x;
    }
    while(scanf("%d",&x)==1)
    {
        if(x==-1)break;
        B[p2++]=x;
        vis[x]=1;
    }
    int i;
    for(i=0;i<p1;i++)
    {
        if(!vis[A[i]])
        {
            printf("%d ",A[i]);
        }
    }
    return 0;
}


