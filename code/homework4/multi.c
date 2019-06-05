#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define true 1
#define false 0
#define bool int
//#define DEBUG 1
//#define int long long
struct Node
{
    long long a;
    long long n;
    struct Node *next;
};
typedef struct Node Node;

void ins(Node **phead,long long a,long long n)
{
    Node *tmp=(Node*)malloc(sizeof(Node));
    tmp->a=a;
    tmp->n=n;
    tmp->next=NULL;
    if(*phead==NULL)
    {
        (*phead)=tmp;
        return;
    }
    if((*phead)->n<tmp->n)
    {
        tmp->next=(*phead);
        (*phead)=tmp;
        return;
    }
    if((*phead)->n == tmp->n)
    {
        (*phead)->a += a;
        free(tmp);
        return;
    }
    Node *p,*q;
    p=(*phead);
    q=(*phead)->next;
    while(q)
    {
        if(p->n==n)
        {
            p->a+=a;
            free(tmp);
            return;
        }
        if(q->n==n)
        {
            q->a+=a;
            free(tmp);
            return;
        }
        if(q->n<tmp->n)
        {
            break;
        }
        p=q;
        q=q->next;
    }
    p->next=tmp;
    tmp->next=q;
}

char buf[100000];
int i=0;
long long fastread()
{
    while(buf[i]!='\0' && !isdigit(buf[i]))
    {
        i++;
    }
    long long x=0;
    while(buf[i]!='\0' && isdigit(buf[i]))
    {
        x=x*10+buf[i]-'0';
        i++;
    }
    return x;
}
void read_poly(Node **phead)
{
    long long a,n;
    fgets(buf,100000,stdin);
    int len=strlen(buf);
    i=0;
    while(i<len)
    {
        a=fastread();
        n=fastread();
        if(a==0)
            continue;
        ins(phead,a,n);
    }
}
void printlist(Node *head)
{
    Node *u;
    for(u=head;u;u=u->next)
    {
        printf("a=%d,n=%d\n",u->a,u->n);
    }
}
void calc(Node *head1,Node *head2,Node **head3)
{
    *head3=NULL;
    Node *i,*j;
    for(i=head1;i!=NULL;i=i->next)
    {
        for(j=head2;j!=NULL;j=j->next)
        {
            ins(head3,(i->a)*(j->a),(i->n)+(j->n));
        }
    }

}

Node *head1=NULL,*head2=NULL,*head3=NULL;
int main()
{
#ifdef DEBUG
    freopen("multi.in","r",stdin);
#endif
    read_poly(&head1);
    //printlist(head1);
    read_poly(&head2);
    //printlist(head2);
    calc(head1,head2,&head3);
    Node *u;
    for(u=head3;u;u=u->next)
    {
        printf("%lld %lld ",u->a,u->n);
    }
    return 0;
}
