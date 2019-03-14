#include<stdio.h>
#include"bhHeaders.h"

/*
    Recursively display tree inorder
*/
void display_tree(struct quad* nd)
{
    if (nd == NULL)
        return;
    // Display the data of the node
    printf(" %*c(%d) \n %*c[%f, %f] \n %*c[%f]\n\n",50, ' ', nd->data, 42,' ', nd->centre.x, nd->centre.y, 47, ' ', nd->s);
    
    // Display data for each node plus some formating it looks better
    if(nd->NE != NULL)
        printf("%*c|NE:%d|  ",34,' ',nd->NE->data);
    if(nd->SE != NULL)
        printf("|SE:%d|  ",nd->SE->data);
    if(nd->SW != NULL)
        printf("|SW:%d|  ",nd->SW->data);
    if(nd->NW != NULL)
        printf("|NW:%d|",nd->NW->data);
    printf("\n\n");
    
    // Recurse through
    display_tree(nd->NE);
    display_tree(nd->SE);
    display_tree(nd->SW);
    display_tree(nd->NW);
}