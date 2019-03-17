#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"bhHeaders.h"
/* 
    Allocates a new node and respectively fills data, coordinates and size of square for that node.
*/
struct quad* newNode(int data, double s, double x, double y) 
{ 
    // Allocate memory for new quad  
    struct quad* quad = (struct quad*)malloc(sizeof(struct quad)); 

    // If out of memory abort:
    if(quad == NULL)
    {
        fprintf (stderr, "Out of memory!!! (create_node)\n");
        exit(1);
    }
    // Assign data to this quad, s size of square, centre point of it
    // b as NULL for not storing a pointer to a body yet, false for divided as it has not subdivided yet.
    quad->data = data;
    quad->s = s; 
    quad->centre.x = x; quad->centre.y = y;
    quad->b = NULL;
    quad->divided = false;

    // Initialize all children as NULL 
    quad->NE = NULL; 
    quad->SE = NULL;
    quad->SW = NULL;
    quad->NW = NULL;

    return(quad); 
}