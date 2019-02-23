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
    compare two integers
*/
int compare(int left,int right)
{
    if(left > right)
        return 1;
    if(left < right)
        return -1;
    return 0;
}
	

/*
    Recursively display tree or subtree
*/
void display_tree(struct node* nd)
{
    if (nd == NULL)
        return;
    /* display node data */
    printf(" %*c(%d) \n %*c[%f, %f] \n %*c[%f]\n\n",50, ' ', nd->data, 42,' ', nd->center[0], nd->center[1], 47, ' ', nd->s);
    
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
//New functions

void subdivide(struct node* nd, double (*A)[2], int N_PARTICLES, int* quadrant_){
    
    
    if(nd == NULL){
        return;
    }
    
    //printf("Subdivide call\n");
    int twig=0;
    
    twig--;
    nd->NE = newNode(nd->data+twig, nd->s/2, nd->center[0]+nd->s/4, nd->center[0]+nd->s/4);
    nd->NE->parent = nd->data;
    
    twig--;
    nd->SE = newNode(nd->data+twig, nd->s/2, nd->center[0]+nd->s/4, nd->center[0]-nd->s/4);
    nd->SE->parent = nd->data;
    
    twig--;
    nd->SW = newNode(nd->data+twig, nd->s/2, nd->center[0]-nd->s/4, nd->center[0]-nd->s/4);
    nd->SW->parent = nd->data;
    
    twig--;
    nd->NW = newNode(nd->data+twig, nd->s/2, nd->center[0]-nd->s/4, nd->center[0]+nd->s/4); 
    nd->NW->parent = nd->data;
    

}


int count(struct node* nd, double (*A)[2], int N_PARTICLES, int* quadrant_){
    
    if (nd==NULL) {
        return 0;
    }

    quadrant_[0]=0; quadrant_[1]=0; quadrant_[2]=0; quadrant_[3]=0; 
    
    //printf("Count call\n");
    
    int total_count= 0;
    for(int i=0; i<N_PARTICLES; i++){
        if(A[i][0] < (nd->center[0]+nd->s) && 
        A[i][0] > (nd->center[0]-nd->s) && 
        A[i][1] < (nd->center[1]+nd->s) &&
        A[i][1] > (nd->center[1]-nd->s))
        {
            total_count++;
        }  
        
    }
    //printf("Total number of particles: %i\n", total_count);

    return total_count;


}



/*
    search for a specific key
*/
struct node* Search(struct node* root, int data) {
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

    int N_DIMENSIONS = 2;
    int N_PARTICLES;
    char term;
    clock_t ts, te;
    printf("How many particles?\n");
      if (scanf("%d%c", &N_PARTICLES, &term) != 2 || term != '\n') {
        printf("Failure: Not an integer. Try again\n");
        exit(-1);
      } 
    //Physical_Properties_Array[Particles Position][Masses][Charges][..etc..] Perhaps better for all of these pointers.  
    double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));
    double *V = malloc(sizeof(double) * N_PARTICLES );
    double *Mass = malloc(sizeof(double) * N_PARTICLES);
    double *Charge = malloc(sizeof(double) * N_PARTICLES);
    double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));

    //Initialise values:
    char x[2]={'x', 'y'};

    for (int i=0; i < N_PARTICLES; i++){
        //printf("Particle [%i] with ", i);
        for(int j=0; j < N_DIMENSIONS; j++){
            A[i][j] = 20 * ( (double) rand() / (double) RAND_MAX ) - 10; //-10, 10
            //printf("%c:[%f] ", x[j],  A[i][j]);
        }
        //printf("\n");
    }

    for (int i = 0; i < N_PARTICLES; i++){
        Mass[i] = 5 * ((double) rand() / (double) RAND_MAX ); //1,5
        Charge[i] = 10 * ((double) rand() / (double) RAND_MAX ) - 5;//-5, 5
        //printf("Particle [%i] : Mass [%f], Charge [%f] \n", i, Mass[i], Charge[i]);
    }


    int* quadrant_ = malloc(sizeof(int)* 4);
    
    /*create root*/ 
    
    struct node *root = newNode(0, 11, 0, 0); //Size of s=11 and pint of reference being (0,0) equiv. to (x_root, y_root)  
    printf("Root square size is: %f\n", root->s);
    
    void check(struct node* root, double (*A)[2], int N_PARTICLES, int* quadrant_ ){
        
        
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
    ts = clock();
    check(root, A, N_PARTICLES, quadrant_);
    te = clock();
    double d = (double)(te-ts)/CLOCKS_PER_SEC;
    
    

    //display_tree(root);

    /* remove the whole tree */
    dispose(root);
    free(quadrant_);
    free(A); //Free memory
    free(Mass);
    free(V);  
    free(F);
    free(Charge);
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
*/