#include<stdio.h>
#include "bhHeaders.h"
/*
    Get Vector difference from points
*/
void difference(struct point* p1, struct point* p2, double *d){
    d[0] = p2->x - p1->x;
    d[1] = p2->y - p1->y;
    // printf("P2 [%f,%f], P1 [%f,%f]\n", p2->x, p2->y, p1->x, p1->y); 
}