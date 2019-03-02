#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#define COUNT 12

  //Object approach
class Point {
  public:
  double x, y;

  Point(){this->x=0; this->y=0;}
  Point(double x, double y){this->x=x; this->y=y;}

  ~Point(){};
   
};

class Body {
  public:
  
  Point pos;
  double mass;   //Mass
  double charge;  //Charge
  
  Body(){}

  Body(double m, double c, Point pos)
  { //Default Constructor
    
    this->pos = pos;
    this->mass = m;
    this->charge = c;
    //std::cout <<"Body constructed\n";
  }

  ~Body(){}//std::cout <<"Body destructed\n";}; //Destructor


};

class Quad {
    
    public:

    Point r; //Center 
    double s; //Size
    int data; //Key data
    int capacity=1; //Capacity for the node

    Body *b;
    
    //Children
    Quad *NE;
    Quad *SE;
    Quad *SW;
    Quad *NW;
    
    

    Quad() 
    { 
        this->r = Point();
        this->s = 110;
        this->b = NULL;
        this->NE  = NULL; 
        this->SE = NULL; 
        this->SW  = NULL; 
        this->NW = NULL; 
        this->data = 0;
    } 
    Quad(Point r, double s) 
    { 
        this->b = NULL;
        NE = NULL; 
        SE = NULL; 
        SW  = NULL; 
        NW = NULL; 
        this->r = r;
        this->s = s;
    } 

    ~Quad(){}//std::cout << "Class Destructed\n";} 
    void insert(Body*, int index); 
    Body* search(Point); 
    bool inBoundary(Point); 

    
};

// Insert a body into the quadtree 
void Quad::insert(Body *body, int index) 
{ 
    if (body == NULL) 
        return; 
  
    // Current quad cannot contain it 
    if (!inBoundary(body->pos)) 
        return; 
  
    // We are at a quad of unit area 
    // We cannot subdivide this quad further 
    if (abs((r.x+s/2) - (r.x-s/2)) <= 1 && 
        abs((r.y+s/2) - (r.y-s/2)) <= 1) 
    { 
    if (b == NULL) 
        b = body; 
        this->data = index;
        return; 
    } 
  
    if (body->pos.x < this->r.x) 
    { 
        // Indicates NW 
        if (body->pos.y > r.y) 
        { 
            if (this->NW == NULL){ 
                this->NW = new Quad(Point(r.x-s/4, r.y+s/4), s/2);
            
            }
            this->NW->insert(body, index); 
        } 
  
        // Indicates SW 
        else
        { 
            if (SW == NULL){ 
                SW = new Quad(Point(r.x-s/4, r.y-s/4), s/2);

            } 
            SW->insert(body, index); 
            
        } 
    } 
    else
    { 
        // Indicates NE 
        if (body->pos.y > r.y) 
        { 
            if (NE == NULL){ 
                NE = new Quad(Point(r.x+s/4, r.y+s/4), s/2);
            }
            NE->insert(body, index); 
            
        } 
  
        // Indicates SE 
        else
        { 
            if (SE == NULL){ 
                SE = new Quad(Point(r.x+s/4, r.y-s/4), s/2);
                
            } 
            SE->insert(body, index); 
        } 
    } 
} 
  
// Find a body in a quadtree 
Body* Quad::search(Point p) 
{ 
    // Current quad cannot contain it 
    if (!inBoundary(p)) 
        return NULL; 
  
    // We are at a quad of unit length 
    // We cannot subdivide this quad further 
    if (b != NULL) 
        return b; 
  
    if (p.x < r.x) 
    { 
        // Indicates NW 
        if (p.y > r.y) 
        { 
            if (NW == NULL) 
                return NULL; 
            return NW->search(p); 
        } 
  
        // Indicates SW
        else
        { 
            if (SW == NULL) 
                return NULL; 
            return SW->search(p); 
        } 
    } 
    else
    { 
        // Indicates NE 
        if (p.y > r.y) 
        { 
            if (NE == NULL) 
                return NULL; 
            return NE->search(p); 
        } 
  
        // Indicates SE 
        else
        { 
            if (SE == NULL) 
                return NULL; 
            return SE->search(p); 
        } 
    } 
}; 



// Check if current quadtree contains the point 
bool Quad::inBoundary(Point p) 
{ 
    return (p.x < this->r.x+this->s/2 && 
            p.x > this->r.x-this->s/2 &&
            p.y < this->r.y+this->s/2 &&
            p.y > this->r.y-this->s/2 ); 
}


//Deallocate memory for all nodes:  
void destroy(Quad* root)
{
    if(root != NULL)
    {
        
        destroy(root->NE);
        destroy(root->SE);
        destroy(root->SW);
        destroy(root->NW);

        delete root;
    }
}

int type_Data(int* N, double* T, int si){
  
  FILE * f; 
  f = fopen("/home/albes/Desktop/log.txt", "w"); /* open the file for writing*/

  /* write 10 lines of text into the file stream*/    
  fprintf(f, "N_PARTICLES,TIME\n");

  for(int i = 0; i < si;i++){
      fprintf (f, "%d,%f\n", N[i], T[i]);
  }

  /* close the file*/  
  fclose (f);
  return 0;
}

/*
    Recursively display tree or subtree
*/
void display_tree(Quad *nd)
{
    if (nd == NULL)
        return;
    /* display quad data */
    printf(" %*c(%d) \n %*c[%f, %f] \n %*c[%f]\n\n",50, ' ', nd->data, 42,' ', nd->r.x, nd->r.y, 47, ' ', nd->s);
    
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


int main()
{
    // Particle Number and Dimensions

    clock_t start, end;
   

    int N_PARTICLES; int N_DIMENSIONS = 2; int seed=1; 
    //New code for file writting
    // int si = 9;
    // int N[si]; double T[si];
    // int type_Data(int*, double*, int);

    //for(int i=0; i<si; i++){
    printf("How many particles?\n");
    scanf("%d", &N_PARTICLES);
    
    //N_PARTICLES = pow(10,i);
    
    //Pointers and their initialization

    std::vector<Body> *Bodies;
    Bodies = new std::vector<Body>(N_PARTICLES);


    srand(seed); //Seed time for random value generation 

    //Initialising the matrices
    double rx, ry;
    double mass, charge;

    for(int i=0; i<N_PARTICLES; i++){
        
    mass = (5 * ((double) rand() / (double) RAND_MAX ));
    charge = (10 * ((double) rand() / (double) RAND_MAX )-5);


    (*Bodies)[i] = Body(mass, charge, Point((100 * ((double) rand() / (double) RAND_MAX )-50), (100 * ((double) rand() / (double) RAND_MAX )-50)));

    //std::cout << "Body position is: [" << (*Bodies)[i].pos.x << "] [" <<  (*Bodies)[i].pos.y << "] " << std::endl;
    //std::cout << "Mass is: " << (*Bodies)[i].mass <<" Charge is: "<< 
    //(*Bodies)[i].charge << std::endl;
    }

    Quad* root = new Quad();

    start = clock();
    for(int i=0; i<N_PARTICLES; i++){
        root->insert(&(*Bodies)[i], i+1);
    } 
    end = clock(); //end timer

    //print_tree(root,0);

    display_tree(root);
    std::cout << "Body is at point: " << root->search((*Bodies)[1].pos) << std::endl;
    //Free Memory
    delete Bodies; 
    destroy(root);
    
    std::cout << "Pointers deleted succesfuly" << std::endl;

    double duration = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time elapsed is: %f (s)\n", duration);
    //N[i]=N_PARTICLES;
    //T[i]=duration;
    //}
    //type_Data(N, T, si);

}

