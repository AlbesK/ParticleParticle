#include<stdio.h>
#include"bhHeaders.h"

/*
    Level Order Traversal for force summation ( Breadth first traversal)
*/
void levelorder(struct quad* n)
{
    enqueue(n);
    enqueue(NULL); // Extra NUll parameter for checking when the tree goes to the next level after enquing all children in one level.
    struct quad* curr = NULL;
    while (!queue_empty())
    {
    
    curr = begin->data;
    dequeue();
    if(curr!=NULL){
        
        if (curr->NE)
            enqueue(curr->NE);
        if (curr->SE)
            enqueue(curr->SE);
        if (curr->SW)
            enqueue(curr->SW);
        if (curr->NW)
            enqueue(curr->NW);
        printf("%d ",curr->data);
    }
    else{
        printf("\n");
        if(!queue_empty()){
            enqueue(NULL);
        }
    }
  
    }
}