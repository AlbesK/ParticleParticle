#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
//#include "Functions.h"
//ios::sync_with_stdio(false);

int main()
{
  // Particle Number and Dimensions

  //Object approach
  class Body {
    private:

    std::vector<double> position{2}; 
    double mass;
    double charge;

    public:

    Body(double x = 1.0, double y = 1.0, double z = 1.0, double m = 1.0, double c = -1.0)
    { //Default Constructor
      this->position[0] = x;
      this->position[1] = y;
      this->position[2] = z;
      this->mass = m;
      this->charge = c;
    }

    //~Body();//Destructor

    double getPosition(){
      for (int i=0; i< 2; ++i){
        std::cout << position[i] << " ";
      }
    }

    double getMass(){
      return this->mass;
    }

    double getCharge(){
      return this->charge;
    }

    int getSize(){
      return position.size();
    }



  };

  Body b1;

  int N_PARTICLES = 4; int N_DIMENSIONS = 3; int seed=1; 
  
  //Pointers and their initialization
  std::vector< std::vector<double> > *Matrix;
  std::vector<double> *Mass;
  std::vector<double> *Charge; 
  
  Matrix = new std::vector< std::vector<double> >(N_PARTICLES, std::vector<double>(N_DIMENSIONS));
  Mass = new std::vector<double>(N_PARTICLES);
  Charge = new std::vector<double>(N_PARTICLES);

  srand(seed); //Seed time for random value generation 

  //Initialising the matrices

  for (int i=0; i < N_PARTICLES; i++){
    for(int j=0; j < N_DIMENSIONS; j++){

      (*Matrix)[i][j] = (10 * ( (double) rand() / (double) RAND_MAX ));
      std::cout << (*Matrix)[i][j] << std::endl;
    
    } 
  }

  for (int i = 0; i < N_PARTICLES; i++){
    
    (*Mass)[i] = (5 * ((double) rand() / (double) RAND_MAX ));
    (*Charge)[i] = (10 * ((double) rand() / (double) RAND_MAX )-5);
    std::cout << "Mass is " << i << (*Mass)[i] << std::endl;
    std::cout << "Charge is " << i << (*Charge)[i] << std::endl;
    

  }
  //Checking Purposes

  std::cout << "Check" << std::endl;
  std::cout << "Now sizes are: For Matrix:" << Matrix->size() << " Then for Mass:" << Mass->size() << " Finally for Charge:" 
  << Charge->size() << std::endl;
  std::cout << " Body default parameters are: " << b1.getPosition() << " Mass is: "
  << b1.getMass() << "Charge is: " << b1.getCharge() << std::endl;

  std::cout << b1.getSize() << std::endl;


  //Free Memory
  delete Matrix; delete Mass; delete Charge;

}