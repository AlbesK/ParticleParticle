#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

////Number of Particles
//#define  N_PARTICLES 3 

////Number of Dimensions the particles reside in
//#define  N_DIMENSIONS 2 

int main()
{
 
  int N_PARTICLES;
  int N_DIMENSIONS = 2;
  int readin;

  printf("How many particles?\n");
  readin = scanf("%i", &N_PARTICLES);
  if (readin != 1) {
    printf("Particle number read failed\n");
    exit(-1);
  }
  if (N_PARTICLES < 2) {
    printf("Insufficent number of particles %i\n", N_PARTICLES);
    exit(-1);
  }
  

    srand(clock()); // seed random number generator

    clock_t start, end;
    
    #include "initl1.c"  //Initialiser

    start = clock(); //start timer
    
    #include "PPmodel.c"  //Model
    
    end = clock(); //end timer
    
    double duration = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time elapsed is: %f (s)\n", duration);
    
    #include "printer.c" //Print file.c

    free(A); //Free memory
    free(mass);
    free(V);
    free(F);

    return 0;
}
