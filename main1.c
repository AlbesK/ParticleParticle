#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Number of Particles
#define  N_PARTICLES 3 

//Number of Dimensions the particles reside in
#define  N_DIMENSIONS 2 

int main()
{
    clock_t start, end;
    double clock_Average = 0;
    double duration = 0;
    
    
    #include "initl1.c"  //Initialiser
    
    for(int i=0; i<10; i++){

        start = clock(); //start timer
    
        #include "PPmodel.c" //Model
    
        end = clock(); //end timer
        duration = (double)(end-start)/CLOCKS_PER_SEC;
        clock_Average += duration;

    }
    
    
    
    
    printf("Time elapsed is: %f (s)\n", clock_Average/10); // Average time for 10 cycles.
    
    #include "printer.c" //Print file.c

    return 0;
}