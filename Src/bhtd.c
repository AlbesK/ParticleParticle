//Barnes-Hut Algorithm -- Implementation in 2D

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*
    Point structure, having for 2D 2 components
*/
struct point 
{
    double x;
    double y;
};

/*
    Body structure, having coordinates in 2D, mass and charge.
*/
struct body 
{
    struct point pos; // Position
    double mass;   // Mass
    double charge;  // Charge
    struct point F_felt;
};

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

	
/*
    Recursively display tree or subtree
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

/*
    Deconstruct quad tree (Postorder)
*/ 
void deconstruct_tree(struct quad* root)
{
    if(root != NULL)
    {
        deconstruct_tree(root->NE);
        deconstruct_tree(root->SE);
        deconstruct_tree(root->SW);
        deconstruct_tree(root->NW);

        free(root);
    }
}

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

/*
    Check if the body is residing inside the node through its coordinates
*/
bool contains(struct quad* nd, struct point p){
        return (p.x < (nd->centre.x+nd->s/2) &&
        p.x > (nd->centre.x-nd->s/2) &&
        p.y < (nd->centre.y+nd->s/2) &&
        p.y > (nd->centre.y-nd->s/2));
        
}


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
/*
    Construct tree (top down) by counting N particles in each node and checking if its a twig 
    (N>2) or a leaf (N=1). Empty nodes are ignored.
*/
int count(struct quad* nd, struct body* bodies, int* N_PARTICLES, int* track){
    if(nd==NULL){ printf("Node is NULL!!\n");return 0;}

    int number = 0; // Number of particles
    double centre_x = 0; // x component of pseudobody
    double centre_y = 0; // y component of pseudobody
    double centre_mass = 0; // Mass of Pseudobody
    double total_charge = 0; // extra term since we have charges!!
    int index = 0; //Index to save individual body for case 1

    // printf("Count call\n");

    for(int i=0; i<*N_PARTICLES; i++){
        if(contains(nd, bodies[i].pos)){
            number++;
            centre_mass += bodies[i].mass;
            centre_x += ((bodies[i].mass)*(bodies[i].pos.x));
            centre_y += ((bodies[i].mass)*(bodies[i].pos.y));
            total_charge += bodies[i].charge;
            index = i;
        }
    }

    if(number==0){
        // printf("Number is 0\n"); 
        // printf("Out of the recursion\n");  
        return 0;
    }
    // printf("Number is: %i\n", number);

    if(number==1){
            nd->b = &bodies[index]; 
            nd->data = index; //Assign the number of the body from the Bodies array, this is for getting back with data where the body is stored as a leaf
            // printf("Pointer to %i\n", nd->data); 
            // printf("Out of the recursion\n");             
            return 0;
    }

    if(number>=2){ // I know its Null as there are more than 2 bodies here.
            if(nd->divided!=true){
            // printf("CENTRE MASS: %f\n",centre_mass);
            centre_x = centre_x/centre_mass;
            centre_y = centre_y/centre_mass;
            struct body pseudobody = {.mass = centre_mass, .pos = ((centre_x), (centre_y)), .charge = total_charge};
            nd->b = &pseudobody; //Assign pseudobody
            printf("Pseudobody [%f,%f] at %i\n", centre_x,centre_y, nd->data);
        
                subdivide(nd, track);
            }
            
    }

    count(nd->NE,bodies,N_PARTICLES, track);
    count(nd->SE,bodies,N_PARTICLES, track);
    count(nd->SW,bodies,N_PARTICLES, track);
    count(nd->NW,bodies,N_PARTICLES, track);

}

/*
    Search quad tree for node with specific data in inorder format
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

/*
    Queue datastructure
*/
/* helper queue for levelorder */
struct linkedList
{
  struct quad* data;
  struct linkedList* next;
  
}; 
 
struct linkedList* begin;
struct linkedList* end;

/*
    Push element inside the end part of the queue by allocating new memory dynamically
*/ 
void enqueue(struct quad* nd)
{
    struct linkedList* temp = malloc(sizeof(struct linkedList));
    temp->data = nd;
    temp->next = NULL;
    if(begin==NULL && end==NULL){
        begin = end = temp;
    }
    end->next = temp;
    end = temp;
}
 /*
    Pop element from queue and free its memory
 */
void dequeue()
{
    struct linkedList* temp = begin;
    if(begin==NULL){return;}
    if(begin==end){
        begin = NULL;
        end = NULL;
    }
    else{
        begin = begin->next;
    }
    free(temp);
}
 
bool queue_empty()
{
  return (begin==NULL && end==NULL);
}
/*
    Level Order Traversal for force summation ( Breadth first traversal)
*/
void levelorder(struct quad* n)
{
  enqueue(n);
  
  while (!queue_empty())
  {
    printf("%d\n",begin->data->data);
    
    if (begin->data->NE)
      enqueue(begin->data->NE);
    if (begin->data->SE)
      enqueue(begin->data->SE);
    if (begin->data->SW)
      enqueue(begin->data->SW);
    if (begin->data->NW)
      enqueue(begin->data->NW);
    dequeue();
    
  }
  
}

/*
    Get the magnitude of the 2D vector
*/
double mag(double* d){
    double m = sqrt(d[0]*d[0]+d[1]*d[1]);
    return m;
}
/*
    Get Vector difference from points
*/
void difference(struct point* p1, struct point* p2, double *d){
    d[0] = p2->x - p1->x;
    d[1] = p2->y - p1->y;
    printf("P2 [%f,%f], P1 [%f,%f]\n", p2->x, p2->y, p1->x, p1->y); 
}

/*
    Get force summation
*/
void force_summation(struct quad* nd, struct body* bodies, int* N_PARTICLES){
    double d[2] = {0,0};
    double m;
    for(int i=0; i<*N_PARTICLES; i++){
        difference(&bodies[i].pos, &nd->NE->b->pos, d);
        m = mag(d);
        printf("|d|:%f, [%f,%f]\n",m,d[0],d[1]);
    }
}

void xyt_data_particles(struct body* bodies, int* N_PARTICLES, double t){
    FILE * f; 
    f = fopen("/home/albes/Desktop/bodiestd.txt", "w"); /* open the file for writing*/
    printf("Writting...\n");
    /* write 10 lines of text into the file stream*/    
    fprintf(f, "N,X,Y,M,C,T\n");

    for(int i = 0; i < *N_PARTICLES;i++){
        fprintf (f, "%d,%f,%f,%f,%f\n", i, bodies[i].pos.x, bodies[i].pos.y, bodies[i].mass, bodies[i].charge);
    }
    fprintf(f,",,,,,%f",t);

    /* close the file*/  
    fclose (f);
    printf("Closed file.\n");
}

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

void xy_trees(struct quad* nd){
    FILE * f; 
    f = fopen("/home/albes/Desktop/nodestd.txt", "w"); /* open the file for writing*/
    printf("Writting...\n");
    /* write 10 lines of text into the file stream*/    
    fprintf(f, "N,X,Y,S\n");
    printdata(nd, f);
    /* close the file*/  
    fclose (f);
    printf("Closed file.\n");
}

/*
    Main function to run the program
*/
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
    int S = 100;
    char x[2]={'x', 'y'};
    srand(seed);

    for (int i=0; i < N_PARTICLES; i++){

            double mass = 5 * ((double) rand() / (double) RAND_MAX ); // 1,5
            double charge = 10 * ((double) rand() / (double) RAND_MAX ) - 5; // -5, 5
            struct point p = {.x = S * ((double) rand() / (double) RAND_MAX ) - S/2, // -50, 50
            .y = 100 * ((double) rand() / (double) RAND_MAX ) - 50};

            struct body b = {.mass = mass, .charge = charge, .pos = p };

            bodies[i] = b;
            printf("%d: %c:[%f], %c:[%f] \n",i, x[0], bodies[i].pos.x, x[1], bodies[i].pos.y );
    
    }

    int track = 0; // To keep track of twig numbering
    struct quad *root = newNode(0, 100, 0, 0); //Size of s=100 and pint of reference being (0,0) equiv. to (x_root, y_root)  
    //printf("Root square size is: %f\n", root->s);
    
    ts = clock(); // Start timer
    count(root, bodies, &N_PARTICLES, &track);
    te = clock(); // End timer
    double t = (double)(te-ts)/CLOCKS_PER_SEC; // Bottom-up tree construction time
    printf("Checking queue\n");
    // levelorder(root);
    // display_tree(root);
    force_summation(root,bodies, &N_PARTICLES);
    // check(root);
    char c;
    printf("Do you want to save the data? Y/n \n");
    scanf("%c", &c);
    
    if(c=='Y'){
        printf("Saving bodies data...\n");
        xyt_data_particles(bodies,&N_PARTICLES, t);
        printf("Saving tree data...\n");
        xy_trees(root);
        printf("Done\n");
    } else
    {
        printf("Continuing\n");   
    }
    
    // deconstruct the tree
    deconstruct_tree(root);
    free(bodies);

    printf("Released memory succesfuly\n");
    printf("Program took %f\n", t);

    return 0; 
}

