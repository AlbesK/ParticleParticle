//Barnes-Hut Algorithm -- Implementation

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


struct node  //Node Structure
{ 
    int data; //key value
    int level; //How deep is it, starting from -1 (Root makes it )
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
  node->s = node->s/2; //Size of square halfed each time is called with same size for each but new coordinates for their centres
  node->center[0] = x; node->center[1] = y;
  
  // Initialize left and right children as NULL 
  node->nw = NULL; 
  node->ne = NULL;
  node->se = NULL;
  node->sw = NULL;

  //node->right = NULL; 
  return(node); 
} 

//Deallocate memory for all nodes:
void dispose(struct node* root)
{
    if(root != NULL)
    {
        dispose(root->nw);
        dispose(root->ne);
        dispose(root->se);
        dispose(root->sw);

        //dispose(root->sq);
        free(root);
    }
}


  
  
int main() {

    int N_DIMENSIONS = 2 ;
    int N_PARTICLES = 8;
    char c;
    //Physical_Properties_Array[Particles Position][Masses][Charges][..etc..] Perhaps better for all of these pointers.  
    double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));
    double *V = malloc(sizeof(double) * N_PARTICLES );
    double *Mass = malloc(sizeof(double) * N_PARTICLES);
    double *Charge = malloc(sizeof(double) * N_PARTICLES);
    double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));

    for (int i=0; i < N_PARTICLES; i++){
        for(int j=0; j < N_DIMENSIONS; j++){
            A[i][j] = 20 * ( (double) rand() / (double) RAND_MAX ) - 10;
            printf("Particle [%i] with [%f] \n", i, A[i][j]);
        }
    }

    for (int i = 0; i < N_PARTICLES; i++){
        Mass[i] = 5 * ((double) rand() / (double) RAND_MAX );
        Charge[i] = 10 * ((double) rand() / (double) RAND_MAX ) - 5;
        printf("Particle [%i] : Mass [%f], Charge [%f] \n", i, Mass[i], Charge[i]);
    }


    
    
    /*create root*/ //Size of s=20 and pint of reference being (0,0) equiv. to (x_root, y_root)
    //Original size corresponding to this node, and for s/d calculation


    struct node *root = newNode(0, 40.0, 0, 0);   
    

    //Count Particles in Cell/Node:
    int quadrant_[4] = {0,0,0,0};

    for(int i=0; i<N_PARTICLES; i++){
        if(A[i][0] >= root->center[0] && A[i][1] >= root->center[1]){quadrant_[0]++;}  //{quadrant_a++;} //depends on NODE
        if(A[i][0] >= root->center[0] && A[i][1] <= root->center[1]){quadrant_[1]++;}  //{quadrant_b++;}
        if(A[i][0] <= root->center[0] && A[i][1] <= root->center[1]){quadrant_[2]++;}  //{quadrant_c++;}
        if(A[i][0] <= root->center[0] && A[i][1] >= root->center[1]){quadrant_[3]++;}  //{quadrant_d++;}
        
    }

    printf("NE: %i, SE: %i, SW: %i, NW: %i \n", quadrant_[0], quadrant_[1], quadrant_[2], quadrant_[3]);

    //Is cell a twig? (>2 Particles) in this case it is:
    if(quadrant_[0]>=2){
        root->ne = newNode(-1, root->s/2, root->center[0]+root->s/2, root->center[1]+root->s/2 );
        printf("NE is a twig\n");
        } 
        else{
            if(quadrant_[0]!=0){
            root->ne = newNode(1, root->s/2, root->center[0]+root->s/2, root->center[1]+root->s/2);
            printf("NE is a leaf\n");
            } //else keep it null; 
        }
    if(quadrant_[1]>=2){
        root->se = newNode(-1, root->s/2, root->center[0]+root->s/2, root->center[1]-root->s/2);
        printf("SE is a twig\n");
        } 
        else{
            if(quadrant_[1]!=0){
            root->se = newNode(1, root->s/2, root->center[0]+root->s/2, root->center[1]-root->s/2);
            printf("SE is a leaf\n");
            }
        }
    if(quadrant_[2]>=2){
        root->sw = newNode(-1, root->s/2, root->center[0]-root->s/2, root->center[1]-root->s/2);
        printf("SW is a twig\n");
        } 
        else{
            if(quadrant_[2]!=0){
            root->sw = newNode(1, root->s/2, root->center[0]-root->s/2, root->center[1]-root->s/2);
            printf("SW is a leaf\n");
            }
        }
    if(quadrant_[3]>=2){
        root->nw = newNode(-1, root->s/2, root->center[0]-root->s/2, root->center[1]+root->s/2);
        printf("NW is a twig\n");
        } 
        else{
            if(quadrant_[0]!=0){
            root->nw = newNode(1, root->s/2, root->center[0]-root->s/2, root->center[1]+root->s/2);
            printf("NW is a leaf\n");
            }
        } 
    
    


    printf("Node is %i\n", root->data);

    /* remove the whole tree */
    dispose(root);

    free(A); //Free memory
    free(Mass);
    free(V);  
    free(F);
    free(Charge);

    return 0; 
  
}