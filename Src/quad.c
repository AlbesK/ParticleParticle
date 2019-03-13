#include<stdio.h>

/*
    Quad tree node structure
*/
struct quad  
{ 
    int data; // key value
    double s; // Original size corresponding to this quad, and for s/d calculation soon
    struct point centre; // Center of this node
    bool divided; // Check if it has divided

    struct body *b; // Pointer to body structure

    // Pointers to children of this node taken with respect to compass directions.
    struct quad *NW; 
    struct quad *NE;
    struct quad *SE;
    struct quad *SW; 

    struct quad *Parent;
    
}; 