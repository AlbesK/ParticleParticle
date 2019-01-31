//Barnes-Hut Algorithm -- Implementation

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>



struct node  //Node Structure
{ 
    int data; //key value
    //How deep is it, starting from -1 (Root makes it )
    double s; //Original size corresponding to this node, and for s/d calculation
    double center[2]; //Center of this quad of this node
    
    struct node *nw; 
    struct node *ne;
    struct node *se;
    struct node *sw; 
}; 
  
/* newNode() allocates a new node with the given data and NULL nw, ne, se, sw pointers */
struct node* newNode(int data, double s, double x, double y) 
{ 
  // Allocate memory for new node  
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  
  // Assign data to this node 
  node->data = data;
  node->s = s; //Size of square halfed each time is called with same size for each but new coordinates for their centres
  node->center[0] = x; node->center[1] = y;
  
  // Initialize all children as NULL 
  node->ne = NULL; 
  node->se = NULL;
  node->sw = NULL;
  node->nw = NULL;


  return(node); 
} 
	






/*
    Recursively display tree or subtree
*/
void display_tree(struct node* nd)
{
    if (nd == NULL)
        return;
    /* display node data */
    printf("Node %d [%f, %f] ",nd->data, nd->center[0], nd->center[1]);
    if(nd->ne != NULL)
        printf("(NE:%d)",nd->ne->data);
    if(nd->se != NULL)
        printf("(SE:%d)",nd->se->data);
    if(nd->sw != NULL)
        printf("(SW:%d)",nd->sw->data);
    if(nd->nw != NULL)
        printf("(NW:%d)",nd->nw->data);
    printf("\n");
 
    display_tree(nd->ne);
    display_tree(nd->se);
    display_tree(nd->sw);
    display_tree(nd->nw);
}

//Deallocate memory for all nodes:  
void dispose(struct node* root)
{
    if(root != NULL)
    {
        dispose(root->ne);
        dispose(root->se);
        dispose(root->sw);
        dispose(root->nw);

        
        free(root);
    }
}


void count(struct node* nd, double (*A)[2], int N_PARTICLES, int *quadrant_){
    
    printf("Count call\n");

    quadrant_[0] = 0; quadrant_[1] = 0; quadrant_[2] = 0; quadrant_[3] = 0;
    for(int i=0; i<N_PARTICLES; i++){
        if(A[i][0] >= nd->center[0] && A[i][1] >= nd->center[1]){quadrant_[0]++;}  //{quadrant_a++;} //depends on NODE
        if(A[i][0] >= nd->center[0] && A[i][1] <= nd->center[1]){quadrant_[1]++;}  //{quadrant_b++;}
        if(A[i][0] <= nd->center[0] && A[i][1] <= nd->center[1]){quadrant_[2]++;}  //{quadrant_c++;}
        if(A[i][0] <= nd->center[0] && A[i][1] >= nd->center[1]){quadrant_[3]++;}  //{quadrant_d++;}
        
    }

    
}

void subdivide(struct node* nd, double (*A)[2], int *quadrant_, int N_PARTICLES){
    
    
    printf("Subdivide call\n");
    count(nd, A, N_PARTICLES, quadrant_);
    

    if(quadrant_[0]>=2){
        printf("Subdivide NE quadrant 0 \n");
        nd->ne = newNode(nd->data-1, nd->s/2, nd->center[0]+nd->s/4, nd->center[1]+nd->s/4);
        
        subdivide(nd->ne, A, quadrant_, N_PARTICLES);
    } 
    else{

        nd->ne = newNode(nd->data+1, nd->s/2, nd->center[0]+nd->s/4, nd->center[1]+nd->s/4);
        //nd->ne->leaf = leaf + 1;
        //printf("NE is a leaf with value %i\n", nd->ne->leaf);
            //else keep it null; 
    }

    if(quadrant_[1]>=2){
        printf("Subdivide SE quadrant 1\n");
        nd->se = newNode(nd->data-1, nd->s/2, nd->center[0]+nd->s/4, nd->center[1]-nd->s/4);
        //subdivide(nd->se, A, quadrant_, N_PARTICLES);
    } 
    else{
                
        nd->se = newNode(nd->data+1, nd->s/2, nd->center[0]+nd->s/4, nd->center[1]-nd->s/4);
        //nd->ne->leaf = leaf + 1;
        //printf("NE is a leaf with value %i\n", nd->ne->leaf);
            //else keep it null; 
    }
    
    if(quadrant_[2]>=2){
        printf("Subdivide SW quadrant 2\n");
        nd->sw = newNode(nd->data-1, nd->s/2, nd->center[0]-nd->s/4, nd->center[1]-nd->s/4);
        //subdivide(nd->sw, A, quadrant_, N_PARTICLES);
    } 
    else{
                
        nd->sw = newNode(nd->data+1, nd->s/2, nd->center[0]-nd->s/4, nd->center[1]-nd->s/4);
        //nd->ne->leaf = leaf + 1;
        //printf("NE is a leaf with value %i\n", nd->ne->leaf);
            //else keep it null; 
    }

    if(quadrant_[3]>=2){
        printf("Subdivide NW quadrant 3\n");
        nd->nw = newNode(nd->data-1, nd->s/2, nd->center[0]-nd->s/4, nd->center[1]+nd->s/4);
        //subdivide(nd->nw, A, quadrant_, N_PARTICLES);
    } 
    else{

        nd->nw = newNode(nd->data+1, nd->s/2, nd->center[0]-nd->s/4, nd->center[1]+nd->s/4);
        //nd->ne->leaf = leaf + 1;
        //printf("NE is a leaf with value %i\n", nd->ne->leaf);
            //else keep it null; 
    }
}

  
  
int main() {

    int N_DIMENSIONS = 2;
    int N_PARTICLES = 8;
    char c;
    //Physical_Properties_Array[Particles Position][Masses][Charges][..etc..] Perhaps better for all of these pointers.  
    double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));
    double *V = malloc(sizeof(double) * N_PARTICLES );
    double *Mass = malloc(sizeof(double) * N_PARTICLES);
    double *Charge = malloc(sizeof(double) * N_PARTICLES);
    double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));

    //Initialise values:

    for (int i=0; i < N_PARTICLES; i++){
        for(int j=0; j < N_DIMENSIONS; j++){
            A[i][j] = 20 * ( (double) rand() / (double) RAND_MAX ) - 10; //-10, 10
            printf("Particle [%i] with [%f] \n", i, A[i][j]);
        }
    }

    for (int i = 0; i < N_PARTICLES; i++){
        Mass[i] = 5 * ((double) rand() / (double) RAND_MAX ); //1,5
        Charge[i] = 10 * ((double) rand() / (double) RAND_MAX ) - 5;//-5, 5
        printf("Particle [%i] : Mass [%f], Charge [%f] \n", i, Mass[i], Charge[i]);
    }


    
    
    /*create root*/ 
    
    struct node *root = newNode(0, 11.0, 0, 0); //Size of s=20 and pint of reference being (0,0) equiv. to (x_root, y_root)  
    printf("Root square size is: %f\n", root->s);

    //count(root, A, N_PARTICLES,)
    int *quadrant_ = malloc(sizeof(int)*4);
    quadrant_[0] = 0; quadrant_[1] = 0; quadrant_[2] = 0; quadrant_[3] = 0;
    
    //Is cell a twig? (>2 Particles) in this case it is:
    //count(root, A, N_PARTICLES, quadrant_);
    subdivide(root, A, quadrant_, N_PARTICLES);
    display_tree(root);

    /* remove the whole tree */
    dispose(root);
    free(quadrant_);
    free(A); //Free memory
    free(Mass);
    free(V);  
    free(F);
    free(Charge);

    return 0; 
}