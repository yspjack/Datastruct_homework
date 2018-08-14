#include <stdio.h>
#include <assert.h>
#include <string.h>
#pragma GCC optimize("O3")
#define INF 100000000
struct Station
{
    char name[512];
    int exchange;
} stations[5000];
int cnt_stations=0;

static inline int find_st(char *str)
{
    int i;
    for(i=1; i<=cnt_stations; i++)
    {
        if(strcmp(stations[i].name,str)==0)
            return i;
    }
    return -1;
}

static inline void ins_station(char *name,int f)
{
    ++cnt_stations;
    strcpy(stations[cnt_stations].name,name);
    stations[cnt_stations].exchange=f;
    //printf("%d:%s\n",cnt_stations,name);
}

struct E
{
    int next,from,to,line_id;
} edges[100000];
int edges_cnt=0;
int head[5000];


static inline void link(int u,int v,int id)
{
    ++edges_cnt;
    edges[edges_cnt].next=head[u];
    edges[edges_cnt].from=u;
    edges[edges_cnt].to=v;
    edges[edges_cnt].line_id=id;

    head[u]=edges_cnt;
}

int vis[5000],d[5000],p[5000];
int pre_edge[5000];
void dij(int s)
{
    int n=cnt_stations;
    memset(vis,0,sizeof(vis));
    int i;
    for(i=1; i<=n; i++)
        d[i]=INF;
    d[s]=0;
    int y;
    for(i=1; i<=n; i++)
    {
        int x=1,m=INF;
        for(y=1; y<=n; y++)
        {
            if(!vis[y] && d[y]<m)
            {
                m=d[y];
                x=y;
            }
        }
        vis[x]=1;
        int u;
        for(u=head[x]; u; u=edges[u].next)
        {
            int y=edges[u].to;
            if(d[y]>d[x]+1)
            {
                d[y]=d[x]+1;
                p[y]=x;
                pre_edge[y]=u;
            }
        }
    }
}

char buf[512],buf2[512];
int path[5000];
void print_path(int s,int t)
{
    int u=t;
    int cnt=0;
    int i;

    while(u!=s)
    {
        path[cnt++]=pre_edge[u];
        u=p[u];
    }
    /*
        for(i=cnt-1;i>=0;i--)
        {
            printf("%d:%d %s\n",i,edges[path[i]].line_id,stations[edges[path[i]].to].name);
        }
    */
    printf("%s-",stations[s].name);
    int sum=1;
    int cur=edges[path[cnt-1]].line_id;
    for(i=cnt-2; i>=0; i--)
    {
        u=edges[path[i]].from;
        if(u!=s && edges[path[i+1]].line_id!=edges[path[i]].line_id)
        {
            printf("%d(%d)-",cur,sum);
            printf("%s-",stations[u].name);
            cur=edges[path[i]].line_id;
            sum=0;
        }
        sum++;
    }

    printf("%d(%d)-",cur,sum);
    printf("%s",stations[t].name);
}
void dfs(int u)
{
    vis[u]=1;
    printf("%d:%s\n",u,stations[u].name);
    register int i;
    for(i=head[u]; i; i=edges[i].next)
    {
        int v=edges[i].to;
        if(!vis[v])
            dfs(v);
    }
}
int main()
{
    FILE *fin=fopen("bgstations.txt","r");

    int lines;
    fscanf(fin,"%d",&lines);
    while(lines--)
    {
        int id,station;
        fscanf(fin,"%d%d",&id,&station);
        int u=-1,v=-1;
        while(station--)
        {
            int f;
            fscanf(fin,"%s%d",buf,&f);
            int tmp=find_st(buf);
            if(tmp==-1)
            {
                ins_station(buf,f);
                v=cnt_stations;
            }
            else
            {
                v=tmp;
            }
            if(u!=-1)
            {
                link(u,v,id);
                link(v,u,id);
            }
            u=v;
        }
    }
    scanf("%s%s",buf,buf2);
    int s,t;
    s=find_st(buf);
    assert(s!=-1);
    t=find_st(buf2);
    assert(t!=-1);

    memset(vis,0,sizeof(vis));
    dij(s);
//    for(t=0; t<=cnt_stations; t++)
//        printf("%d\n",d[t]);
    print_path(s,t);
    return 0;
}
