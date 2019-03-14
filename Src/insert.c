#include<stdio.h>
#include"bhHeaders.h"
/*
    Construct quad tree from bottom-up by putting bodies inside it.
*/
int insert(struct quad* nd, struct body* b, int *index){

    // If current quad cannot contain it 
    if (!contains(nd,b->pos)){  
        return 0; // Not found yet so return 0 and go in the next function call
    } 

    if(nd->b==NULL){ // If there is no pointer to body, assign it (Essentially capacity is kept at 1 here with this method)
        nd->b = b;
        nd->data = *index; //Assign the number of the body from the Bodies array, this is for getting back with data where the body is stored as a leaf
        // printf("Pointer to %i\n", nd->data);
        return 1; // Found so return 1 so we can exit the recursion
    } 
    else{
    
        if(nd->divided!=true){ // Check if the quad quad has subdivided
            // subdivide(nd); // If not, subdivide! Temporarily commented out or might not include it at all in the near future for the top dowm approach
        }
            

        return insert(nd->NE, b, index)|| // Since insert is an int function, the return statement here returns 1 or 0 if 
            insert(nd->SE, b, index)||  // a node is found to point the body and thus save the body at. So for example if we
            insert(nd->SW, b, index)|| // have 2 bodies and the first one is always saved at root ( being empthy and not divided)
            insert(nd->NW, b, index); // then the second Body 1 if it is at NW subcell after division when it goes to the return state-
        // -ment it will go through the OR terms as the contain function will not let the first 3 OR terms ( being insert(nd->NE,...) || ... 
        // to insert(nd->SW,...) and pick the insert(nd->NW,...) to assign. The same process is repeated every time the function calls itself
        // and checks for where to put the body.
        
        
    }

}