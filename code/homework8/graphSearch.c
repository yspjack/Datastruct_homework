#include <stdio.h>
#include <string.h>
int n,m;
int G[105][105];
int queue[10005];
int front=0,rear=0;
int vis[105];
void bfs()
{
    memset(vis,0,sizeof(vis));
    queue[++rear]=0;
    vis[0]=1;
    while(front<rear)
    {
        front++;
        int u=queue[front];
        printf("%d ",u);
        int i;
        for(i=0;i<n;i++)
        {
            if(G[u][i] && !vis[i])
            {
                queue[++rear]=i;
                vis[i]=1;
            }
        }
    }
}
void dfs(int u)
{
    if(vis[u])
        return;
    vis[u]=1;
    printf("%d ",u);
    int i;
    for(i=0;i<n;i++)
    {
        if(G[u][i])
            dfs(i);
    }
}
int u,v;
int main()
{
    scanf("%d%d",&n,&m);
    int i,j;
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&u,&v);
        G[u][v]=G[v][u]=1;
    }
    int de;
    scanf("%d",&de);
    memset(vis,0,sizeof(vis));dfs(0);printf("\n");
    bfs();printf("\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==de||j==de)
            {
                G[i][j]=0;
            }
        }
    }

    memset(vis,0,sizeof(vis));dfs(0);printf("\n");
    bfs();printf("\n");
    return 0;
}
