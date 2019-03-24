/* PP (Particle-Pair) model */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Functions.h"

void findDistance(class Point &x, class Point &y, double &distance, double *r)
{
    double tempx, tempy, tempx_m, tempy_m; //, tempz;
    tempx = (y.x - x.x);
    tempx_m = tempx * tempx; 
    tempy = (y.y - x.y);
    tempy_m = tempy * tempy;
    // tempz = (y.z - x.z);
    // tempz = tempz * tempz;
    r[0] = tempx; r[1] = tempy; //r[2] = tempz;
    distance = tempx_m + tempy_m; //+ tempz;
    distance = sqrt(distance);
    // printf("Distance is %f\n", distance);

}

void ppmodel(int particles, std::vector<Body> *Bodies, std::vector<Point> *Forces){

double Total_Force[2]={0,0}; //0}; [3] here
double Total_Energy = 0;
double r[2] = {0,0}; //,0}; r[3] here for 3D
double distance = 0;
double k = 0;

for(int i = 0; i < particles; i++){
    for(int j = i+1; j < particles; j++){
        
        findDistance((*Bodies)[i], (*Bodies)[j], distance, r);
        // printf("Distance %f r[%f, %f, %f] \n", distance, r[0], r[1], r[2]);
        
        k = (((*Bodies)[i].charge*(*Bodies)[j].charge)/(distance*distance*distance));
        // printf("k: %f\n", k); printf("r[0]: %f\n", r[0]);  printf("r[1]: %f\n", r[1]);
        (*Forces)[i].x += k*r[0]; (*Forces)[i].y += k*r[1]; //(*Forces)[i].z += k*r[2];
        (*Forces)[j].x -= k*r[0]; (*Forces)[j].y -= k*r[1]; //(*Forces)[j].z -= k*r[2];

        
    }
    // printf("F_%i : [%f, %f]\n", i, (*Forces)[i].x, (*Forces)[i].y); //(*Forces)[i].z); // deleted one %f as I want 2D now
    Total_Force[0] += ((*Forces)[i].x); Total_Force[1] += ((*Forces)[i].y);// Total_Force[2] += ((*Forces)[i].z);
}
    // printf("TF : [%f, %f]\n", Total_Force[0], Total_Force[1]);// Total_Force[2]);
}   
    
    

