#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int n,m;
int P[10005];
int findset(int x)
{
    return P[x]==x?x:(P[x]=findset(P[x]));
}

struct E
{
    int id,u,v,w;
}edges[100005];

int cmp(const void *a,const void *b)
{
    struct E *e1=(struct E *)a,*e2=(struct E *)b;
    return e1->w-e2->w;
}
int cmpint(const void *a,const void *b)
{
    int *e1=(int*)a,*e2=(int*)b;
    return *e1-*e2;
}
int ans[10005];
int p=0;
int main()
{
    int i;
    scanf("%d%d",&n,&m);
    for(i=0;i<=n;i++)
    {
        P[i]=i;
    }
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d%d",&edges[i].id,&edges[i].u,&edges[i].v,&edges[i].w);
    }
    qsort(edges,m,sizeof(struct E),cmp);
    long long sum=0;
    for(i=0;i<m;i++)
    {
        int x=edges[i].u,y=edges[i].v;
        int px,py;
        px=findset(x);
        py=findset(y);
        if(px!=py)
        {
            P[px]=py;
            sum+=edges[i].w;
            ans[p++]=edges[i].id;
        }
    }
    qsort(ans,p,sizeof(int),cmpint);
    printf("%lld\n",sum);
    for(i=0;i<p;i++)
    {
        printf("%d ",ans[i]);
    }
    printf("\n");
    return 0;
}
