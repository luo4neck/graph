#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
FILE *fp;
char c;
int i=0, j=0,k=0, vecnum = 0, v=0, link[], start[];


if(argc>2)
    {printf("Please input only file name!\n");}

if((fp = fopen(argv[1], "rb")) == NULL)
    {
    printf("Please input a right file name!\n");
    exit(0);
    }

while(!feof(fp))
    {
    c = getc(fp);
    if(c>47 && c<58)
       {
       link[i] = c-48;
       j++;
       }
    else if(c ==10)
       {
       start[k]=j;
       k++;
       j=0;
       }
    }

printf("%d\n", k);

return 0;
}
