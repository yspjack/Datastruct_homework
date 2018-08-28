#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int G[20][20];
int vis[20][20];
int min(int x,int y)
{
    return x<y?x:y;
}
int main()
{
    int i,j;
    for(i=1; i<=19; i++)
    {
        for(j=1; j<=19; ++j)
        {
            scanf("%d",&G[i][j]);
        }
    }
    memset(vis,0,sizeof(vis));
    int dx,dy;
    int ansx,ansy,winner=0;
    for(i=1; i<=19; i++)
    {
        for(j=1; j<=19; ++j)
        {
            if(G[i][j]==0)
                continue;
            int c=G[i][j];
            int x,y;
            for(dx=-1; dx<=1; dx++)
            {
                for(dy=-1; dy<=1; dy++)
                {
                    if(dx==0 && dy==0)
                        continue;
                    int cnt=0;
                    x=i+dx;
                    y=j+dy;
                    if(x<1 ||y<1||x>19||y>19)
                        continue;
                    if(G[x][y]!=0)
                    {
                        cnt=1;
                        while(x>=1&&y>=1&&x<=19&&y<=19)
                        {
                            if(G[x][y]!=c)
                                break;
                            ++cnt;
                            x+=dx;
                            y+=dy;
                            //if(cnt==4)
                            //    break;
                        }
                    }
                    int blk=2;
                    if(x>=1&&y>=1&&x<=19&&y<=19&&G[x][y]==0)
                        --blk;
                    x=i-dx;
                    y=j-dy;
                    if(x>=1&&y>=1&&x<=19&&y<=19&&G[x][y]==0)
                        --blk;
                    //printf("%d %d %d %d %d %d\n",i,j,dx,dy,cnt,blk);
                    if(cnt==4 && blk<2)
                    {
                        ansx=i;
                        ansy=j;
                        winner=c;
                        goto output_found;
                    }
                }
            }
        }
    }
    printf("No\n");
    return 0;
output_found:
    printf("%d:%d,%d\n",winner,ansx,ansy);
    return 0;
}
