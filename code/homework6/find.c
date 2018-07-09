#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int n;
char father[25],lch[25],rch[25];
struct Node
{
    int dep;
    char val[25];
    int parent,left,right;
} nodes[4096];
FILE *fin;
int cnt=0;
int find_node(const char *val)
{
    int i;
    for(i=1; i<=cnt; i++)
    {
        if(strcmp(nodes[i].val,val)==0)
            return i;
    }
    return 0;
}
void ins(const char *str)
{
    ++cnt;
    nodes[cnt].dep=0;
    nodes[cnt].parent=0;
    nodes[cnt].left=0;
    nodes[cnt].right=0;
    strcpy(nodes[cnt].val,str);
}

int main()
{
    fin=fopen("in.txt","r");
    int i;
    fscanf(fin,"%d",&n);
    for(i=1; i<=n; i++)
    {
        fscanf(fin,"%s%s%s",father,lch,rch);
        if(i==1)
        {
            int p=0,q=0;
            ins(father);
            p=cnt;
            if(strcmp(lch,"NULL")!=0)
            {
                ins(lch);
                q=cnt;
                nodes[p].left=q;
                nodes[q].parent=p;
                nodes[q].dep=1;
            }
            if(strcmp(rch,"NULL")!=0)
            {
                ins(rch);
                q=cnt;
                nodes[p].right=q;
                nodes[q].parent=p;
                nodes[q].dep=1;
            }
            continue;
        }
        int p=find_node(father),q=0;
        if(strcmp(lch,"NULL")!=0)
        {
            ins(lch);
            q=cnt;
            nodes[p].left=q;
            nodes[q].parent=p;
            nodes[q].dep=nodes[p].dep+1;
        }
        if(strcmp(rch,"NULL")!=0)
        {
            ins(rch);
            q=cnt;
            nodes[p].right=q;
            nodes[q].parent=p;
            nodes[q].dep=nodes[p].dep+1;
        }
    }
    scanf("%s%s",lch,rch);
    int p1=find_node(lch),p2=find_node(rch);
    //printf("dep %d,%d\n",nodes[p1].dep,nodes[p2].dep);
    if(nodes[p1].dep!=nodes[p2].dep)
    {
        if(nodes[p1].dep>nodes[p2].dep)
        {
            int t=p1;
            p1=p2;
            p2=t;
        }
        printf("%s %s %d\n",nodes[p2].val,nodes[p1].val,nodes[p2].dep-nodes[p1].dep);
        return 0;
    }
    int q1=p1,q2=p2;
    while(q1&&q2)
    {
        if(strcmp(nodes[q1].val,nodes[q2].val)==0)
        {
            printf("%s %s %d\n",nodes[q1].val,lch,nodes[p1].dep-nodes[q1].dep);
            printf("%s %s %d\n",nodes[q2].val,rch,nodes[p2].dep-nodes[q2].dep);
            break;
        }
        q1=nodes[q1].parent;
        q2=nodes[q2].parent;
    }
    return 0;
}
