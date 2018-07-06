#include <stdio.h>
#include <assert.h>
#pragma GCC optimize ("O3")
#define INF 10000000
struct Station
{
    char name[512];
    int exchange;
} stations[5000] __attribute__((aligned(sizeof(size_t))));
int cnt_stations=0;

char* _strcpy(char *dest, const char *src)
{
    while ((*dest++ = *src++));
    return dest;
}
#define strcpy _strcpy
int strcmp(const char *l, const char *r)
{
	for (; *l==*r && *l; l++, r++);
	return *l - *r;
}
void *memset(void *dest, int c, size_t n);

int find_st(char *str)
{
    int i;
    for(i=1; i<=cnt_stations; i++)
    {
        if(strcmp(stations[i].name,str)==0)
            return i;
    }
    return -1;
}

void ins_station(char *name,int f)
{
    ++cnt_stations;
    strcpy(stations[cnt_stations].name,name);
    stations[cnt_stations].exchange=f;
    //printf("%d:%s\n",cnt_stations,name);
}

int line_id[500][500];
int G[500][500];


void link(int u,int v,int id)
{
    G[u][v]=1;
    line_id[u][v]=id;
}

int vis[5000],d[5000],p[5000];
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
        for(y=1; y<=n; y++)
        {
            if(d[y]>d[x]+G[x][y])
            {
                d[y]=d[x]+G[x][y];
                p[y]=x;
            }

        }
    }
}

char buf[512],buf2[512];
int next[1000];
void print_path(int s,int t)
{
    int u=t;
    next[u]=0;
    while(u!=s)
    {
        next[p[u]]=u;
        u=p[u];
    }
    printf("%s-",stations[s].name);
    int sum=0;
    int cur=line_id[s][next[s]];
    for(u=s; u!=t; u=next[u])
    {
        if(stations[u].exchange)
        {
            if(u!=s && line_id[u][next[u]]!=line_id[p[u]][u])
            {
                printf("%d(%d)-",cur,sum);
                printf("%s-",stations[u].name);
                cur=line_id[u][next[u]];
                sum=0;
            }
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
    int i;
    for(i=1; i<=cnt_stations; i++)
    {
        if(G[i] && !vis[i])
            dfs(i);
    }
}
int main()
{

    do
    {
        int i,j;
        for(i=0; i<500; i++)
        {
            for(j=0; j<500; j++)
            {
                if(i!=j)
                    G[i][j]=INF;
                else
                    G[i][j]=0;
            }
        }
    }
    while(0);
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
            if(1||f)
            {
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

            }
            else
            {
                ins_station(buf,f);
                v=cnt_stations;

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
    //dfs(s);
//    printf("s=%d,t=%d\n",s,t);
    dij(s);
//    for(t=0; t<=cnt_stations; t++)
//        printf("%d\n",d[t]);
    print_path(s,t);

    return 0;
}
