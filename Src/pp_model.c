/* PP (Particle-Pair) model */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Functions.h"

void ppmodel(int particles, int dimensions, double* V, double (*F)[dimensions], double (*A)[dimensions], double* Mass){

for(int i=0; i<particles; i++){
    for(int j=i+1; j<particles; j++){
        
        double difference[dimensions]; //difference array for vector components e.g. (x2-x1), (y2-y1) etc   
        double r = 0.0; //r storage of distance for N_DIMENSIONS vectors

        /*Find the distance between particle i and i+1,i+2,...,i+n etc 
        then increment i and find the distance for i+1 with i+2,i+3,...,
        i+n*/
        
        for(int n=0; n<dimensions; n++){
            
            /* finding the (x2-x1)^2 components for the total vector distance */
            difference[n] = (*(*A+n) - *(*(A+1)+n)) * (*(*A+n) - *(*(A+1)+n)); 
            r += difference[n]; //Add the components
             
        }

        double sqr = sqrt(r); //Defining a value for the square root for efficiency and calculating the total distance r in sqr

        *(V+i) += *(Mass+j) * (1.0/sqr);  //Calculating Potentials using pointers
        *(V+j) += *(Mass+i) * (1.0/sqr);

        for(int n=0; n<dimensions; n++){

            *(*F+n) += (*(Mass+i) * *(Mass+j))/(sqr*sqr*sqr)*difference[n];   
            
        }

        //F[i] += mass[j] * (1.0/(sqr*sqr*sqr))*r; //Calculating Forces using the trick F = 1/r^3 * r, where r = r0 * k where k is direction
        //F[j] += -F[i];

        }
	for(int n=0; n<dimensions; n++){
            printf("F[%i][%i] = %f\n", i, n, *(*F+n) );
        }
}
}

    
    
    

