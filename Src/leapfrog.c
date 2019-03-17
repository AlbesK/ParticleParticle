#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Functions.h"

void leapfrog(int* particles, int* dimensions,double* Mass, double* Charge, 
double (*A)[*dimensions], double (*Vel)[*dimensions], 
double (*F)[*dimensions], double* Time, double* dt){

    FILE* f;
    f = fopen("/home/albes/Desktop/leap.txt", "w"); /* open the file for writing*/
    double total_steps = round((Time[1]-Time[0])/(*dt));
    fprintf(f,"T,");
    for(int i=0; i<*particles; i++){
        fprintf(f,"N%d,", i);
        for(int j=0; j<*dimensions; j++){
            fprintf(f, "x%d,", j);
        }
        fprintf(f,"\n");
    }
    
    // for(int i=0; i<total_steps; i++){

    // }

    fclose(f);
}
