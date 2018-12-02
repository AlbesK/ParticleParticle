/*Initialising the Array (A) of our particles and dimensions,
later including charge and masses*/    

#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#include "Functions.h"


void initialiser(int particles, int dimensions, double (*A)[dimensions], double* Mass, double* Charge, int seed ){ // i for particles, j for dimensions

/*Loop through the array and initialise the position with random values between */ 

srand(seed); //Seed time for random value generation 

for (int i=0; i < particles; i++){
  for(int j=0; j < dimensions; j++){
    A[i][j] = 10 * ( (double) rand() / (double) RAND_MAX );
  }
}

for (int i = 0; i < particles; i++){
    Mass[i] = 5 * ((double) rand() / (double) RAND_MAX );
    Charge[i] = 10 * ((double) rand() / (double) RAND_MAX ) - 5;
}

}
