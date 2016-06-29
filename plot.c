#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#define NUM_POINTS 100
#define NUM_COMMANDS 3
struct point
{
	int x,y,col;
}points[NUM_POINTS];
int main()
{
	int i,j,temp1,min_dist=9999999,max_dist=0;
	int min1,min2,max1,max2;
	char * commandsForGnuplot[] = {"set title \"Nearest and farthest points\"","set palette model RGB defined (0 \"red\",1 \"black\",2 \"green\")", "plot 'data.temp' using 1:2:3 notitle with points pt 2 palette"};
	int col[NUM_POINTS];
    	FILE * temp = fopen("data.temp", "w");
//	srand(time(NULL));
	for(i=0;i<NUM_POINTS;i++)
	{
		points[i].x=rand()%1000;
		points[i].y=rand()%1000;
		points[i].col=1;
	}
	
	for(i=0;i<NUM_POINTS-1;i++)
	{
		for(j=i+1;j<NUM_POINTS;j++)
		{
			if((temp1=sqrt(pow(points[i].x-points[j].x,2)+pow(points[i].y-points[j].y,2)))<min_dist)
			{
				min_dist=temp1;
				min1=i;
				min2=j;
			}
			if((temp1=sqrt(pow(points[i].x-points[j].x,2)+pow(points[i].y-points[j].y,2)))>max_dist)
			{
				max_dist=temp1;
				max1=i;
				max2=j;
			}

		}
	}
	points[min1].col=points[min2].col=2;
	points[max1].col=points[max2].col=0;
	printf("%d %d   %d %d  %d\n",points[min1].x,points[min1].y,points[min2].x,points[min2].y,min_dist);
	printf("%d %d   %d %d  %d\n",points[max1].x,points[max1].y,points[max2].x,points[max2].y,max_dist);
    	/*Opens an interface that one can use to send commands as if they were typing into the
     	*     gnuplot command line.  "The -persistent" keeps the plot open even after your
     	*     C program terminates.
     	*/
    	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    	for (i=0; i < NUM_POINTS; i++)
    	{
   		 fprintf(temp, "%d %d %d\n", points[i].x,points[i].y,points[i].col); //Write the data to a temporary file
    	}

    	for (i=0; i < NUM_COMMANDS; i++)
    	{
    		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    	}
    	return 0;
}
