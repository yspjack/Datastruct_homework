#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char prekey[64];
int strip(char *str)
{
    int i=strlen(str);
    while(i>=0)
    {
        if(isspace(str[i]))
        {
            str[i]='\0';
        }
        else
            return i;
        i--;
    }
    return 0;
}
int vis[256];
char code1[256];
char code2[256];
int next[256];
int prev[256];

void get_code()
{
    int i;
    int len=strlen(code1);
    for(i=0; i<len-1; i++)
    {
        next[i]=i+1;
        prev[i+1]=i;
    }
    prev[0]=len-1;
    next[len-1]=0;
    int last=len;
    int v=0;
    while(last--)
    {
        int step=code1[v];
        char tmp=code1[v];
        //printf("%d\n",step);
        //del
        next[prev[v]]=next[v];
        prev[next[v]]=prev[v];
        //disp
        if(v==next[v])
        {
            //剩下的最后一个字符的密文为原密钥的第一个字符
            code2[(int)tmp]=code1[0];
            break;
        }
        while(step--)
        {
            v=next[v];
        }
        code2[(int)tmp]=code1[v];
#ifdef DEBUG
        printf("%c->%c\n",(char)tmp,code1[v]);
#endif // DEBUG
    }
#ifdef DEBUG
    for(i=32; i<=126; i++)
    {
        printf("%c",i);
    }
    printf("\n");
    for(i=32; i<=126; i++)
    {
        printf("%c",code2[i]);
    }
    printf("\n");
#endif
}

int main()
{
    FILE *fin,*fout;
    fin=fopen("in.txt","r");
    fout=fopen("in_crpyt.txt","w");

    fgets(prekey,64,stdin);
    //fputs(prekey,fout);
    int len1=strip(prekey);
    int i,j;
    memset(vis,0,sizeof(vis));
    for(i=0,j=0; i<len1; i++)
    {
        if(prekey[i]>=32 && prekey[i]<=126)
        {
            if(!vis[(int)prekey[i]])
            {
                vis[(int)prekey[i]]=1;
                code1[j++]=prekey[i];
            }
        }
    }
    for(i=32; i<=126; i++)
        if(!vis[i])
            code1[j++]=i;
    code1[j]=0;
#ifdef DEBUG
    puts(code1);
#endif // DEBUG
    get_code();
    int ch;
    while((ch=fgetc(fin))!=EOF)
    {
        if(ch>=32 && ch<=126)
        {
            fputc(code2[ch],fout);
        }
        else
            fputc(ch,fout);
    }

    return 0;
}
