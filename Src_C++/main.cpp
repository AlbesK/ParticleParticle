#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

//#include "Functions.h"
 
    

    
  
    
  
//ios::sync_with_stdio(false);

  //Object approach
class Point {
  public:
  double x, y, z;
  
  void setX(double x){
    this->x = x;
  }
  void setY(double y){
    this->y = y;
  }
  void setZ(double z){
    this->z = z;
  }

  ~Point(){};
  
};

class Body: public Point {
  public:
  
  double mass;   //Mass
  double charge;  //Charge
  
  

  Body(double m = 1.0, double c = -1.0)
  { //Default Constructor
    
    this->mass = m;
    this->charge = c;
  }

  ~Body(){}; //Destructor


};

  

int main()
{
  // Particle Number and Dimensions
  
  clock_t start, end;
  start = clock(); //start timer

  int N_PARTICLES = 4; int N_DIMENSIONS = 3; int seed=1; 




  
  //Pointers and their initialization
  
  std::vector<Body> *Bodies;
  Bodies = new std::vector<Body>(N_PARTICLES);


  srand(seed); //Seed time for random value generation 

  //Initialising the matrices
  double rx, ry, rz;
  double mass, charge;
  Body* b = new Body();

  for(int i=0; i<N_PARTICLES; i++){
     
     b->setX((10 * ((double) rand() / (double) RAND_MAX )));
     b->setY((10 * ((double) rand() / (double) RAND_MAX )));
     b->setZ((10 * ((double) rand() / (double) RAND_MAX )));

     mass = (5 * ((double) rand() / (double) RAND_MAX ));
     charge = (10 * ((double) rand() / (double) RAND_MAX )-5);
    
     b->mass = mass; b->charge = charge;

     (*Bodies)[i] = *b; 

     std::cout << "Body position is: " << (*Bodies)[i].x << " " <<  (*Bodies)[i].y << 
     " " << (*Bodies)[i].z << std::endl;
     std::cout << "Mass is: " << (*Bodies)[i].mass <<" Charge is: "<< 
     (*Bodies)[i].charge << std::endl;
  }


  //Free Memory
  delete  Bodies; delete b; 

  end = clock(); //end timer
  double duration = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Time elapsed is: %f (s)\n", duration);

}