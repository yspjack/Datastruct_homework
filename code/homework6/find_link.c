#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

struct Node
{
    int dep;
    char val[25];
    struct Node *parent,*left,*right;
};
typedef struct Node Node;

int n=0;
char father[25],lch[25],rch[25];
FILE *fin=NULL;
Node *root=NULL;


Node* find_node_real(Node *u,const char *val)
{
    if(u==NULL)
        return NULL;
    if(strcmp(u->val,val)==0)
    {
        return u;
    }
    Node *lch=NULL,*rch=NULL;
    lch=find_node_real(u->left,val);
    if(lch!=NULL)
        return lch;
    rch=find_node_real(u->right,val);
    if(rch!=NULL)
        return rch;
    return NULL;
}
Node* find_node(const char *val)
{
    return find_node_real(root,val);
}

Node* newNode(const char *name)
{
    Node *tmp=malloc(sizeof(Node));
    memset(tmp,0,sizeof(Node));
    strcpy(tmp->val,name);
    return tmp;
}
void dump(Node *u)
{
    if(u==NULL)
        return;
    dump(u->left);
    printf("%s\n",u->val);
    dump(u->right);
}
int main()
{
    fin=fopen("in.txt","r");
    int i;
    fscanf(fin,"%d",&n);
    for(i=1; i<=n; i++)
    {
        fscanf(fin,"%s%s%s",father,lch,rch);
        if(root==NULL)
        {
            root=newNode(father);
            if(strcmp(lch,"NULL")!=0)
            {
                Node *q=newNode(lch);
                q->dep=1;
                root->left=q;
                q->parent=root;
            }
            if(strcmp(rch,"NULL")!=0)
            {
                Node *q=newNode(rch);
                q->dep=1;
                root->right=q;
                q->parent=root;
            }
        }
        else
        {
            Node* p=find_node(father);
            if(strcmp(lch,"NULL")!=0)
            {
                Node *q=newNode(lch);
                p->left=q;
                q->parent=p;
                q->dep=p->dep+1;
            }
            if(strcmp(rch,"NULL")!=0)
            {
                Node *q=newNode(rch);
                p->right=q;
                q->parent=p;
                q->dep=p->dep+1;
            }
        }
    }
    scanf("%s%s",lch,rch);
    Node *p1=find_node(lch),*p2=find_node(rch);
    //printf("dep %d,%d\n",nodes[p1].dep,nodes[p2].dep);
    if(p1->dep!=p2->dep)
    {
        if(p1->dep>p2->dep)
        {
            Node *t=p1;
            p1=p2;
            p2=t;
        }
        printf("%s %s %d\n",p2->val,p1->val,p2->dep-p1->dep);
        return 0;
    }
    Node *q1=p1,*q2=p2;
    while(q1&&q2)
    {
        if(strcmp(q1->val,q2->val)==0)
        {
            printf("%s %s %d\n",q1->val,lch,p1->dep-q1->dep);
            printf("%s %s %d\n",q2->val,rch,p2->dep-q2->dep);
            break;
        }
        q1=q1->parent;
        q2=q2->parent;
    }
    return 0;
}
