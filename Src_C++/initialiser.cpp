/*Initialising the Array (A) of our particles and dimensions,
later including charge and masses*/    

#include <iostream>
#include <cmath>
// #include <cstdlib>
//#include <time.h>

#include "Functions.h"


void initialiser(int seed, int N_PARTICLES, std::vector<Body> *Bodies, std::vector<Point> *Forces){ 

/*Loop through the array and initialise the position with random values between */ 

srand(seed); //Seed time for random value generation 

  //Initialising the matrices
  double rx, ry; //rz;
  double mass, charge;


  for(int i=0; i<N_PARTICLES; i++){
    
    mass = (5 * ((double) rand() / (double) RAND_MAX )); // 0-5
    charge = (10 * ((double) rand() / (double) RAND_MAX )-5); // -5, 5
  
    (*Bodies)[i] = Body(mass, charge);

    (*Bodies)[i].setX((100 * ((double) rand() / (double) RAND_MAX )) - 50);
    (*Bodies)[i].setY((100 * ((double) rand() / (double) RAND_MAX )) - 50);
    //(*Bodies)[i].setZ((10 * ((double) rand() / (double) RAND_MAX )));

    (*Forces)[i].setX(0);
    (*Forces)[i].setY(0);
    //(*Forces)[i].setZ(0);

    std::cout << "Body position is: " << (*Bodies)[i].x << " " <<  (*Bodies)[i].y << std::endl;
    //" " << (*Bodies)[i].z << std::endl;
    std::cout << "Mass is: " << (*Bodies)[i].mass <<" Charge is: "<< 
    (*Bodies)[i].charge << std::endl;
  }
}
