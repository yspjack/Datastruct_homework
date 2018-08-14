#include <stdio.h>
#include <string.h>
int A[15];
int n;
void dfs(int cur)
{
    if(cur==n)
    {
        int i;
        for(i=0;i<n;i++)
        {
            printf("%d ",A[i]);
        }
        printf("\n");
        return;
    }
    int i;
    for(i=1;i<=n;i++)
    {
        int ok=1;
        int j;
        for(j=0;j<cur;j++)
            if(A[j]==i)
            {
                ok=0;
                break;
            }
        if(ok)
        {
            A[cur]=i;
            dfs(cur+1);
            A[cur]=0;
        }
    }
}

int main()
{
    scanf("%d",&n);
    memset(A,0,sizeof(0));
    dfs(0);
    return 0;
}

