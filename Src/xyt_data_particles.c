#include<stdio.h>
#include"bhHeaders.h"

void xyt_data_particles(struct body* bodies, int* N_PARTICLES, double t){
    FILE * f; 
    f = fopen("/home/albes/Desktop/bodiestd.txt", "w"); /* open the file for writing*/
    printf("Writting...\n");
    /* write 10 lines of text into the file stream*/    
    fprintf(f, "N,X,Y,M,C,T\n");

    for(int i = 0; i < *N_PARTICLES;i++){
        fprintf (f, "%d,%f,%f,%f,%f\n", i, bodies[i].pos.x, bodies[i].pos.y, bodies[i].mass, bodies[i].charge);
    }
    fprintf(f,",,,,,%f",t);

    /* close the file*/  
    fclose (f);
    printf("Closed file.\n");
}