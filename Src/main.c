#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Functions.h"

int main()
{
  ///Number of Particles & Number of Dimensions the particles reside in
  int N_PARTICLES;
  int N_DIMENSIONS = 2;
  clock_t start, end;
  char term;
  clock_t ts, te;

  //Commenting for now for automatic input for the plot
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
  int seed = 1;
  
  printf("Seed value?\n");
  if (scanf("%d%c", &seed, &term) != 2 || term != '\n') {
    printf("Failure: Not an integer. Try again\n");
    exit(-1);
  } 



  double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //Dynamically allocate memory for Array-
  double (*Velocity)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));
  double *Mass = malloc(sizeof(double) * N_PARTICLES); //- for memory
  double *Charge = malloc(sizeof(double) * N_PARTICLES);
  double *V = malloc(sizeof(double) * N_PARTICLES); //- for Potentials
  double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //- for Forces


  printf("-----\n");

  initialiser(N_PARTICLES, N_DIMENSIONS, A, F, Velocity, Mass, Charge, seed); //Initialise the Array A of dimensions per particle and their respective Masses- 
  //-( will be charges in the future)
  printf("-----\n");
  
  double duration;
  

  start = clock(); //start timer
  ppmodel(&N_PARTICLES, &N_DIMENSIONS, V, F, A, Mass, Charge); //Model
  end = clock(); //end timer
  duration = (double)(end-start)/CLOCKS_PER_SEC;  
  
  printf("Time elapsed is: %f (s)\n", duration); //To see the duration on the calculation model only
  char c; // Boolean char to check for saving
  printf("Do you want to save the data? Y/n \n");
  scanf("%c", &c);
      
  if(c=='Y'){
    double tstart, tend;
    double dt;
    printf("For what times?\n");
    printf("t_start?\n");
    scanf("%lf\n", &tstart);
    printf("t_end?\n");
    scanf("%lf\n", &tend);
    printf("Timestep dt? \n");
    scanf("%lf", &dt);
    
    printf("Calculating for timerange: [%f,%f]\n", tstart, tend);
    double Time[2] = {tstart, tend};
    printf("Saving data...\n");
    // leapfrog(&N_PARTICLES, &N_DIMENSIONS, Mass, Charge, A, Velocity, F, Time, &dt);
    printf("Done\n");
  } else
  {
      printf("Continuing\n");   
  }
  free(A); //Free memory
  free(Velocity);
  free(F);
  free(Mass);
  free(V);  
  free(Charge);
  
  
  printf("Released the memory succesfully\n");  

  printf("Program took %f\n", duration);

  return 0;
}

int type_Data(int* N, double* Time, int length, double* sd){
  
  FILE * f; 
  f = fopen("/home/albes/Desktop/plot.txt", "w"); /* open the file for writing*/

  /* write 10 lines of text into the file stream*/    
  fprintf(f, "N_PARTICLES,TIME,SD\n");

  for(int i = 0; i < length;i++){
      fprintf (f, "%d,%f,%f\n", N[i], Time[i], sd[i]);
  }

  /* close the file*/  
  fclose (f);
  return 0;
}

int reset(int particles, int dimensions, double* V, double (*F)[dimensions]){

  for(int i=0; i<particles; i++){
    V[i]=0;
  }

  for(int j=0; j<particles; j++){
    for(int i=0; i<dimensions; i++){
      F[j][i]=0;
    }
  }

  return 0;
}
 