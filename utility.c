#include<stdlib.h>
#include"utility.h"

///////////////////////////////////////////
///////BUBBLE SORT////////////////////////
//////////////////////////////////////////

void sortedArea(int *area,int *currentPoint)
{
	int totalpoint=*currentPoint;
	
	int i,j,temp;
	for(i=0;i<totalpoint-1;i++)
	{
		for(j=0;j<totalpoint-i-1;j++)
		{
			if(area[j]>area[j+1])
			{
				temp=area[j+1];
				area[j+1]=area[j];
				area[j]=temp;
			}
		}

	}
}



/////////////////////////////////////////////////////
///////////GET AREA ////////////////////////////////
////////////////////////////////////////////////////
int * getArea(Point2D *ptr,int len,int leftEdge,int bottomEdge,int *currentPoint)
{       
	int totalpoint=*currentPoint;
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




///////////////////////////////////////////////
//////////SORT W.R.T. ONE AXIS////////////////
//////////////////////////////////////////////
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
                for(i=0;i<n-1;i++)
                        {
                        for(j=0;j<n-i-1;j++)
                                {       
                                        if(sorted[j].x>sorted[j+1].x)
                                                {       
                                                        temp.x=sorted[j].x;
                                                        temp.y=sorted[j].y;
                                                        sorted[j].x=sorted[j+1].x;
                                                        sorted[j].y=sorted[j+1].y;
                                                        sorted[j+1].x=temp.x;
                                                        sorted[j+1].y=temp.y;
                                                }
                                        }
                                }
        }
        else
        {
		for(i=0;i<n-1;i++)
                        {
                        for(j=0;j<n-i-1;j++)
                                {
                                        if(sorted[j].y>sorted[j+1].y)
                                                {
                                                        temp.x=sorted[j].x;
                                                        temp.y=sorted[j].y;
                                                        sorted[j].x=sorted[j+1].x;
                                                        sorted[j].y=sorted[j+1].y;
                                                        sorted[j+1].x=temp.x;
                                                        sorted[j+1].y=temp.y;
                                                }
                                        }
                                }
       
        }
        return sorted;
}


/////////////////////////////////////////////////////////////////////////////
//////////GET RIGHT-TOP points from given line//////////////////////////////
////////////////////////////////////////////////////////////////////////////
Point2D* getAboveRightPoints(int startx,int starty,Point2D* ptrx,Point2D* ptry,int len,int *currentPoint)
{       
        int k=0;
        int i,j;
        int count=0;
	int totalpoint=*currentPoint;
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

