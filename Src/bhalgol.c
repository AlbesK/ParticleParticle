//Barnes-Hut Algorithm -- Implementation

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
    int N_DIMENSIONS;
    int N_PARTICLES;
    char c;
    //Physical_Properties_Array[Particles Position][Masses][Charges][..etc..] Perhaps better for all of these pointers.  
    double (*A)[N_DIMENSIONS] = malloc(size_of(double[N_PARTICLES][N_DIMENSIONS]));
    double *V = malloc(size_of((double) * N_PARTICLES ));
    double *Mass = malloc(size_of((double) * N_PARTICLES));
    double *Charge = malloc(size_of(double) * N_PARTICLES);
    double (*F)[N_DIMENSIONS] = malloc(size_of(double[N_PARTICLES][N_DIMENSIONS]));

    print("Please input number of particles: \n");

    if (scanf("%d%c", &N_PARTICLES, &term) != 2 || term != '\n'){
        printf("Failure, please try again by inputing a positive integer value..");
        exit(-1);
    }

    if (N_PARTICLES < 2){
        printf("Insuficient amount of particles");
        exit(-1);
    }

    return 0;

}