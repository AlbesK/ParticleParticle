#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Functions.h"

int main()
{
  ///Number of Particles & Number of Dimensions the particles reside in
  int N_PARTICLES;
  int N_DIMENSIONS = 3;
  int readin;
  clock_t start, end;

  printf("How many particles?\n");
  readin = scanf("%i", &N_PARTICLES);
  if (readin != 1) {
    printf("Particle number read failed\n");
    exit(-1);
  }

  printf("Calculating\n");
  if (N_PARTICLES < 2) {
    printf("Insufficent number of particles %i\n", N_PARTICLES);
    exit(-1);
  }
  
  double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //Dynamically allocate memory for Array-
  double *Mass = malloc(sizeof(double) * N_PARTICLES); //- for memory
  printf("Mass is allocated\n");
  double *V = malloc(sizeof(double) * N_PARTICLES); //- for Potentials
  printf("Potential is allocated, perhaps wrongly in the same position of pointer?\n");
  double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //- for Forces

  
  printf("-----\n");
  

  initialiser(N_PARTICLES, N_DIMENSIONS, A, Mass); //Initialise the Array A of dimensions per particle and their respective Masses- 
  //-( will be charges in the future)
  printf("-----\n");
   
  start = clock(); //start timer
    
  ppmodel(N_PARTICLES, N_DIMENSIONS, V, F, A, Mass); //Model
    
  end = clock(); //end timer
    
  double duration = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Time elapsed is: %f (s)\n", duration); //To see the duration on the calculation model only
    
  //#include "printer.c" //Print file.c
    
  free(A); //Free memory
  free(Mass);
  free(V);  
  free(F);
  printf("Released the memory succesfully\n");  
  return 0;
}
