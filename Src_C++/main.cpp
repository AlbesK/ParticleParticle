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

  int N_PARTICLES = 4; int N_DIMENSIONS = 3; int seed=1; 



  
  //Pointers and their initialization
  std::vector< std::vector<double> > *Matrix;
  std::vector<double> *Mass;
  std::vector<double> *Charge; 
  
  std::vector<Body> *Bodies;
  Bodies = new std::vector<Body>(N_PARTICLES);

  Matrix = new std::vector< std::vector<double> >(N_PARTICLES, std::vector<double>(N_DIMENSIONS));
  Mass = new std::vector<double>(N_PARTICLES);
  Charge = new std::vector<double>(N_PARTICLES);

  srand(seed); //Seed time for random value generation 

  //Initialising the matrices
  double rx, ry, rz;
  double mass, charge;
  Body b;

  for(int i=0; i<N_PARTICLES; i++){
    
     b.setX(10 * ( (double) rand() / (double) RAND_MAX ));
     b.setY(10 * ( (double) rand() / (double) RAND_MAX ));
     b.setZ(10 * ( (double) rand() / (double) RAND_MAX ));

     mass = (5 * ((double) rand() / (double) RAND_MAX ));
     charge = (10 * ((double) rand() / (double) RAND_MAX )-5);
    
     b = (mass, charge);

     (*Bodies)[i] = b; 

     std::cout << "Body position is: " << (*Bodies)[i].x << " " <<  (*Bodies)[i].y << " " << (*Bodies)[i].z <<std::endl;
  }

  for (int i=0; i < N_PARTICLES; i++){
    std::cout << "Matrix Position is: " ;
    for(int j=0; j < N_DIMENSIONS; j++){

      (*Matrix)[i][j] = (10 * ( (double) rand() / (double) RAND_MAX ));
      std::cout << (*Matrix)[i][j] << " ";
    
    } 
    std::cout << std::endl;
  }

  

  for (int i = 0; i < N_PARTICLES; i++){
    
    (*Mass)[i] = (5 * ((double) rand() / (double) RAND_MAX ));
    (*Charge)[i] = (10 * ((double) rand() / (double) RAND_MAX )-5);
    std::cout << "Mass is " << i << (*Mass)[i] << std::endl;
    std::cout << "Charge is " << i << (*Charge)[i] << std::endl;
    

  }

  //Free Memory
  delete  Matrix; delete  Mass; delete  Charge; delete  Bodies;

}