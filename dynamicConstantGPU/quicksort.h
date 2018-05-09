#include<stdio.h>
#include<struct.h>
__global__ void qsort(Point2D *,int ,int ,int);
__device__ void swap(Point2D *,Point2D *);
__device__ int partition(Point2D *,int ,int,int);
