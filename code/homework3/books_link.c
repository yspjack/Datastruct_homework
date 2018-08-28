#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Book
{
    char name[55];
    char author[25];
    char press[35];
    char date[15];
    struct Book *next;
};
struct Book *vhead;
int ins(FILE *fin)
{
    struct Book *p,*q,*tmp;
    tmp=malloc(sizeof(struct Book));
    if(fscanf(fin,"%s%s%s%s",tmp->name,tmp->author,tmp->press,tmp->date)!=4)
    {
        free(tmp);
        return 0;
    }
    tmp->next=NULL;
    if(vhead->next==NULL)
    {
        vhead->next=tmp;
        return 1;
    }
    p=vhead;
    q=vhead->next;
    while(q)
    {
        if(strcmp(q->name,tmp->name)>0)
            break;
        p=q;
        q=q->next;
    }
    tmp->next=q;
    p->next=tmp;
    return 1;
}

void query()
{
    char key[1024];
    scanf("%s",key);
    struct Book *p,*head=vhead->next;
    for(p=head; p; p=p->next)
    {
        if(strstr(p->name,key)==NULL)
            continue;
        printf("%-50s%-20s%-30s%-10s\n",p->name,p->author,p->press,p->date);
    }
}
void del()
{
    char key[1024];
    scanf("%s",key);
    {
        struct Book *p=vhead,*q=vhead->next;
        while(q)
        {
            if(strstr(q->name,key)!=NULL)
            {
                p->next=q->next;
                struct Book *tmp=q;
                //free(q);
                q=p->next;
                free(tmp);
                //break;
            }
            else
            {
                p=q;
                q=q->next;
            }
        }


    }
}
int main()
{
    int cnt=0;
    vhead=malloc(sizeof(struct Book));
    vhead->next=NULL;
    FILE *f=fopen("books.txt","r");
    while(ins(f))
    {
        ++cnt;
    }
    //printf("%d\n",cnt);
    fclose(f);
    int op;
    while(scanf("%d",&op)==1)
    {
        if(op==0)
            break;
        if(op==1)
            ins(stdin);
        else if(op==2)
            query();
        else if(op==3)
        {
            del();
        }
    }
    do
    {
        f=fopen("ordered.txt","w");
        struct Book *p;
        for(p=vhead->next; p; p=p->next)
        {
            fprintf(f,"%-50s%-20s%-30s%-10s\n",p->name,p->author,p->press,p->date);
        }
        fclose(f);
    }
    while(0);
    return 0;
}
