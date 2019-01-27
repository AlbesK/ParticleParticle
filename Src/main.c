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
  clock_t start, end;
  char term;

  //New code for writing to output file:

  int N[15];
  double Time[15];
  int type_Data(int*, double*);

  //end of new code for file writing

  for(int i=0; i<15; i++){

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

  //Seed input to check values with trial of OpenMP
  int seed;

  printf("Seed value?\n");
  if (scanf("%d%c", &seed, &term) != 2 || term != '\n') {
    printf("Failure: Not an integer. Try again\n");
    exit(-1);
  } 


  
  double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //Dynamically allocate memory for Array-
  double *Mass = malloc(sizeof(double) * N_PARTICLES); //- for memory
  double *Charge = malloc(sizeof(double) * N_PARTICLES);
  double *V = malloc(sizeof(double) * N_PARTICLES); //- for Potentials
  double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //- for Forces

  
  printf("-----\n");
  

  initialiser(N_PARTICLES, N_DIMENSIONS, A, Mass, Charge, seed); //Initialise the Array A of dimensions per particle and their respective Masses- 
  //-( will be charges in the future)
  printf("-----\n");
   
  start = clock(); //start timer
    
  ppmodel(N_PARTICLES, N_DIMENSIONS, V, F, A, Mass, Charge); //Model
    
  end = clock(); //end timer
    
  double duration = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Time elapsed is: %f (s)\n", duration); //To see the duration on the calculation model only
    
  //#include "printer.c" //Print file.c
  N[i]=N_PARTICLES;
  Time[i]=duration;

  

  free(A); //Free memory
  free(Mass);
  free(V);  
  free(F);
  free(Charge);
  printf("Released the memory succesfully\n");  
  }
  type_Data(N, Time);
  return 0;
}

int type_Data(int* N, double* Time){
  /* open the file for writing*/
  FILE * f; 
  f = fopen("/home/albes/Desktop/plot.txt", "w");
  int i;
  
  

  /* write 10 lines of text into the file stream*/
  fprintf(f, "N_PARTICLES,TIME\n");

  for(i = 0; i < 15;i++){
      fprintf (f, "%d,%f\n", N[i], Time[i]);
  }

  /* close the file*/  
  fclose (f);
  return 0;
}
