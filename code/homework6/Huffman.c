#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
int freq[256];
struct Node
{
    char code[256];
    int count;
    int ch;
    int parent,left,right,next;
}nodes[1000];
int nodes_cnt=0;
const int vhead=0;
void ins(char ch,int cnt)
{
    ++nodes_cnt;
    memset(&nodes[nodes_cnt],0,sizeof(nodes[0]));
    nodes[nodes_cnt].ch=ch;
    nodes[nodes_cnt].count=cnt;

    if(nodes[vhead].next==0)
    {
        nodes[vhead].next=nodes_cnt;
        return;
    }
    int p=vhead,q=nodes[vhead].next;
    while(q)
    {
        if(nodes[q].count>cnt)
            break;
        p=q;
        q=nodes[q].next;
    }
    nodes[nodes_cnt].next=q;
    nodes[p].next=nodes_cnt;
}
void dump_list(int u)
{
    while(u)
    {
        printf("list node %d %d:%d\n",u,nodes[u].ch,nodes[u].count);
        u=nodes[u].next;
    }
}
int build_tree(int u)
{
    int v=nodes[u].next;
    if(!v)
    {
        return u;
    }
    ins(0,nodes[u].count+nodes[v].count);
    int p=nodes_cnt;
    nodes[p].left=u;
    nodes[p].right=v;
    nodes[u].parent=p;
    nodes[v].parent=p;
    return build_tree(nodes[v].next);
}
void dump_tree(int u)
{
    if(!u)
        return;
    struct Node p=nodes[u];
    printf("tree node %d %c(%d):%d %s\n",u,p.ch,p.ch,p.count,p.code);
    dump_tree(p.left);
    dump_tree(p.right);
}
char buf[256];
char mapping[256][256];
void encode(int u,int dep)
{
    if(!u)
        return;
    if(!nodes[u].left && !nodes[u].right){

        strcpy(mapping[nodes[u].ch],buf);
        strcpy(nodes[u].code,buf);
        return;
    }
    if(nodes[u].left)
    {
        buf[dep]='0';
        buf[dep+1]='\0';
        encode(nodes[u].left,dep+1);
    }
    if(nodes[u].right)
    {
        buf[dep]='1';
        buf[dep+1]='\0';
        encode(nodes[u].right,dep+1);
    }
}

void dump_map()
{
    int i;
    for(i=0;i<256;i++)
    {
        if(freq[i])
            printf("%c(%d):%s\n",i,i,mapping[i]);
    }
}
void build()
{
    int i;
    for(i=0;i<256;i++)
    {
        if(freq[i]>0)
        {
            ins(i,freq[i]);
        }
    }
    //dump_list(nodes[vhead].next);
    int root=build_tree(nodes[vhead].next);
    encode(root,0);
    //dump_tree(root);
    dump_map();
}

void compress(FILE *fin,FILE *fout)
{
    int bits=0,tmp=0;
    int ch;
    while((ch=fgetc(fin))!=EOF)
    {
        if(ch=='\n')
            continue;
        int i,n=strlen(mapping[ch]);
        for(i=0;i<n;i++)
        {
            tmp<<=1;
            if(mapping[ch][i]=='1')
            {
                tmp|=1;
            }
            if(++bits==8)
            {
                printf("%x",tmp&0xff);
                fputc(tmp,fout);
                bits=0;
                tmp=0;
            }
        }
    }
    do
    {
        ch=0;
        int i,n=strlen(mapping[ch]);
        for(i=0;i<n;i++)
        {
            tmp<<=1;
            if(mapping[ch][i]=='1')
            {
                tmp|=1;
            }
            if(++bits==8)
            {
                printf("%x",tmp&0xff);
                fputc(tmp,fout);
                bits=0;
                tmp=0;
            }
        }
    }
    while(0);
    if(bits>0)
    {
        tmp<<=(8-bits);
        printf("%x",tmp&0xff);
        fputc(tmp,fout);
    }
}
int main()
{
    int ch;
    FILE *fin=fopen("input.txt","r");
    FILE *fout=fopen("output.txt","w");
    while((ch=fgetc(fin))!=EOF)
    {
        if(ch=='\n')
            continue;
        freq[ch]++;
    }
    freq[0]=1;
    build();
    fseek(fin,0,SEEK_SET);
    compress(fin,fout);
    return 0;
}
