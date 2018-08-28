#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct user
{
    char name[16];
    char tele[16];
} user;
user dat[55];
int n;
int cmp(const void *a_,const void *b_)
{
    user *a=(user*)a_,*b=(user*)b_;
    return strcmp(a->name,b->name);
}
char buf[1024];
int main()
{
    int i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",buf);
        memcpy(dat[i].name,buf,10);
        dat[i].name[10]='\0';
        scanf("%s",buf);
        memcpy(dat[i].tele,buf,10);
        dat[i].tele[10]='\0';
    }
    qsort(dat,n,sizeof(user),cmp);
    for(i=0;i<n;i++)
    {
        printf("%12s%12s\n",dat[i].name,dat[i].tele);
    }
    return 0;
}


