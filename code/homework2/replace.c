#include <stdio.h>
#include <ctype.h>
#include <string.h>
char in[128],out[128];
char buf[1024];
int main()
{
    FILE *fin,*fout;
    fin=fopen("filein.txt","r");
    fout=fopen("fileout.txt","w");
    scanf("%s%s",in,out);
    int l1,l2;
    l1=strlen(in);
    l2=strlen(out);
    while(fgets(buf,1024,fin))
    {
        int n=strlen(buf);
        int i=0;
        while(i<n)
        {
            int ok=0;
            if(tolower(buf[i])==tolower(in[0]))
            {
                int j=0;
                ok=1;
                while(j<l1)
                {
                    if(i>=n)
                    {
                        ok=0;
                        break;
                    }
                    if(tolower(buf[i+j])!=tolower(in[j]))
                    {
                        ok=0;
                        break;
                    }
                    j++;
                }
                if(ok)
                {
                    i+=j;
                    fprintf(fout,"%s",out);
                }
            }
            fprintf(fout,"%c",buf[i]);
            i++;
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

