/* PP (Particle-Pair) model */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Functions.h"

void findDistance(class Point &x, class Point &y, double &distance, double *r)
{
    double tempx, tempy, tempz;
    tempx = (x.x - y.x);
    tempx = tempx * tempx; 
    tempy = (x.y - y.y);
    tempy = tempy * tempy;
    tempz = (x.z - y.z);
    tempz = tempz * tempz;
    r[0] = tempx; r[1] = tempy; r[2] = tempz;
    distance = tempx + tempy + tempz;
    distance = sqrt(distance);

}

void ppmodel(int particles, std::vector<Body> *Bodies, std::vector<Point> *Forces){

double Total_Force[3];
double Total_Energy = 0;
double r[3] = {0,0,0};
double distance = 0;

for(int i = 0; i < particles; i++){
    for(int j = i+1; j < particles; j++){
        
        findDistance((*Bodies)[i], (*Bodies)[j], distance, r);
        printf("Distance %f r[%f, %f, %f] \n", distance, r[0], r[1], r[2]);
    
    }
}

}   
    
    

