#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

void Wides(int **p, int *visited, int *dis, int k, int distance, int vecnum)
{//recursive function to traverse the graph..
int j=1, w=0, *wide;
wide = (int *)malloc(sizeof(int) * (vecnum));

while(p[k][j] >= 0)// unused **p positions are set to -1..
    {// visit all the neighbours of node k..
    if( visited[ p[k][j] ] == FALSE ) // if not visited, mark it and into it later.. 
        {
        visited[ p[k][j] ] = TRUE;
//        printf("node %d visited\n", p[k][j]);
        dis[distance]++;
        wide[w] = p[k][j];
        w++;
        }
    j++;
    }

if(w>=1)
    {
    int i;
    for(i=0; i<w; i++)
        {
  //      printf("into node %d\n", wide[i]);
        Wides(p, visited, dis, wide[i], distance+1, vecnum);
        }
    }
free(wide);
}

void Disprint(int *dis, int Sub, int vecnum)
{
printf("Number of connected sub-graphs: %d\n", Sub);
printf("Distance | Number of node-pairs\n");
int i;
for(i=0; i<vecnum-1; i++)
    {
    if(dis[i] > 0)
    printf("%d          %d \n" ,i+1, dis[i]/2); 
    }
}

int Sum(int *v)
{
int i=0,s=0;
while(v[i]!=NULL)
    {
    s= s+ v[i];
    i++;
    }
return s;
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
int i=0, k=0, j=0, vecnum = 0;

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

int **p, *visited, *dis, *sub;
p=(int **)malloc(vecnum*sizeof(int *));//p store all the values from the reading file
visited = (int *)malloc(sizeof(int) * vecnum);// store if a node had been visited, used in each loop and recursive..
dis = (int *)malloc(sizeof(int) * (vecnum-1));// store distance information between nodes..
sub = (int *)malloc(sizeof(int) * vecnum);// store how many sub graph inside the code..

for(i=0; i<vecnum; i++)
    { 
    visited[i] = FALSE;
    sub[i] = FALSE;
    if(i>0) { dis[i-1] = 0; }

    p[i] = (int *)malloc(sizeof(int)*vecnum); 
    for(j=0; j<vecnum; j++)// set **p to -1
        {
        p[i][j] = -1;
        }
    }

i=j=0;
printf("Data in '%s':\n", argv[1]);
fp = fopen(argv[1], "rb");
while(!feof(fp))// read and print the data in the file..
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
printf("\n");

/*============ begin search how many sub-graphs there is =============*/

int distance, Sub=1;

while(Sum(sub) < vecnum)
    {
    for(i=0; i<vecnum; i++)
        { if(sub[i] == FALSE) k=i; }
    
    if(Sum(sub)== 0) k=0;// always into the loop from 0..
    
    for(i=0; i<vecnum; i++)// set all nodes as non-visited..
        { visited[i] = FALSE; }
    
    visited[k] = TRUE;
    sub[k] = TRUE;
    distance = 0;
    Wides(p, visited, dis, k, distance, vecnum);
  
    for(i=1; i<vecnum; i++)
        {
        if( visited[i] == TRUE)
            sub[i] = TRUE;
        }

    //printf("%d, \n", Sum(visited) );
    //printf("%d, \n", Sum(sub) );
    
    if(Sum(sub) < vecnum)// if not all nodes are visited.. this is a sub-graph.. visit all the nodes inside the sub-graph..
        {
        for(i=0; i<vecnum; i++)
            {
            if (sub[i] == TRUE && i!=k) 
                {
                for(j=0; j<vecnum; j++)// set all nodes as non-visited
                    { visited[j] = FALSE; }
                visited[i] = TRUE;
                Wides(p, visited, dis, i, distance, vecnum);
                }
            }
        }
    else // all the nodes are visited.. no sub-graph..
        {
        for(i=0; i<vecnum; i++)
            {
            if(k!=i) 
                {
                for(j=0; j<vecnum; j++)// set all nodes as non-visited
                    { visited[j] = FALSE; }
                visited[i] = TRUE;
                Wides(p, visited, dis, i, distance, vecnum);
                }
            }
        }

    Disprint(dis, Sub, vecnum);
    Sub++;
    }
/*============ data have stored in **p graph part begin here =========*/

free_graph(p, vecnum);
free(visited);
free(dis);
free(sub);
return 0;
}
