#include<stdio.h>

/*
    Construct tree (top down) by counting N particles in each node and checking if its a twig 
    (N>2) or a leaf (N=1). Empty nodes are ignored.
*/
int count(struct quad* nd, struct body* bodies, int* N_PARTICLES, int* track){
    if(nd==NULL){ printf("Node is NULL!!\n");return 0;}

    int number = 0; // Number of particles
    double centre_x = 0; // x component of pseudobody
    double centre_y = 0; // y component of pseudobody
    double centre_mass = 0; // Mass of Pseudobody
    double total_charge = 0; // extra term since we have charges!!
    int index = 0; //Index to save individual body for case 1

    // printf("Count call\n");

    for(int i=0; i<*N_PARTICLES; i++){
        if(contains(nd, bodies[i].pos)){
            number++;
            centre_mass += bodies[i].mass;
            centre_x += ((bodies[i].mass)*(bodies[i].pos.x));
            centre_y += ((bodies[i].mass)*(bodies[i].pos.y));
            total_charge += bodies[i].charge;
            index = i;
        }
    }

    if(number==0){
        // printf("Number is 0\n"); 
        // printf("Out of the recursion\n");  
        return 0;
    }
    // printf("Number is: %i\n", number);

    if(number==1){
            nd->b = &bodies[index]; 
            nd->data = index; //Assign the number of the body from the Bodies array, this is for getting back with data where the body is stored as a leaf
            // printf("Pointer to %i\n", nd->data); 
            // printf("Out of the recursion\n");             
            return 0;
    }

    if(number>1){ // I know its Null as there are more than 2 bodies here.
            if(nd->divided!=true){
            // printf("CENTRE MASS: %f\n",centre_mass);
            centre_x = centre_x/centre_mass; centre_y = centre_y/centre_mass;
            struct point p = {.x = centre_x, .y= centre_y};
            newBody(nd, p, centre_mass,  total_charge); //Assign pseudoboy
            // free(pseudobody);
            // printf("Pseudobody [%f,%f] at %i\n", centre_x,centre_y, nd->data);
        
            subdivide(nd, track);
            }
            
    }

    count(nd->NE,bodies,N_PARTICLES, track);
    count(nd->SE,bodies,N_PARTICLES, track);
    count(nd->SW,bodies,N_PARTICLES, track);
    count(nd->NW,bodies,N_PARTICLES, track);

}