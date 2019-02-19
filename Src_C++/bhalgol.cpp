#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

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

    Body *b;
    
    //Children
    Quad *NE;
    Quad *SE;
    Quad *SW;
    Quad *NW;
    
    

    Quad() 
    { 
        this->r = Point();
        this->s = 11;
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
    void insert(Body*); 
    Body* search(Point); 
    bool inBoundary(Point); 

    
};

// Insert a body into the quadtree 
void Quad::insert(Body *body) 
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
        return; 
    } 
  
    if (body->pos.x < r.x) 
    { 
        // Indicates NW 
        if (body->pos.y > r.y) 
        { 
            if (NW == NULL) 
                NW = new Quad(Point(r.x-s/4, r.y+s/4), s/2); 
            NW->insert(body); 
        } 
  
        // Indicates SW 
        else
        { 
            if (SW == NULL) 
                SW = new Quad(Point(r.x-s/4, r.y-s/4), s/2); 
            SW->insert(body); 
        } 
    } 
    else
    { 
        // Indicates NE 
        if (body->pos.y > r.y) 
        { 
            if (NE == NULL) 
                NE = new Quad(Point(r.x+s/4, r.y+s/4), s/2);
            NE->insert(body); 
        } 
  
        // Indicates SE 
        else
        { 
            if (SE == NULL) 
                SE = new Quad(Point(r.x+s/4, r.y-s/4), s/2); 
            SE->insert(body); 
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

/*
    Recursively display tree or subtree
*/
void display_tree(Quad *nd)
{
    if (nd == NULL)
        return;
    /* display node data */
    printf("Quad Node at <%f, %f> Size [%f]\n", nd->r.x, nd->r.y, nd->s);
    if(nd->NE != NULL)
        printf("(NE:%d)  ",nd->NE->data);
    if(nd->SE != NULL)
        printf("(SE:%d)  ",nd->SE->data);
    if(nd->SW != NULL)
        printf("(SW:%d)  ",nd->SW->data);
    if(nd->NW != NULL)
        printf("(NW:%d)",nd->NW->data);
    printf("\n");
 
    display_tree(nd->NE);
    display_tree(nd->SE);
    display_tree(nd->SW);
    display_tree(nd->NW);
}

//Deallocate memory for all nodes:  
void dispose(Quad* root)
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



int main()
{
    // Particle Number and Dimensions

    clock_t start, end;
    start = clock(); //start timer

    int N_PARTICLES; int N_DIMENSIONS = 2; int seed=1; 

    printf("How many particles?\n");
    scanf("%d", &N_PARTICLES);
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


    (*Bodies)[i] = Body(mass, charge, Point((10 * ((double) rand() / (double) RAND_MAX )-5), (10 * ((double) rand() / (double) RAND_MAX )-5)));

    //std::cout << "Body position is: [" << (*Bodies)[i].pos.x << "] [" <<  (*Bodies)[i].pos.y << "] " << std::endl;
    //std::cout << "Mass is: " << (*Bodies)[i].mass <<" Charge is: "<< 
    //(*Bodies)[i].charge << std::endl;
    }

    Quad root(Point(0, 0), 11);

    for(int i=0; i<N_PARTICLES; i++){
        root.insert(&(*Bodies)[i]);
    } 

    //display_tree(&root);
    //dispose(&root);
    //Free Memory
    delete  Bodies; 
    
    std::cout << "Pointers deleted succesfuly" << std::endl;

    end = clock(); //end timer
    double duration = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time elapsed is: %f (s)\n", duration);

}