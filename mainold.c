#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define BOUND 10

int totalpoint;

typedef struct{
int x;
int y;
}Point2D;

int * getArea(Point2D *ptr,int len,int leftEdge,int bottomEdge)
{
	int *area=(int*)malloc(totalpoint * sizeof(int));
	int i=0;
	int ar=0;

	for(i=0;i<totalpoint;i++)
	{
		if((ptr[i].x+1-leftEdge) > (ptr[i].y+1-bottomEdge))
		{
			ar=(int)(ptr[i].x+1-leftEdge)*((ptr[i].x+1-leftEdge));
		}
		else
		{
			ar=(int)(ptr[i].y+1-bottomEdge)*((ptr[i].y+1-bottomEdge));
		}
		area[i]=ar;
	}
	return area;
}

Point2D* getAboveRightPoints(int startx,int starty,Point2D* ptrx,Point2D* ptry,int len)
{
	int k=0;
	int i,j;
	int count=0;
	Point2D* temp;
	printf("Inside Function");
	//find the value of points common in sortedX and sortedY array
	for(i=startx;i<len;i++)
	{
		for(j=starty;j<len;j++)
		{	
			if(ptrx[i].x==ptry[j].x && ptrx[i].y==ptry[j].y)
			{
				ptry[j].x=100;
				ptry[j].y=100;
				count++;
			}	
		}	
	}
	//allocate memory for all uncommon points
	totalpoint=(len-startx)+(len-starty)-count;
	printf("\n Value- %d",totalpoint);

	temp=(Point2D*)malloc(totalpoint*sizeof(Point2D));
	for(i=startx;i<len;i++)
	{
		temp[k].x=ptrx[i].x;
		temp[k].y=ptrx[i].y;
		k++;
	}
	for(j=starty;j<len;j++)
	{
		if(ptry[j].x!=100 && ptry[j].y!=100)
		{
			temp[k].x=ptry[j].x;
			temp[k].y=ptry[j].y;
			k++;
		}
	}
	
	return temp;
}
void getRandomInputPoints(int n,Point2D * ptr)
{
	int i=0;
	int halfBound=BOUND/2;
	int pointx=0,pointy=0;
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
                if(pointy>=halfBound)
                        ptr->y=pointy%halfBound;
                else
                        ptr->y=(-1)*(pointy%halfBound);

		ptr++;
	}
}
void sortedArea(int* area)
{
	int i,j,temp;
	for(i=0;i<totalpoint;i++)
	{
		for(j=0;j<totalpoint-i-1;j++)
		{
			if(area[j+1]>area[j])
			{
				temp=area[j+1];
				area[j+1]=area[j];
				area[j]=temp;
			}
		}
	}
}
Point2D* sortArray(int x,Point2D *ptr,int n)
{
	int i,j;
	Point2D temp;
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
							temp.x=sorted[j].x;
							temp.y=sorted[j].y;
							sorted[j].x=sorted[i].x;
							sorted[j].y=sorted[i].y;
							sorted[i].x=temp.x;
							sorted[i].y=temp.y;
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
                                                        temp.x=sorted[j].x;
                                                        temp.y=sorted[j].y;
                                                        sorted[j].x=sorted[i].x;
                                                        sorted[j].y=sorted[i].y;
                                                        sorted[i].x=temp.x;
                                                        sorted[i].y=temp.y;
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
	Point2D corner;
	Point2D *Rpoints=NULL;
	Point2D leftPoint;
	int *area;
	int currentArea=0;
	int minArea=INT_MAX;
	Point2D bottomPoint;
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

	for(i=0;i<n;i++)
		printf("\t%d %d,",points[i].x,points[i].y);
	//for(i=0;i<n;i++)
                //printf("\t%d %d,",sortedY[i].x,sortedY[i].y);

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

			Rpoints=getAboveRightPoints(i,j,sortedX,sortedY,n);
			if(totalpoint<k)
				continue;	
			area=getArea(Rpoints,n,leftEdge,bottomEdge);
			sortedArea(area);
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

	free(points);
return 0;
}
