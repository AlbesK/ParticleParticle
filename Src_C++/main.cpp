#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
//#include "Functions.h"
//ios::sync_with_stdio(false);

int main()
{
  // Particle Number and Dimensions

  int N_PARTICLES = 4; int N_DIMENSIONS = 3; int seed=1; 
  
  //Pointers and their initialization
  std::vector< std::vector<double> > *Matrix;
  std::vector<double> *Mass;
  std::vector<double> *Charge; 
  
  Matrix = new std::vector< std::vector<double> >(N_PARTICLES, std::vector<double>(N_DIMENSIONS));
  Mass = new std::vector<double>(N_PARTICLES);
  Charge = new std::vector<double>(N_PARTICLES);

  //Creating references
  std::vector< std::vector<double> > &Matrix_ref = *Matrix;
  std::vector<double> &Mass_ref = *Mass;
  std::vector<double> &Charge_ref = *Charge;

  srand(seed); //Seed time for random value generation 


  for (int i=0; i < N_PARTICLES; i++){
    for(int j=0; j < N_DIMENSIONS; j++){
      //Matrix_ref[i][j] = (10 * ( (double) rand() / (double) RAND_MAX ));
      //std::cout << Matrix_ref[i][j] << std::endl;
      (*Matrix)[i][j] = (10 * ( (double) rand() / (double) RAND_MAX ));
      std::cout << (*Matrix)[i][j] << std::endl;
    } 
  }

  for (int i = 0; i < N_PARTICLES; i++){
    //Mass_ref[i] = (5 * ((double) rand() / (double) RAND_MAX ));
    //Charge_ref[i] = (10 * ((double) rand() / (double) RAND_MAX ) - 5);
    //std::cout << "Mass is" << i << Mass_ref[i] << std::endl;
    //std::cout << "Charge is" << i << Charge_ref[i] << std::endl;
    (*Mass)[i] = (5 * ((double) rand() / (double) RAND_MAX ));
    (*Charge)[i] = (10 * ((double) rand() / (double) RAND_MAX )-5);
    std::cout << "Mass is " << i << (*Mass)[i] << std::endl;
    std::cout << "Charge is " << i << (*Charge)[i] << std::endl;
    

  }

  std::cout << "Check" << std::endl;
  std::cout << "Now sizes are: For Matrix:" << Matrix->size() << " Then for Mass:" << Mass->size() << " Finally for Charge:" << Charge->size() << std::endl;
  delete Matrix; delete Mass; delete Charge;

}