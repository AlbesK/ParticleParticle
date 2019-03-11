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
  clock_t ts, te;
  int l=0;
  //New code for writing to output file:
  //printf("The power with base 4?\n");
  //scanf("%d", &l); 
  

  // int N[l-1]; N[0]=0; 
  // double Time[l-1]; Time[0]=0;
  // int type_Data(int*, double*, int length, double* sd);
  // double calculateSD(double data[]);
  
  // int reset(int, int dimensions, double*, double (*F)[dimensions]);
  // double sd[l-1]; sd[0]=0;
  //end of new code for file writing
  // double data[4];
  // ts = clock();


  //for(int i=1; i<l; i++){ //New Loop to save the data to be plotted
  

    
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
      double *Mass = malloc(sizeof(double) * N_PARTICLES); //- for memory
      double *Charge = malloc(sizeof(double) * N_PARTICLES);
      double *V = malloc(sizeof(double) * N_PARTICLES); //- for Potentials
      double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS])); //- for Forces


      printf("-----\n");


      initialiser(N_PARTICLES, N_DIMENSIONS, A, Mass, Charge, seed); //Initialise the Array A of dimensions per particle and their respective Masses- 
      //-( will be charges in the future)
      printf("-----\n");
      
      double duration;
      
      //for(int j=0; j<4; j++){
        start = clock(); //start timer
        ppmodel(&N_PARTICLES, &N_DIMENSIONS, V, F, A, Mass, Charge); //Model
        end = clock(); //end timer
        duration = (double)(end-start)/CLOCKS_PER_SEC;
        //data[j] = duration;
        //reset(N_PARTICLES, N_DIMENSIONS, V, F);
      // }
      
      //sd[i], duration = calculateSD(data);
      
      printf("Time elapsed is: %f (s)\n", duration); //To see the duration on the calculation model only

      free(A); //Free memory
      free(F);
      free(Mass);
      free(V);  
      free(Charge);
      
      
      printf("Released the memory succesfully\n");  
    
    
    // N[i]=N_PARTICLES;
    // Time[i]=duration;

  //}
  // te = clock();
  // double d = (double)(te-ts)/CLOCKS_PER_SEC;
  printf("Program took %f\n", duration);
  //type_Data(N, Time, l, sd);
  return 0;
}

double calculateSD(double data[])
{
    double sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i=0; i<4; ++i)
    {
        sum += data[i];
    }

    mean = sum/4;

    for(i=0; i<4; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/3), mean;
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
