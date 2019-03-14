#include<stdio.h>
#include "bhHeaders.h"
/*
    Helper function for xy_tree.c to print data to csv file so it can be processed later
*/
void printdata(struct quad* nd, FILE* f){
    if (nd == NULL){return;}
    // Display the data of the node
    fprintf(f,"%d,%f,%f,%f\n",nd->data, nd->centre.x, nd->centre.y, nd->s);
    
    // Recurse through
    printdata(nd->NE,f);    
    printdata(nd->SE,f);
    printdata(nd->SW,f);
    printdata(nd->NW,f);
}