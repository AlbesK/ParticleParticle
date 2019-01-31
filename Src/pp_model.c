/* PP (Particle-Pair) model */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Functions.h"

void ppmodel(int particles, int dimensions, double* V, double (*F)[dimensions], double (*A)[dimensions], double* Mass, double* Charge){

double Total_Force[dimensions]; Total_Force[0]=0; Total_Force[1]=0; Total_Force[2]=0;
double Total_Energy = 0.0;

for(int i = 0; i < particles; i++){
    for(int j = i+1; j < particles; j++){
        
        double difference[dimensions]; //difference array for vector components e.g. (x2-x1), (y2-y1) etc   
        double r = 0.0; //r storage of distance for N_DIMENSIONS vectors

        /*Find the distance between particle i and i+1,i+2,...,i+n etc 
        then increment i and find the distance for i+1 with i+2,i+3,...,
        i+n*/
        
        for(int n = 0; n < dimensions; n++){
            
            /* finding the (x2-x1)^2 components for the total vector distance */
            difference[n] = (A[i][n]-A[j][n])*(A[i][n]-A[j][n]); 
            r += difference[n]; //Add the components
             
        }

        double sqr = sqrt(r); //Defining a value for the square root for efficiency and calculating the total distance r in sqr

        V[i] += Charge[j] * (1.0/sqr);  //Calculating Potentials using pointers
        V[j] += Charge[i] * (1.0/sqr);

        for(int n = 0; n < dimensions; n++){

            F[i][n] += (Charge[i] * Charge[j])/(sqr*sqr*sqr)*difference[n];
            F[j][n] -= F[i][n];  //F[j] += -F[i];
            
        }

        
        

        }

	for(int n = 0; n < dimensions; n++){
    
    Total_Force[n] += F[i][n];
    
    }
    
    Total_Energy += V[i];
    
}
/*
printf("The total force on this system is: [ ");
for(int n=0; n< dimensions; n++){
printf( "%f ", Total_Force[n]);
}
printf("]\n");
printf("The total energy of this system is: %f\n", Total_Energy);
*/






}

    
    
    

