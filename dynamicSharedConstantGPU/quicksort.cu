#include "quicksort.h"
#include<cuda_runtime.h>

__device__ void swap(Point2D *a,Point2D* b)
{
Point2D t; 
t.x = a->x;
t.y=a->y;
a->x= b->x;
a->y=b->y;
b->x = t.x;
b->y=t.y;
}

__device__ int partition(Point2D  *data,int l,int r,int x)
{
 Point2D pivot = data [r];
 int i = l-1;

 for(int j = l;j<=r-1;j++)
 {
   if(x==1)
   {
   	if(data[j].x <= pivot.x)
    	{
    	 i++;
     	swap(&data[i],&data[j]); 
     	}
   }
   else
   {
	if(data[j].y <= pivot.y)
        {
         i++;
        swap(&data[i],&data[j]);
        }
    }
 }
 swap(&data[i+1],&data[r]);
 return (i+1);
}

__global__ void qsort(Point2D *data,int  l,int r,int x)
{

if(l<r)
{
int pivot = partition (data,l,r,x);

cudaStream_t s1,s2;
unsigned int flag = cudaStreamDefault;

cudaStreamCreateWithFlags(&s1,flag);
cudaStreamCreateWithFlags(&s2,flag);

qsort<<<1,1,0,s1>>>(data,l,pivot-1,x);
qsort<<<1,1,0,s1>>>(data,pivot+1,r,x);
}
}


