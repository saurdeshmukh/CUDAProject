#include<stdio.h>
#include<stdlib.h>
#include"randomPoints.h"


void printArray(Point2D*ptr,int n)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		printf("Point %d - X: %d , Y: %d\n",i+1,ptr[i].x,ptr[i].y);

	}

}

int main()
{
int n=0,k=0;
int i=0,j=0;
Point2D *sortedX,*sortedY;
Point2D bottomPoint;
Point2D corner;
Point2D leftPoint;
Point2D *Rpoints=NULL;
int *area;
int currentArea=0;
int minArea=INT_MAX;
int totalpoints=0;

printf("\nEnter Number of Points in plane(n):");
fflush(stdin);
scanf("%d",&n);
printf("\nEnter Number of Points insie square(k):");
fflush(stdin);
scanf("%d",&k);
Point2D * points=(Point2D *)malloc(n*sizeof(Point2D));
//getRandomInputPoints(n,points);

points[0].x=0;
points[0].y=3;
points[1].x=2;
points[1].y=3;
points[2].x=4;
points[2].y=4;
points[3].x=4;
points[3].y=1;

printf("\nPoints:\n");
printArray(points,n);

sortedX=sortArray(1,points,n); 
sortedY=sortArray(0,points,n);

printf("\nSorted by X:\n");
printArray(sortedX,n);

printf("\nSorted by Y:\n");
printArray(sortedY,n);
                                                                          
for(i=0;i<n-k+1;++i)
	{
		for(j=0;j<n-k+1;++j)
                {

                        leftPoint=sortedX[i];
                        bottomPoint=sortedY[j];
                        if(leftPoint.x > bottomPoint.x || leftPoint.y < bottomPoint.y)
                                continue;

                        int leftEdge=(int)(leftPoint.x-1);
                        int bottomEdge=(int)(bottomPoint.y-1);

                        Rpoints=getAboveRightPoints(i,j,sortedX,sortedY,n,&totalpoints);
                        if(totalpoints<k)
                                continue;
                        area=getArea(Rpoints,n,leftEdge,bottomEdge,&totalpoints);
                        sortedArea(area,&totalpoints);
                        currentArea=area[k-1];
                        if(minArea>currentArea)
                        {
                                minArea=currentArea;
                                corner.x=leftEdge;
                                corner.y=bottomEdge;
                        }


                }
        }

        printf("\nMinimum Area:%d",minArea);


return 0;
}

