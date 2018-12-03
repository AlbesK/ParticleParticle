#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Functions.h"
using namespace std;
ios::sync_with_stdio(false);

int main()
{
  ///Number of Particles & Number of Dimensions the particles reside in
  int N_PARTICLES;
  int N_DIMENSIONS = 3;
  clock_t start, end;
  char term;
  cout << "How many particles?\n" << endl;
  if ((cin >> "%d%c", &N_PARTICLES, &term) != 2 || term != '\n') {//Stack overflow bit https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
    printf("Failure: Not an integer. Try again\n");
    exit(-1);
  } 

  //Seed input to check values with trial of OpenMP
  int seed;

  cin >> "Seed value?\n" << endl;
  if ((cin >> "%d%c", &seed, &term) != 2 || term != '\n') {
    cout << "Failure: Not an integer. Try again\n" << endl;
    exit(-1);
  } 

  cout << "Calculating\n" << endl;
  if (N_PARTICLES < 2) {
    cout << "Insufficent number of particles %i\n", N_PARTICLES << endl;
    exit(-1);
  }
  
  double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //Dynamically allocate memory for Array-
  double *Mass = malloc(sizeof(double) * N_PARTICLES); //- for memory
  double *Charge = malloc(sizeof(double) * N_PARTICLES);
  double *V = malloc(sizeof(double) * N_PARTICLES); //- for Potentials
  double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //- for Forces

  
  cout << "-----\n" << endl;
  

  initialiser(N_PARTICLES, N_DIMENSIONS, A, Mass, Charge, seed); //Initialise the Array A of dimensions per particle and their respective Masses- 
  //-( will be charges in the future)
  cout << "-----\n" << endl;
   
  start = clock(); //start timer
    
  ppmodel(N_PARTICLES, N_DIMENSIONS, V, F, A, Mass, Charge); //Model
    
  end = clock(); //end timer
    
  double duration = (double)(end-start)/CLOCKS_PER_SEC;
  cout << "Time elapsed is: %f (s)\n", duration <<endl; //To see the duration on the calculation model only
    
  //#include "printer.c" //Print file.c
    
  free(A); //Free memory
  free(Mass);
  free(V);  
  free(F);
  free(Charge);
  cout << "Released the memory succesfully\n" << endl;  
  return 0;
}