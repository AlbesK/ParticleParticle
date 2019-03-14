#include<stdio.h>
#include"bhHeaders.h"

/*
    Get the magnitude of the 2D vector
*/
double mag(double* d){
    double m = sqrt(d[0]*d[0]+d[1]*d[1]);
    return m;
}