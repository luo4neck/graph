#include<stdio.h>
#include<stdlib.h>

void free_graph(int **p, int vecnum)
{
int i;
for(i=0; i<vecnum; i++)
    {
    free(p[i]);
 //   printf("fuck %d\n", i);
    }
//printf("fuck all\n");
free(p);
//printf("fuck all\n");
}


int main(int argc, char *argv[])
{
if(argc>2)
    {printf("Please input only file name!\n");}

FILE *fp;
char c;
int i=0, j=0, vecnum = 0;

if((fp = fopen(argv[1], "rb")) == NULL)
    {
    printf("Please input a right file name!\n");
    exit(0);
    }

while(!feof(fp))
    {
    c = getc(fp);
    if ( c==10 )  vecnum++;
    }
//printf("%d\n",vecnum);

int **p;
p=(int **)malloc(vecnum*sizeof(int *));
for(i=0; i<vecnum; i++)
    { 
    p[i] = (int *)malloc(sizeof(int)*vecnum); 
    for(j=0; j<vecnum; j++)
        {
        p[i][j] = -1;
    //    printf("%d, ", p[i][j]);
        }
  //  printf("\n");
    }

//printf("fuck all\n");
fp = fopen(argv[1], "rb");
i=j=0;
while(!feof(fp))
    {
    c = getc(fp);
    if( c>47 && c<58)
        {
        p[i][j] = c-48;
  //  printf("%d, ", p[i][j]);
        j++;
        }
    if ( c==10 ) 
        {
        i++;
        j=0;
 //       printf("\n");
        }// vecnum++;
    }
free(fp);

for(i=0; i<vecnum; i++)
    {
    j=0;
    while( p[i][j] >= 0 )
        {

    printf("%d, ", p[i][j]);
        j++;
        }
        printf("\n");
    }



//printf("fuck all\n");
free_graph(p, vecnum);
return 0;
}
