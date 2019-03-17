#include<stdio.h>
#include"bhHeaders.h"

/*
    Subdivide node to 4 quadrants and assign memory dynamically through newNode() function
*/
void subdivide(struct quad* nd, int* track){ 
    
    if(nd == NULL){ // If there is no node do not subdive. (safety measure)
        return;
    }
    // printf("Subdivide call at: %i \n", nd->data);
    // Call newNode function for each child node that was Null of the node at hand and assign a memory block of size (struct quad)
    // -n is assigned here if the node is a 'twig' meaning it is not a 'leaf' for now empty cells are also -n where n integers that
    // that are unique for each quad.
    //    _____________________
    //   |          |          |
    //   |   (NW)   |   (NE)   |
    //   |          |          |
    //   |    -+    |    ++    |
    //   |__________|__________|
    //   |          |          |
    //   |    --    |    +-    |
    //   |          |          |
    //   |   (SW)   |   (SE)   |
    //   |__________|__________|

    nd->NE = newNode(*track-1, nd->s/2, nd->centre.x + nd->s/4, nd->centre.y + nd->s/4); 
    nd->SE = newNode(*track-2, nd->s/2, nd->centre.x + nd->s/4, nd->centre.y - nd->s/4); 
    nd->SW = newNode(*track-3, nd->s/2, nd->centre.x - nd->s/4, nd->centre.y - nd->s/4); 
    nd->NW = newNode(*track-4, nd->s/2, nd->centre.x - nd->s/4, nd->centre.y + nd->s/4); 
    
      
    nd->divided = true; // The node subdivided ( safety for not subdividing again the same node )
    *track = *track-4;
    // printf("Track is: %i\n", *track);

}