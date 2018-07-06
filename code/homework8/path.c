#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int n,m;
typedef struct
{
    int id,u,v;
} Edge;
Edge edges[10000];
int vis[10000];
int head[10000];

int cmp(const void *a,const void *b)
{
    Edge *e1=(Edge*)a,*e2=(Edge*)b;
    return e1->id-e2->id;
}
void ins()
{

}
int p[10000];
void dfs(int u,int d)
{
    int i;
    if(u==n-1)
    {
        for(i=0; i<d; i++)
            printf("%d ",p[i]);
        printf("\n");
        return;
    }
    for(i=0; i<m; i++)
    {
        if(edges[i].u==u)
        {
            int v=edges[i].v;
            if(!vis[v])
            {
                vis[v]=1;
                p[d]=edges[i].id;
                dfs(v,d+1);
                p[d]=0;
                vis[v]=0;
            }
        }
        else if(edges[i].v==u)
        {
            int v=edges[i].u;
            if(!vis[v])
            {
                vis[v]=1;
                p[d]=edges[i].id;
                dfs(v,d+1);
                p[d]=0;
                vis[v]=0;
            }
        }
    }
    return;
}

int main()
{
    int i;
    scanf("%d%d",&n,&m);
    for(i=0; i<m; i++)
    {
        scanf("%d%d%d",&edges[i].id,&edges[i].u,&edges[i].v);
    }
    qsort(edges,m,sizeof(Edge),cmp);
    vis[0]=1;
    dfs(0,0);
}
