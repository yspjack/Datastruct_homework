#include <stdio.h>
#include <string.h>
char str[1024];
char tmp[1024];
int main()
{
    int e=0;
    int l,p,r;
    int i;
    scanf("%s",str);
    for(i=0; str[i]; i++)
    {
        if(str[i]=='.')
        {
            p=i;
            break;
        }
    }
    if(p==1 && str[0]=='0')
    {
        i=0;
        int zeros=0;
        int cur=0;
        int n=strlen(str);
        for(i=0; i<n; i++)
        {
            if(str[i]=='.')
                continue;
            if(str[i]=='0')
                zeros++;
            else
            {
                break;
            }
        }
        for(;i<n;i++)
            tmp[cur++]=str[i];
        tmp[cur]=0;
        putchar(tmp[0]);
        if(cur>1)
        {
            putchar('.');
        }
        for(i=1; i<cur; i++)
            putchar(tmp[i]);
        e=zeros;

        printf("e%d\n",-e);
    }
    else
    {
        i=0;
        r=0;
        l=p;
        int cur=0;
        for(i=0; i<p; i++)
        {
            tmp[cur++]=str[i];
        }
        for(i=p+1; str[i]; i++)
        {
            r=i;
            tmp[cur++]=str[i];
        }
        tmp[cur]=0;
        putchar(tmp[0]);
        putchar('.');
        for(i=1; i<cur; i++)
            putchar(tmp[i]);
        e=p-1;
        printf("e%d\n",e);
    }
    return 0;
}
