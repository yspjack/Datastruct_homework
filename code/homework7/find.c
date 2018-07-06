#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

FILE *fin;
char word[25];
int op;
char dict[3600][25];
int dict_sz=0;

int head[3600],next[3600];
/* compute hash value for string */
#define NHASH  3001
#define MULT  37
unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p;
    for(p=str; *p!='\0'; p++)
        h = MULT*h + *p;
    return h % NHASH;
}

int range[26];

int main()
{
    fin=fopen("dictionary3000.txt","r");
    memset(head,-1,sizeof(head));
    while(fgets(dict[dict_sz],25,fin))
    {
        int j;
        int len=strlen(dict[dict_sz]);
        for(j=len-1;j>=0;j--)
        {
            if(isspace(dict[dict_sz][j]))
                dict[dict_sz][j]='\0';
            else
                break;
        }
        if(dict[dict_sz][0]=='\0')
            continue;
        //task 3
        range[dict[dict_sz][0]-'a']=dict_sz;
        //hash
        int h=hash(dict[dict_sz]);
        next[dict_sz]=head[h];
        head[h]=dict_sz;
        dict_sz++;
    }

    //printf("%d %d\n",range[0],range[1]);

    scanf("%s",word);
    scanf("%d",&op);
    int cnt=0;
    int result=0;
    if(op==1)
    {
        int i;
        for(i=0;i<dict_sz;i++)
        {
            int cmp=strcmp(word,dict[i]);
            ++cnt;
            if(cmp==0)
            {
                result=1;
                break;
            }
            else if(cmp<0)
            {
                result=0;
                break;
            }
        }
        goto print_ans;
    }
    else if(op==2)
    {
        int left=0,right=dict_sz-1;
        while(left<=right)
        {
            int mid=(left+right)/2;
            ++cnt;
            int c=strcmp(dict[mid],word);
            //puts(dict[mid]);
            if(c==0)
            {
                result=1;
                goto print_ans;
            }
            if(c>0)
            {
                right=mid-1;
            }
            else
            {
                left=mid+1;
            }
        }
    }
    else if(op==3)
    {
        int from,to;
        if(word[0]=='a')
        {
            from=0;
            to=range[0];
        }
        else
        {
            from=range[word[0]-'a'-1]+1;
            to=range[word[0]-'a'];
        }

        int left=from,right=to;
        while(left<=right)
        {
            int mid=(left+right)/2;
            ++cnt;
            int c=strcmp(dict[mid],word);
            //puts(dict[mid]);
            if(c==0)
            {
                result=1;
                goto print_ans;
            }
            if(c>0)
            {
                right=mid-1;
            }
            else
            {
                left=mid+1;
            }

        }

    }
    else if(op==4)
    {
        int h=hash(word);
        int u=head[h];
        while(u!=-1)
        {
            ++cnt;
            if(strcmp(dict[u],word)==0)
            {
                result=1;
                goto print_ans;
            }
            u=next[u];
        }
    }
print_ans:
    printf("%d %d\n",result,cnt);
    return 0;

}
