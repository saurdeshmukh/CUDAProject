#include<stdio.h>
#include<stdlib.h>
#include"randomPoints.h"


void printArray(Point2D*ptr,int n)
{
    int i=0;
    for(i=0;i<n;i++)
    {
//        printf("Point %d - X: %d , Y: %d\n",i+1,ptr[i].x,ptr[i].y);
        
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
   // getRandomInputPoints(n,points);
    
    points[0].x=5;
    points[0].y=8;
    points[1].x=7;
    points[1].y=3;
    points[2].x=4;
    points[2].y=4;
    points[3].x=4;
    points[3].y=6;
    points[4].x=8;
    points[4].y=8;
    points[5].x=9;
    points[5].y=3;
    points[6].x=7;
    points[6].y=3;
    points[7].x=2;
    points[7].y=4;
    points[8].x=2;
    points[8].y=2;
    points[9].x=6;
    points[9].y=9;
    points[10].x=6;
    points[10].y=2;
    points[11].x=0;
    points[11].y=9;
    points[12].x=4;
    points[12].y=9;
    points[13].x=8;
    points[13].y=3;
    points[14].x=7;
    points[14].y=2;
    points[15].x=5;
    points[15].y=4;
    points[16].x=0;
    points[16].y=6;
    points[17].x=3;
    points[17].y=5;
    points[18].x=9;
    points[18].y=0;
    points[19].x=5;
    points[19].y=4;
	
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
             //printf("\n i value-%d j Value-%d",i,j);
            // printf("\nLeftPoint x- %d y-%d",leftPoint.x,leftPoint.y);
            // printf("\nBottomPoint x-%d y-%d",bottomPoint.x,bottomPoint.y);
            // printf("\nLeft-%d bottom-%d\n",leftEdge,bottomEdge);
   	     Rpoints=getAboveRightPoints(i,j,sortedX,sortedY,n,&totalpoints);
	    // printf("\nTotal Points:%d\n",totalpoints);
            // printf("\nAbove Points:\n");
            printArray(Rpoints,totalpoints);
            
            if(totalpoints<k)
                continue;
            area=getArea(Rpoints,n,leftEdge,bottomEdge,&totalpoints);
            sortedArea(area,&totalpoints);
            currentArea=area[k-1];
           // printf("\nCurrentArea-%d",currentArea);

           if (i==4 &&j==5)
           {
             printf("\n i value-%d j Value-%d",i,j);
             printf("\nLeftPoint x- %d y-%d",leftPoint.x,leftPoint.y);
             printf("\nBottomPoint x-%d y-%d",bottomPoint.x,bottomPoint.y);
             printf("\nLeft-%d bottom-%d\n",leftEdge,bottomEdge);
             printf("\nTotal Points:%d\n",totalpoints);
             printf("\nAbove Points:\n");
	     for(int m=0;m<totalpoints;m++)
		printf("\n-%d %d",Rpoints[m].x,Rpoints[m].y);
	     for(int m=0;m<totalpoints;m++)
            	printf("\nCurrentArea-%d",area[m]);
           } 
	   if(minArea>currentArea)
            {
                minArea=currentArea;
                corner.x=leftEdge;
                corner.y=bottomEdge;
            }
            
            
        }
    }
    
    printf("\nMinimum Area:%d\n",minArea);
    
    
    return 0;
}
