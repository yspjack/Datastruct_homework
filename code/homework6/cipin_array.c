#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    char *val;
    int freq;
    int lch,rch;
}nodes[1<<20];
int root=0;
int cnt=0;

void ins(const char *str)
{
    if(root==0)
    {
        ++cnt;
        int tmp=cnt;
        int n=strlen(str);
        nodes[tmp].val=malloc(sizeof(char)*(n+1));
        strcpy(nodes[tmp].val,str);
        nodes[tmp].freq=1;
        nodes[tmp].lch=0;
        nodes[tmp].rch=0;
        root=tmp;
    }
    else
    {
        int p=root,q=0;
        while(p)
        {
            q=p;
            int cmp=strcmp(str,nodes[p].val);
            if(cmp<0)
            {
                p=nodes[p].lch;
            }
            else if(cmp>0)
            {
                p=nodes[p].rch;
            }
            else
            {
                nodes[p].freq++;
                return;
            }
        }

        int tmp=++cnt;
        int n=strlen(str);
        nodes[tmp].val=malloc(sizeof(char)*(n+1));
        strcpy(nodes[tmp].val,str);
        nodes[tmp].freq=1;
        nodes[tmp].lch=0;
        nodes[tmp].rch=0;

        if(strcmp(str,nodes[q].val)<0)
        {
            nodes[q].lch=tmp;
        }
        else
        {
            nodes[q].rch=tmp;
        }
    }
}
char buf[1024];
int getword()
{
    int ch=getchar();
    while(!isalpha(ch))
    {
        if(ch==EOF)
            return 0;
        ch=getchar();
    }
    int p=0;
    while(isalpha(ch))
    {
        buf[p++]=tolower(ch);
        ch=getchar();
    }
    buf[p]=0;
    return 1;
}
void dump(int u)
{
    if(u)
    {
        dump(nodes[u].lch);
        printf("%s %d\n", nodes[u].val,nodes[u].freq);
        dump(nodes[u].rch);
    }
}
int main()
{
    //freopen("article.txt","r",stdin);
    while(getword())
    {
        //printf("$$%s$$\n",buf);
        ins(buf);
    }
    printf("%s ",nodes[root].val);
    if(nodes[root].rch)
    {
        printf("%s ",nodes[nodes[root].rch].val);
    }
    if(nodes[root].rch && nodes[nodes[root].rch].rch)
    {
        printf("%s",nodes[nodes[nodes[root].rch].rch].val);
    }
    printf("\n");
    dump(root);
    return 0;
}
