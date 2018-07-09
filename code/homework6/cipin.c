#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
struct Node
{
    char *val;
    int freq;
    struct Node *lch,*rch;
};
struct Node *root=NULL;

void ins(const char *str)
{
    if(root==NULL)
    {
        struct Node *tmp;
        tmp=malloc(sizeof(struct Node));
        int n=strlen(str);
        tmp->val=malloc(sizeof(char)*(n+1));
        strcpy(tmp->val,str);
        tmp->freq=1;
        tmp->lch=NULL;
        tmp->rch=NULL;
        root=tmp;
    }
    else
    {
        struct Node *p=root,*q=NULL;
        while(p)
        {
            q=p;
            int cmp=strcmp(str,p->val);
            if(cmp<0)
            {
                p=p->lch;
            }
            else if(cmp>0)
            {
                p=p->rch;
            }
            else
            {
                p->freq++;
                return;
            }
        }

        struct Node *tmp;
        tmp=malloc(sizeof(struct Node));
        int n=strlen(str);
        tmp->val=malloc(sizeof(char)*(n+1));
        strcpy(tmp->val,str);
        tmp->freq=1;
        tmp->lch=NULL;
        tmp->rch=NULL;

        if(strcmp(str,q->val)<0)
        {
            q->lch=tmp;
        }
        else
        {
            q->rch=tmp;
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
void dump(struct Node* u)
{
    if(u)
    {
        dump(u->lch);
        printf("%s %d\n", u->val,u->freq);
        dump(u->rch);
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
    printf("%s ",root->val);
    if(root->rch)
    {
        printf("%s ",root->rch->val);
    }
    if(root->rch && root->rch->rch)
    {
        printf("%s",root->rch->rch->val);
    }
    printf("\n");
    dump(root);
    return 0;
}
