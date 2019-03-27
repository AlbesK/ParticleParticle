/*Initialising the Array (A) of our particles and dimensions,
later including charge and masses*/    

#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#include "Functions.h"


void initialiser(int particles, int dimensions, double (*A)[dimensions], double (*F)[dimensions], double (*Vel)[dimensions], double* Mass, double* Charge, int seed ){ // i for particles, j for dimensions

/*Loop through the array and initialise the position with random values between */ 

srand(seed); //Seed time for random value generation 

for (int i=0; i < particles; i++){
  for(int j=0; j < dimensions; j++){
    A[i][j] = 100 *  (double) rand() / (double) RAND_MAX -50 ; //Random values between -100, 100
    Vel[i][j] = 2 * (double) rand() / (double) RAND_MAX -1;  // Random values between -1, 1
    F[i][j] = 0;
    // printf("A[%i][%f]\n", i, A[i][j]);
  }
}

for (int i = 0; i < particles; i++){
    Mass[i] = 5 * ((double) rand() / (double) RAND_MAX ); //Random values between 0-5
    Charge[i] = 10 * (double) rand() / (double) RAND_MAX  - 5; //Random values between -5, 5
}

}
