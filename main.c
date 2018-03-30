#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define BOUND 20


typedef struct{
int x;
int y;
}Point2D;

void getRandomInputPoints(int n,Point2D * ptr)
{
	int i=0;
	int halfBound=BOUND/2;
	int pointx=0,pointy=0;
	int minArea=INT_MAX;
	for(i=0;i<n;i++)
	{	
		//getting x-coordinate value
		int pointx=rand()%BOUND;
		if(pointx>=halfBound)
			ptr->x=pointx%halfBound;
		else
			ptr->x=(-1)*(pointx%halfBound);

		//getting y-coordinate value
                int pointy=rand()%BOUND;
                if(pointx>=halfBound)
                        ptr->y=pointy%halfBound;
                else
                        ptr->y=(-1)*(pointy%halfBound);

		ptr++;
	}
}

Point2D* sortArray(int x,Point2D *ptr,int n)
{
	int i,j,temp=0;
	Point2D* sorted=(Point2D*)malloc(n*sizeof(Point2D));
	for(i=0;i<n;i++)
	{
		 sorted[i].x=ptr[i].x;
		sorted[i].y=ptr[i].y;
	}
	//sort by x co-ordinate
	if(x==1)
	{	
		for(i=0;i<n;i++)
			{
			for(j=0;j<n;j++)
				{
					if(sorted[j].x>sorted[i].x)
						{
							temp=sorted[j].x;
							sorted[j].x=sorted[i].x;
							sorted[i].x=temp;
						}
					}
				}		
	}
	else
	{
                for(i=0;i<n;i++)
                        {
                        for(j=0;j<n;j++)
                                {
                                        if(sorted[j].y>sorted[i].y)
                                                {
                                                        temp=sorted[j].y;
                                                        sorted[j].y=sorted[i].y;
                                                        sorted[i].y=temp;
                                                }
                                        }
                                }
        }
	return sorted; 
}			

int main()
{
	int n=0,k=0;
	int i=0,j=0;
	Point2D *sortedX;
	Point2D *sortedY;
	Point2D *corner=null;
	Point2D leftPoint=null;
	Point2D bottomPoint=null;
	printf("\nEnter Number of Points in plane(n):");
	fflush(stdin);
	scanf("%d",&n);
	printf("\nEnter number of points inside square(k):");
	fflush(stdin);
	scanf("%d",&k);
	Point2D *points=(Point2D*)malloc(n*sizeof(Point2D));	
	getRandomInputPoints(n,points);
	sortedX=sortArray(1,points,n);
	sortedY=sortArray(0,points,n);
	for(i=0;i<n-k+1;++i)
	{
		for(j=0;j<n-k+1;++j)
		{
			
			leftPoint=sortedX[i];
			bottomPoint=sorted[j];
			if(leftPoint.x > bottomPoint.x || leftPoint.y < bottomPoint.y)
				continue;
						




		
		}
	}
	

	free(points);
return 0;
}
