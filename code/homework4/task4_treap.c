#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define true 1
#define false 0
#define bool int
struct Node
{
    int rank;
    char *val;
    int freq;
    struct Node *right;
    struct Node *left;
} __attribute__((aligned(sizeof(long))));

typedef struct Node Node;
struct Node *root;
static void left_rotate(Node **node)
{
    Node *right = (*node)->right;
    (*node)->right = right->left;
    right->left = (*node);
    (*node)=right;
}
static void right_rotate(Node **node)
{
    Node *left = (*node)->left;
    (*node)->left = left->right;
    left->right = (*node);
    (*node)=left;
}

void insert(Node **node,char *word)
{
    if(*node==NULL)
    {
        (*node)=(Node*)malloc(sizeof(Node));
        (*node)->freq=1;
        int len=strlen(word);
        (*node)->val=(char*)malloc(sizeof(char)*(len+1));
        strcpy((*node)->val,word);
        (*node)->freq=1;
        (*node)->left=NULL;
        (*node)->right=NULL;
        (*node)->rank=rand();

    }
    else
    {
        int d=strcmp(word,(*node)->val);
        if(d<0)
        {
            insert(&((*node)->left),word);
            if((*node)->left->rank > (*node)->rank)
                right_rotate(node);
        }
        else if(d>0)
        {
            insert(&((*node)->right),word);
            if((*node)->right->rank > (*node)->rank)
                left_rotate(node);
        }

    }
}
int ins(char *word)
{
    struct Node *p;
    p=root;
    while(p)
    {
        int result = strcmp(word, p->val);
        if (result < 0)
            p = p->left;
        else if (result > 0)
            p = p->right;
        else
        {
            p->freq++;
            return 0;
        }
    }
    insert(&root,word);
    return 1;
}

void dfs(struct Node *node)
{
    if(node==NULL)
        return;
    dfs(node->left);
    printf("%s %d\n", node->val,node->freq);
    dfs(node->right);
}

void dump()
{
    dfs(root);
}
char buf[512];
int getword()
{
    int ch=getchar();
    while(!isalpha(ch))
    {
        if(ch==EOF)
            return false;
        ch=getchar();
    }
    int p=0;
    while(isalpha(ch))
    {
        buf[p++]=tolower(ch);
        ch=getchar();
    }
    buf[p]=0;
    return true;
}

int main()
{
    freopen("article.txt","r",stdin);
    while(getword())
    {
        ins(buf);
    }
#if 0
    while(getword())
    {
        printf("$$%s$$\n",buf);
    }
#endif // 0
    dump();
    return 0;
}
