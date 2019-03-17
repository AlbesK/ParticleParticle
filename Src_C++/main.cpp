#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

#include "Functions.h"
    
int main()
{
  // Particle Number and Dimensions

  clock_t start, end;
  char term;
  start = clock(); //start timer

  int N_PARTICLES; int N_DIMENSIONS = 3; int seed=1;

  printf("How many particles?\n");
  if (scanf("%d%c", &N_PARTICLES, &term) != 2 || term != '\n') {//Stack overflow bit https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
    printf("Failure: Not an integer. Try again\n");
    exit(-1);
  } 

  printf("Calculating\n");
  if (N_PARTICLES < 2) {
    printf("Insufficent number of particles %i\n", N_PARTICLES);
    exit(-1);
  } 


  //Pointers and their initialization

  std::vector<Body> *Bodies;
  Bodies = new std::vector<Body>(N_PARTICLES);
  std::vector<Point> *Forces;
  Forces = new std::vector<Point>(N_PARTICLES);

  initialiser(seed, N_PARTICLES, Bodies, Forces);
  ppmodel(N_PARTICLES, Bodies, Forces);
  //Free Memory
  delete  Bodies;
  delete  Forces; 
  std::cout << "Pointers deleted succesfuly" << std::endl;

  end = clock(); //end timer
  double duration = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Time elapsed is: %f (s)\n", duration);

}