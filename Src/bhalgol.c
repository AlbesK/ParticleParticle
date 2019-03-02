//Barnes-Hut Algorithm -- Implementation

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct point
{
    double x;
    double y;
};

struct body
{
    struct point pos; // Position
    double mass;   // Mass
    double charge;  // Charge
};

struct quad  // Node Structure
{ 
    int data; // key value
    // How deep is it, starting from -1 (Root makes it )
    double s; // Original size corresponding to this quad, and for s/d calculation
    struct point centre; // Center of this quad of this quad
    bool divided; // Check if it has divided
    int capacity; // Capacity for this node

    struct body *b;

    struct quad *NW; 
    struct quad *NE;
    struct quad *SE;
    struct quad *SW; 
}; 
  
/* newNode() allocates a new quad with the given data and NULL NW, NE, SE, SW pointers */
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
    // Assign data to this quad 
    quad->data = data;
    quad->s = s; //Size of square halfed each time is called with same size for each but new coordinates for their centres
    quad->centre.x = x; quad->centre.y = y;
    quad->capacity = 0;
    quad->b = NULL;
    quad->divided = false;

    // Initialize all children as NULL 
    quad->NE = NULL; 
    quad->SE = NULL;
    quad->SW = NULL;
    quad->NW = NULL;

    return(quad); 
} 

	
/*
    Recursively display tree or subtree
*/
void display_tree(struct quad* nd)
{
    if (nd == NULL)
        return;
    /* display quad data */
    printf(" %*c(%d) \n %*c[%f, %f] \n %*c[%f]\n\n",50, ' ', nd->data, 42,' ', nd->centre.x, nd->centre.y, 47, ' ', nd->s);
    
    if(nd->NE != NULL)
        printf("%*c|NE:%d|  ",34,' ',nd->NE->data);
    if(nd->SE != NULL)
        printf("|SE:%d|  ",nd->SE->data);
    if(nd->SW != NULL)
        printf("|SW:%d|  ",nd->SW->data);
    if(nd->NW != NULL)
        printf("|NW:%d|",nd->NW->data);
    printf("\n\n");
 
    display_tree(nd->NE);
    display_tree(nd->SE);
    display_tree(nd->SW);
    display_tree(nd->NW);
}

//Deallocate memory for all nodes:  
void dispose(struct quad* root)
{
    if(root != NULL)
    {
        dispose(root->NE);
        dispose(root->SE);
        dispose(root->SW);
        dispose(root->NW);

        free(root);
    }
}
//New functions

void subdivide(struct quad* nd){
    
    if(nd == NULL){
        return;
    }
    
    //printf("Subdivide call at: %i \n", nd->data);
    //twig--;
    nd->NE = newNode(-1, nd->s/2, nd->centre.x + nd->s/4, nd->centre.y + nd->s/4);
    
    
    //twig--;
    nd->SE = newNode(-1, nd->s/2, nd->centre.x + nd->s/4, nd->centre.y - nd->s/4);
    
    
    //twig--;
    nd->SW = newNode(-1, nd->s/2, nd->centre.x - nd->s/4, nd->centre.y - nd->s/4);
    
    
    //twig--;
    nd->NW = newNode(-1, nd->s/2, nd->centre.x - nd->s/4, nd->centre.y + nd->s/4); 

    nd->divided = true;

}

bool contains(struct quad* nd, struct point p){
        return (p.x < (nd->centre.x+nd->s/2) &&
        p.x > (nd->centre.x-nd->s/2) &&
        p.y < (nd->centre.y+nd->s/2) &&
        p.y > (nd->centre.x-nd->s/2));
        
}

void insert(struct quad* nd, struct body* b, int *index, int *found){

    if(*found==1){return;}

    // Current quad cannot contain it 
    if (!contains(nd,b->pos)){ 
        return; 
    } 

    if(nd->b==NULL){ // If there is no pointer to body assign it (Essentially capacity is kept at 1 here with this method)
        nd->b = b;
        nd->capacity = nd->capacity++;
        nd->data = *index;
        *found = 1;
        //printf("Pointer to %i\n", nd->data);
    } else{
        if(nd->divided!=true){ // Check if the quad quad has subdivided
            subdivide(nd);
        }
        if(*found==0){
            insert(nd->NE, b, index, found);
            if(*found==1){return;}
        
            //printf("skipped NE\n");
               
            insert(nd->SE, b, index, found);
            if(*found==1){return;}
            
            //printf("skipped SE\n");
        
            insert(nd->SW, b, index, found);
            if(*found==1){return;}
            
            //printf("skipped SW\n");
        
            insert(nd->NW, b, index, found);
            if(*found==1){return;}
            
            //printf("skipped NW\n");
        }
        
        
    }


}


/*
    search for a specific key
*/
struct quad* Search(struct quad* root, int data) {
	// base condition for recursion
	// if tree/sub-tree is empty, return and exit
	if(root == NULL){return NULL;}

	printf("%i \n",root->data); // Print data
    if(root->data == data){return root;}
	
    Search(root->NW, data);     // Visit NW subtree
	Search(root->SW, data);    // Visit SW subtree
    Search(root->SE, data);   // Visit SE subtree
    Search(root->NE, data);  // Visit NE subtree
}

  
int main() {

    int N_DIMENSIONS = 2; int seed=1;
    int N_PARTICLES;
    char term;
    clock_t ts, te;
    printf("How many particles?\n");
    if (scanf("%d%c", &N_PARTICLES, &term) != 2 || term != '\n') {
        printf("Failure: Not an integer. Try again\n");
        exit(-1);
    } 

    printf("Calculating\n");
    if (N_PARTICLES < 2) {
        printf("Insufficent number of particles %i\n", N_PARTICLES);
        exit(-1);
    } 
    struct body* bodies = malloc(sizeof(struct body)*N_PARTICLES);

    //Initialise values:
    char x[2]={'x', 'y'};
    srand(seed);

    for (int i=0; i < N_PARTICLES; i++){

            double mass = 5 * ((double) rand() / (double) RAND_MAX ); // 1,5
            double charge = 10 * ((double) rand() / (double) RAND_MAX ) - 5; // -5, 5
            struct point p = {.x = 100 * ((double) rand() / (double) RAND_MAX ) - 50, // -50, 50
            .y = 100 * ((double) rand() / (double) RAND_MAX ) - 50};

            struct body b = {.mass = mass, .charge = charge, .pos = p };

            bodies[i] = b;
            //printf("%c:[%f], %c:[%f] \n", x[0], bodies[i].pos.x, x[1], bodies[i].pos.y );
    
    }


    /*create root*/ 
    
    struct quad *root = newNode(0, 100, 0, 0); //Size of s=100 and pint of reference being (0,0) equiv. to (x_root, y_root)  
    //printf("Root square size is: %f\n", root->s);
    
    ts = clock();
    for(int i=0; i<N_PARTICLES; i++){
        int found = 0;
        insert(root, &bodies[i], &i, &found);
    }
    te = clock();
    double d = (double)(te-ts)/CLOCKS_PER_SEC;
    
    //display_tree(root);

    /* remove the whole tree */
    dispose(root);
    free(bodies);

    printf("Released memory succesfuly\n");
    printf("Program took %f\n", d);

    return 0; 
}

/*         if(quadrant_[0]>=2){
            twig--;
            nd->NE = newNode(nd->data+twig, nd->s/2, nd->center[0]+nd->s/4, nd->center[0]+nd->s/4);
        } 
        if(quadrant_[1]>=2){
            twig--;
            nd->SE = newNode(nd->data+twig, nd->s/2, nd->center[0]+nd->s/4, nd->center[0]-nd->s/4);
        }
        if(quadrant_[2]>=0){
            twig--;
            nd->SW = newNode(nd->data+twig, nd->s/2, nd->center[0]-nd->s/4, nd->center[0]-nd->s/4);
        }
        if(quadrant_[3]>=0){
            twig--;
            nd->NW = newNode(nd->data+twig, nd->s/2, nd->center[0]-nd->s/4, nd->center[0]+nd->s/4);
        }
    void check(struct quad* root, double (*A)[2], int N_PARTICLES, int* quadrant_ ){
        
        
        if(root==NULL){
            return;
        }
        int number = 0;
        int leaf = 0;
        
        number = count(root, A, N_PARTICLES, quadrant_);
        if(number>=2){
            //printf("T>=2\n");
            subdivide(root, A, N_PARTICLES, quadrant_);
            check(root->NE, A, N_PARTICLES, quadrant_);
            check(root->SE, A, N_PARTICLES, quadrant_);
            check(root->SW, A, N_PARTICLES, quadrant_);
            check(root->NW, A, N_PARTICLES, quadrant_);
        }
        if(number==1){root->data = -root->data+leaf++;}
        if(number==0){root=NULL;}
        
        
    }
*/