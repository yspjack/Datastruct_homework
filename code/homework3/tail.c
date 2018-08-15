#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char cmd[128];
char args[5][128];
char line[1024][1024];
int main(int argc,char** args)
{
    int i;
    char filename[128];
    int li=10;
    if(argc>=2)
    {
        sscanf(args[1],"%d",&li);
        li=-li;
        strcpy(filename,args[2]);
        //fprintf(stderr,"%d\n",li);
    }
    else
    {
        strcpy(filename,args[1]);
    }
    FILE *F=fopen(filename,"r");
    if(F==NULL)
    {
        //fputs("err",stderr);
        printf("%s\n",args[1]);
        return 0;
    }
    int p=0;
    while(fgets(line[p],1024,F))
    {
        p++;
    }
    for(i=li;i>0;i--)
        printf(line[p-i]);
    fclose(F);
    return 0;
}
