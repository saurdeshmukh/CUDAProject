#include"randomPoints.h"
#include"utility.h"
#include<time.h>

void getRandomInputPoints(int n,Point2D * ptr)
{       
	srand(time(0));
        int i=0;
        //int halfBound=BOUND/2;
        int pointx=0,pointy=0;
        for(i=0;i<n;i++)
        {       
                //getting x-coordinate value
                pointx=rand()%BOUND;
                //if(pointx>=halfBound)
                //ptr->x=pointx%halfBound;
                //else    
                //ptr->x=(-1)*(pointx%halfBound);
		
		ptr->x=pointx;                


                //getting y-coordinate value
                pointy=rand()%BOUND;
                //if(pointy>=halfBound)
                //ptr->y=pointy%halfBound;
                //else    
                //ptr->y=(-1)*(pointy%halfBound);
		
		ptr->y=pointy;

                ptr++;
        }
}


