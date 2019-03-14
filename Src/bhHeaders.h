#ifndef BH_HEADERS
#define BH_HEADERS

#include<stdbool.h>

struct point{
    double x;
    double y;
};
struct body{
    double mass;
    double charge;
    struct point pos;
};
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

struct linkedList
{
  struct quad* data;
  struct linkedList* next;

};

void enqueue(struct quad* nd);
void dequeue();
bool queue_empty();

struct linkedList* begin;
struct linkedList* end;

struct quad* newNode(int data, double s, double x, double y);
void newBody(struct quad* nd, struct point pos, double mass, double charge);
void display_tree(struct quad* nd);
void deconstruct_tree(struct quad* root);
void subdivide(struct quad* nd, int* track);
bool contains(struct quad* nd, struct point p);
int insert(struct quad* nd, struct body* b, int *index);
int count(struct quad* nd, struct body* bodies, int* N_PARTICLES, int* track);
struct quad* Search(struct quad* root, int data);
void levelorder(struct quad* n);
double mag(double* d);
void difference(struct point* p1, struct point* p2, double *d);
void force_summation(struct quad* nd, struct body* bodies, struct point* Forces, int* N_PARTICLES);

void xyt_data_particles(struct body* bodies, int* N_PARTICLES, double t);
void printdata(struct quad* nd, FILE* f);
void xy_trees(struct quad* nd);

#endif