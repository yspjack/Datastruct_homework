#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char key[1005];
int vis[26];
char buf[1005];
//read key,return length of key
int readkey()
{
    memset(vis,0,sizeof(vis));
    scanf("%s",buf);
    int n=strlen(buf);
    int i,j=0;
    for(i=0;i<n;++i)
    {
        int ch=buf[i]-'a';
        if(!vis[ch])
        {
            key[j++]=buf[i];
            vis[ch]=1;
        }
    }
    for(i=25;i>=0;--i)
    {
        if(!vis[i])
            key[j++]='a'+i;
    }
    key[j]=0;
    return j;
}

int main()
{
    FILE *fin,*fout;
    fin=fopen("encrypt.txt","r");
    fout=fopen("output.txt","w");
    readkey();
    //puts(key);
    int ch;
    while((ch=fgetc(fin))!=EOF)
    {
        if(isalpha(ch))
        {
            fputc(key[ch-'a'],fout);
        }
        else
            fputc(ch,fout);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
