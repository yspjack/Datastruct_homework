#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int head;
struct Book
{
    char name[55];
    char author[25];
    char press[35];
    char date[15];
    int del;
};
struct Book books[505];
int cnt=0;
void ins()
{
    scanf("%s%s%s%s",books[cnt].name,books[cnt].author,books[cnt].press,books[cnt].date);
    books[cnt].del=0;
    ++cnt;
}
int cmp(const void *a,const void *b)
{
    //fprintf(stderr,"#%s#%s#\n",((struct Book*)a)->name,((struct Book*)b)->name);
    return strcmp(((struct Book*)a)->name,((struct Book*)b)->name);
}
void query()
{
    char key[1024];
    scanf("%s",key);
    qsort(books,cnt,sizeof(struct Book),cmp);
    int i;
    for(i=0; i<cnt; i++)
    {
        if(books[i].del)
        {
            continue;
        }
        if(strstr(books[i].name,key)==NULL)
            continue;
        printf("%-50s%-20s%-30s%-10s\n",books[i].name,books[i].author,books[i].press,books[i].date);
    }
}
int main()
{
    FILE *f=fopen("books.txt","r");
    cnt=0;
    while(fscanf(f,"%s%s%s%s",books[cnt].name,books[cnt].author,books[cnt].press,books[cnt].date)==4)
    {
        books[cnt].del=0;
        cnt++;
    }
    fclose(f);
    int op;
    while(scanf("%d",&op)==1)
    {
        if(op==0)
            break;
        if(op==1)
            ins();
        else if(op==2)
            query();
        else if(op==3)
        {
            char key[1024];
            scanf("%s",key);
            qsort(books,cnt,sizeof(struct Book),cmp);
            int i;
            for(i=0; i<cnt; i++)
            {
                if(books[i].del)
                {
                    continue;
                }
                if(strstr(books[i].name,key)==NULL)
                    continue;
                books[i].del=1;
            }
        }
    }
    do
    {
        fopen("ordered.txt","w");
        qsort(books,cnt,sizeof(struct Book),cmp);
        int i;
        for(i=0; i<cnt; i++)
        {
            if(books[i].del)
            {
                continue;
            }

            fprintf(f,"%-50s%-20s%-30s%-10s\n",books[i].name,books[i].author,books[i].press,books[i].date);
            //fprintf(f,"$%s$%s$%s$%s$\n",books[i].name,books[i].author,books[i].press,books[i].date);
        }
        fclose(f);
    }
    while(0);
    return 0;
}
