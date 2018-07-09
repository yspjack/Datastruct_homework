#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
int left[4096],right[4096],val[4096];
int root=0;
void dfs(int u,int d)
{
    if(u)
    {
        if(!left[u]&&!right[u])
            printf("%d %d\n",val[u],d);
        else
        {
            dfs(left[u],d+1);
            dfs(right[u],d+1);
        }
    }
}
int main()
{
    int i,n;
    scanf("%d",&n);
    for(i=1; i<=n; i++)
    {
        scanf("%d",&val[i]);
        if(i==1)
        {
            root=1;
        }
        else
        {
            int x=root,y=0;
            while(x)
            {
                y=x;
                if(val[i]<val[x])
                {
                    x=left[x];
                }
                else
                {
                    x=right[x];
                }
            }
            if(val[i]<val[y])
            {
                left[y]=i;
            }
            else
            {
                right[y]=i;
            }

        }
    }
    dfs(root,1);
    return 0;
}
