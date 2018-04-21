#include<stdio.h>
#include<limits.h>

#define BOUND 5
#pragma once
typedef struct{
int x;
int y;
}Point2D;

void sortedAraa(int *,int *);
Point2D * sortArray(int,Point2D *,int);
int * getArea(Point2D *,int,int,int,int *);
Point2D* getAboveRightPoints(int,int,Point2D *,Point2D *,int,int *);
