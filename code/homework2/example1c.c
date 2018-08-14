#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char expr[4096];
int num[4096],top=0;
int op[4096],top2=0;

int isop(char ch)
{
    return ch=='+'||ch=='-'||ch=='*'||ch=='/';
}
void print_num()
{
    int i;
    for(i=0; i<top; i++)
    {
        printf("%d ",num[i]);
    }
}
void print_op()
{
    int i;
    for(i=0; i<top2; i++)
    {
        printf("%c ",op[i]);
    }
}
void process()
{
    char o=op[top2--];
    int b=num[top--];
    int a=num[top--];
    if(o=='+')
    {
        num[++top]=a+b;
    }
    else if(o=='-')
    {
        num[++top]=a-b;
    }
    else if(o=='*')
    {
        num[++top]=a*b;
    }
    else if(o=='/')
    {
        num[++top]=a/b;
    }
}
int main()
{
    fgets(expr,4096,stdin);
    int i=0,n=strlen(expr);
    while(i<n)
    {
        if(expr[i]<=' ')
        {
            ++i;
            continue;
        }
        if(expr[i]=='*'||expr[i]=='/')
        {
            while(top2 && (op[top2]=='/'||op[top2]=='*'))
            {
                process();
            }
            op[++top2]=expr[i];
        }
        else if(expr[i]=='+'||expr[i]=='-')
        {
            while(top2 && isop(op[top2]))
            {
                process();
            }
            op[++top2]=expr[i];
        }
        else if(expr[i]>='0' && expr[i]<='9')
        {
            int x=0;
            while(expr[i]>='0' && expr[i]<='9')
            {
                x=x*10+expr[i]-'0';
                i++;
            }
            num[++top]=x;
            continue;
        }
        else if(expr[i]=='=')
        {
            while(top2 && isop(op[top2]))
            {
                process();
            }
            break;
        }
        i++;
    }
    printf("%d\n",num[top]);
    return 0;
}


