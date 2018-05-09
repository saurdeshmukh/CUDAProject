#include <stdio.h>
#include<limits.h>
#include <cuda_runtime.h>
#define maxWIDTH 350
#define BOUND 100
#include<time.h>

typedef struct
{
int x;
int y;
}Point2D;

__host__ void getRandomInputPoints(int n,Point2D * ptr)
{
        srand(0);
        int i=0;
        int pointx=0,pointy=0;
        for(i=0;i<n;i++)
        {
                pointx=rand()%BOUND;
                ptr->x=pointx;
                pointy=rand()%BOUND;
                ptr->y=pointy;
                ptr++;
        }
}

__host__ void printArray(Point2D*ptr,int n)
{
    int i=0;
    for(i=0;i<n;i++)
    {
        printf("Point %d - X: %d , Y: %d\n",i+1,ptr[i].x,ptr[i].y);

    }

}
__device__ int  minAreaFunction(int *ptr)
{
	int minArea=INT_MAX;
	for(int i=0;i<(maxWIDTH*maxWIDTH);i++)
		{
			if(ptr[i]<minArea && ptr[i]!=0)
			{
				minArea=ptr[i];
			}
		}
	return minArea;

}
__device__ void sortedArea(int *area,int *currentPoint)
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


__device__ int * getArea(Point2D *ptr,int len,int leftEdge,int bottomEdge,int *currentPoint)
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

__device__ Point2D* getAboveRightPoints(int startx,int starty,Point2D* ptrx,Point2D* ptry,int len,int *currentPoint)
{
    int k=0;
    int i,j;
    int count=0;
    int totalpoint=*currentPoint;
    Point2D* temp;
    int check=0;
    for(i=startx;i<len;i++)
    {
        for(j=starty;j<len;j++)
        {
            if(ptrx[i].x==ptry[j].x && ptrx[i].y==ptry[j].y)
            {
                count++;
		break;
            }
        }
    }
    
    totalpoint=count;
    
    
    temp=(Point2D*)malloc(totalpoint*sizeof(Point2D));
    for(j=starty;j<len;j++)
    {
        for(i=startx;i<len;i++)
        {
            if(ptry[j].x==ptrx[i].x && ptry[j].y==ptrx[i].y)
            {
		check=0;
		for(int m=0;m<k;m++)
			if(ptry[j].x==temp[m].x && ptry[j].y==temp[m].y)
				check=1;
		if(check==0)
		{
                	temp[k].x=ptry[j].x;
                	temp[k].y=ptry[j].y;
                	k++;
			break;
		}
            }
        }
    }
	
    *currentPoint=k;
    return temp;
}

__device__ void sortingbyAxis(Point2D *points,Point2D *sorted,int n,int x)
{

	int i,j;
	Point2D temp;
        for(i=0;i<n;i++)
        {        
                sorted[i].x=points[i].x;
                sorted[i].y=points[i].y;
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
	//sort by y co-ordinate
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

}
__global__ void k_bounding_algorithm(Point2D * points,int n,int k,int *finalArea,Point2D * sortedX,Point2D * sortedY,int *minArea)
{
	int threadId = blockDim.x*blockIdx.x + threadIdx.x;
	if(threadId < ((n-k+1)*(n-k+1)))
	{
	int i=threadId / (n-k+1);
	int j=threadId %(n-k+1);
	Point2D bottomPoint;
        Point2D leftPoint;
        Point2D *Rpoints=NULL;
        int *area;
	int totalpoints=0;
        minArea[threadId]=0;
	if(threadId==0)
	{
		sortingbyAxis(points,sortedX,n,1);
		sortingbyAxis(points,sortedY,n,0);
	}
	minArea[threadId]=INT_MAX;
	__syncthreads();
	leftPoint=sortedX[i];
        bottomPoint=sortedY[j];
	if(leftPoint.x <= bottomPoint.x && leftPoint.y >= bottomPoint.y)
	{
            int leftEdge=(int)(leftPoint.x-1);
            int bottomEdge=(int)(bottomPoint.y-1);
            Rpoints=getAboveRightPoints(i,j,sortedX,sortedY,n,&totalpoints);
		if(totalpoints>=k)
                {
			area=getArea(Rpoints,n,leftEdge,bottomEdge,&totalpoints);
            		sortedArea(area,&totalpoints);
			minArea[threadId]=area[k-1];
		}
	}
	__syncthreads();
	if(threadId ==0)
        {
                *finalArea=minAreaFunction(minArea);
		free(Rpoints);
		free(area);
        }
    }

}

int main(void)
{
    cudaError_t err = cudaSuccess;
    cudaEvent_t seq_start,seq_stop;    

   int n=0;
   int k=0;
    
    printf("\nEnter Number of Points in plane(n):");
    fflush(stdin);
    scanf("%d",&n);
    printf("\nEnter Number of Points inside square(k):");
    fflush(stdin);
    scanf("%d",&k);

   int *h_minArea=NULL;
    
    cudaEventCreate(&seq_start);
    cudaEventCreate(&seq_stop);

    Point2D *h_points = (Point2D *)malloc(n*sizeof(Point2D));

    if (h_points == NULL)
    {
        fprintf(stderr, "Failed to allocate host vectors!\n");
        exit(EXIT_FAILURE);
    }

    Point2D *h_sortedX = (Point2D *)malloc(maxWIDTH*sizeof(Point2D));
    if (h_sortedX == NULL)
    {
        fprintf(stderr, "Failed to allocate sorted X host vectors!\n");
        exit(EXIT_FAILURE);
    }
    Point2D *h_sortedY = (Point2D *)malloc(maxWIDTH*sizeof(Point2D));
    if (h_sortedY == NULL)
    {
        fprintf(stderr, "Failed to allocate sorted Y host vectors!\n");
        exit(EXIT_FAILURE);
    }

    int *h_Area = NULL;
    err = cudaMalloc((void**)&h_Area,maxWIDTH*maxWIDTH*sizeof(int));

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    getRandomInputPoints(n,h_points);

    printf("\nPoints:\n");
    printArray(h_points,n);
    h_minArea = (int*)malloc(sizeof(int));

    Point2D *d_points = NULL;
    err = cudaMalloc((void**)&d_points,n*sizeof(Point2D));

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(d_points,h_points,n*sizeof(Point2D),cudaMemcpyHostToDevice);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy vector A from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    
    int *d_minArea = NULL;
    err = cudaMalloc((void**)&d_minArea,sizeof(int));

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    
    err = cudaMemcpy(d_minArea,h_minArea,sizeof(int),cudaMemcpyHostToDevice);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy minArea from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

     int *d_Area = NULL;
    err = cudaMalloc((void**)&d_Area,maxWIDTH*maxWIDTH*sizeof(int));

    if (err != cudaSuccess)
    {   
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(d_Area,h_Area,maxWIDTH*maxWIDTH*sizeof(int),cudaMemcpyHostToDevice);

    if (err != cudaSuccess)
    {   
        fprintf(stderr, "Failed to copy minArea from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    Point2D *d_sortedX = NULL;
    err = cudaMalloc((void**)&d_sortedX,n*sizeof(Point2D));

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device sortedX (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    Point2D *d_sortedY = NULL;
    err = cudaMalloc((void**)&d_sortedY,n*sizeof(Point2D));

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device sortedY (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(d_sortedX,h_sortedX,n*sizeof(Point2D),cudaMemcpyHostToDevice);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy sortedX from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(d_sortedY,h_sortedY,n*sizeof(Point2D),cudaMemcpyHostToDevice);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy sortedY from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    int blocksPerGrid = 3;
    dim3 threadsPerBlock (1024,1,1);
    printf("CUDA kernel launch with %d blocks of 1024 threads\n", blocksPerGrid);
    cudaEventRecord(seq_start);
    k_bounding_algorithm<<<blocksPerGrid,threadsPerBlock>>>(d_points,n,k,d_minArea,d_sortedX,d_sortedY,d_Area);
    cudaEventRecord(seq_stop);
    cudaEventSynchronize(seq_stop);
    float seq_milliseconds = 0;
   err = cudaEventElapsedTime(&seq_milliseconds, seq_start, seq_stop);
    if (err != cudaSuccess)
   {
        fprintf(stderr, "Failed to calculate elapse time (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    
    printf("The elapsed time is %.2f ms\n", seq_milliseconds);

    err = cudaGetLastError();

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(h_minArea,d_minArea,sizeof(int),cudaMemcpyDeviceToHost);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy vector A from device to host (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
     }
    
    printf("\n%d\n",*h_minArea);
    
    err = cudaFree(d_minArea);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free d_minArea (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaFree(d_points);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free d_points (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    free(h_points);

    err = cudaDeviceReset();

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to deinitialize the device! error=%s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    cudaFree(d_sortedX);
    cudaFree(d_sortedY);
    return 0;
}

