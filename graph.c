#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

void Wides(int **p, int *visited, int *dis, int k, int distance, int vecnum)
{//recursive function to traverse the graph..
int j=1, w=0, *wide;
wide = (int *)malloc(sizeof(int) * (vecnum));

while(p[k][j] >= 0)
    {
    //if( visited[ p[k][j] ] == FALSE && p[k][j]>k )
    if( visited[ p[k][j] ] == FALSE )
        {
        visited[ p[k][j] ] = TRUE;
        printf("node %d visited\n", p[k][j]);
        dis[distance]++;
//printf("%d %d %d here?\n",w,k,j);
        wide[w] = p[k][j];
 //   printf("%d %d %d here?\n",w,k,j);
        w++;
        }
    j++;
    }

if(w>=1)
    {
    int i;
    for(i=0; i<w; i++)
        {
        printf("into node %d\n", wide[i]);
        Wides(p, visited, dis, wide[i], distance+1, vecnum);
        }
    }
free(wide);
}

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
int i=0, k=0, j=0, vecnum = 0, Sub=0;

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

int **p, *visited, *dis;
p=(int **)malloc(vecnum*sizeof(int *));
visited = (int *)malloc(sizeof(int) * vecnum);
dis = (int *)malloc(sizeof(int) * (vecnum-1));
for(i=0; i<vecnum; i++)
    { 
    visited[i] = 0;
    if(i>0) { dis[i-1] = 0; }

    p[i] = (int *)malloc(sizeof(int)*vecnum); 
    for(j=0; j<vecnum; j++)
        {
        p[i][j] = -1;
        }
    }

fp = fopen(argv[1], "rb");
i=j=0;
while(!feof(fp))
    {
    c = getc(fp);
    if( c>47 && c<58)
        {
        p[i][j] = c-48;
        printf("%d, ", p[i][j]);
        j++;
        }
    if ( c==10 ) 
        {
        i++;
        j=0;
        printf("\n");
        }
    }
free(fp);

/*============ begin search how many sub-graphs there is =============*/

int distance;
for(k=0; k<vecnum; k++) //loop for 7 nodes
    {
    printf("\nin loop %d !!!!!!!!!\n",k);
    for(i=0; i<vecnum; i++)
        { visited[i] = FALSE; }
    visited[k] = TRUE;
    distance = 1;
    Wides(p, visited, dis, k, distance, vecnum);
    }

/*============ data have stored in **p graph part begin here =========*/


    printf("here well why there is a segmentation fault\n");
free_graph(p, vecnum);
free(visited);
//system("rm graph.o"); 
return 0;
}
