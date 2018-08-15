#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
    char val[20];
    int freq;
    struct Node *next;
};
typedef struct Node Node;
Node *head=NULL;
void ins(char *word)
{
    Node *u=head;
    while(u)
    {
        if(strcmp(u->val,word)==0)
        {
            u->freq++;
            return;
        }
        u=u->next;
    }

    Node *tmp=(Node*)malloc(sizeof(Node));
    strcpy(tmp->val,word);
    tmp->freq=1;
    tmp->next=NULL;

    if(head==NULL)
    {
        head=tmp;
        return;
    }
    if(strcmp(head->val,tmp->val)>0)
    {
        tmp->next=head;
        head=tmp;
        return;
    }
    Node *p,*q;
    p=head;
    q=head->next;
    while(q)
    {
        if(strcmp(q->val,tmp->val)>0)
        {
            break;
        }
        p=q;
        q=q->next;
    }
    tmp->next=q;
    p->next=tmp;

}

void dumplist()
{
    Node *u=head;
    while(u)
    {
        printf("%s %d\n",u->val,u->freq);
        u=u->next;
    }
}

char buf[512];
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
    dumplist();
    return 0;
}
