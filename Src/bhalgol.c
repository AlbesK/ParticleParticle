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
    
    struct node *NW; 
    struct node *NE;
    struct node *SE;
    struct node *SW; 
}; 
  
/* newNode() allocates a new node with the given data and NULL NW, NE, SE, SW pointers */
struct node* newNode(int data, double s, double x, double y) 
{ 
  // Allocate memory for new node  
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  
  // Assign data to this node 
  node->data = data;
  node->s = s; //Size of square halfed each time is called with same size for each but new coordinates for their centres
  node->center[0] = x; node->center[1] = y;
  
  // Initialize all children as NULL 
  node->NE = NULL; 
  node->SE = NULL;
  node->SW = NULL;
  node->NW = NULL;


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
    if(nd->NE != NULL)
        printf("(NE:%d)",nd->NE->data);
    if(nd->SE != NULL)
        printf("(SE:%d)",nd->SE->data);
    if(nd->SW != NULL)
        printf("(SW:%d)",nd->SW->data);
    if(nd->NW != NULL)
        printf("(NW:%d)",nd->NW->data);
    printf("\n");
 
    display_tree(nd->NE);
    display_tree(nd->SE);
    display_tree(nd->SW);
    display_tree(nd->NW);
}

//Deallocate memory for all nodes:  
void dispose(struct node* root)
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


int count(struct node* nd, double (*A)[2], int N_PARTICLES, int* quadrant_){
    
    if (nd==NULL) {
        return 0;
    }

    quadrant_[0]=0; quadrant_[1]=0; quadrant_[2]=0; quadrant_[3]=0; 
    
    printf("Count call\n");

    int total_count= 0;
    for(int i=0; i<N_PARTICLES; i++){
        if(A[i][0] < (nd->center[0]+nd->s) && A[i][1] < (nd->center[0]+nd->s)){
            total_count++;
            if(A[i][0]>= nd->center[0] && A[i][1]>= nd->center[1]){quadrant_[0]++;}
            if(A[i][0]>= nd->center[0] && A[i][1]<= nd->center[1]){quadrant_[1]++;}
            if(A[i][0]<= nd->center[0] && A[i][1]<= nd->center[1]){quadrant_[2]++;}
            if(A[i][0]<= nd->center[0] && A[i][1]>= nd->center[1]){quadrant_[3]++;}
        }  
        
    }
    printf("Total number of particles: %i\n", total_count);

    return total_count;


}

void subdivide(struct node* nd, double (*A)[2], int N_PARTICLES, int* quadrant_){
    
    
    printf("Subdivide call\n");
    int t = count(nd, A, N_PARTICLES, quadrant_);
    int twig=0;
    int leaf=0;
    
    if (t>=2) {
        if(quadrant_[0]>=2){
            twig--;
            nd->NE = newNode(nd->data+twig, nd->s/2, nd->center[0]+(nd->s/4), nd->center[0]+(nd->s/4));
            subdivide(nd->NE, A, N_PARTICLES, quadrant_);
            
        } 
        else {
            if (quadrant_[0]=1) {
                leaf++;
                nd->NE = newNode(leaf-nd->data, nd->s/2, nd->center[0]+(nd->s/4), nd->center[0]+(nd->s/4) );
            }
            
        }
        
        
        
        if(quadrant_[1]>=2){
            twig--;
            nd->SE = newNode(nd->data+twig, nd->s/2, nd->center[0]+(nd->s/4), nd->center[0]-(nd->s/4));
            subdivide(nd->SE, A, N_PARTICLES, quadrant_);
        }
        else {
            if (quadrant_[1]=1) {
                leaf++;
                nd->SE = newNode(leaf-nd->data, nd->s/2, nd->center[0]+(nd->s/4), nd->center[0]-(nd->s/4));
            }
            
        }        
        
        if(quadrant_[2]>=2){
            twig--;
            nd->SW = newNode(nd->data+twig, nd->s/2, nd->center[0]-(nd->s/4), nd->center[0]-(nd->s/4));
            //subdivide(nd->SW, A, N_PARTICLES, quadrant_);
        }
        else {
            if (quadrant_[2]=1) {
                leaf++;
                nd->SW = newNode(leaf-nd->data, nd->s/2, nd->center[0]-(nd->s/4), nd->center[0]-(nd->s/4));
            }
            
        }
        
        if(quadrant_[3]>=2){
            twig--;
            nd->NW = newNode(nd->data+twig, nd->s/2, nd->center[0]-(nd->s/4), nd->center[0]+(nd->s/4));
            subdivide(nd->NW, A, N_PARTICLES, quadrant_);
        }
        else {
            if (quadrant_[3]=1) {
                leaf++;
                nd->NW = newNode(leaf-nd->data, nd->s/2, nd->center[0]-(nd->s/4), nd->center[0]+(nd->s/4));
            }
            
        }

  
        

            
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
    char x[2]={'x', 'y'};

    for (int i=0; i < N_PARTICLES; i++){
        printf("Particle [%i] with ", i);
        for(int j=0; j < N_DIMENSIONS; j++){
            A[i][j] = 20 * ( (double) rand() / (double) RAND_MAX ) - 10; //-10, 10
            printf("%c:[%f] ", x[j],  A[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N_PARTICLES; i++){
        Mass[i] = 5 * ((double) rand() / (double) RAND_MAX ); //1,5
        Charge[i] = 10 * ((double) rand() / (double) RAND_MAX ) - 5;//-5, 5
        printf("Particle [%i] : Mass [%f], Charge [%f] \n", i, Mass[i], Charge[i]);
    }


    int* quadrant_ = malloc(sizeof(int)* 4);
    
    /*create root*/ 
    
    struct node *root = newNode(0, 11, 0, 0); //Size of s=11 and pint of reference being (0,0) equiv. to (x_root, y_root)  
    printf("Root square size is: %f\n", root->s);

    subdivide(root, A, N_PARTICLES, quadrant_);

    display_tree(root);

    /* remove the whole tree */
    dispose(root);
    free(quadrant_);
    free(A); //Free memory
    free(Mass);
    free(V);  
    free(F);
    free(Charge);
    printf("Released memory succesfuly\n");

    return 0; 
}