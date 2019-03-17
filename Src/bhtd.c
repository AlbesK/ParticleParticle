//Barnes-Hut Algorithm -- Implementation in 2D

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "bhHeaders.h"

/*
    Main function to run the program
*/
int main() {

    int N_DIMENSIONS = 2; int seed=1;
    int N_PARTICLES;
    char term;
    clock_t ts, te;
    printf("How many particles?\n");
    if (scanf("%d%c", &N_PARTICLES, &term) != 2 || term != '\n') {
        printf("Failure: Not an integer. Try again\n");
        exit(-1);
    } 

    printf("Calculating\n");
    if (N_PARTICLES < 2) {
        printf("Insufficent number of particles %i\n", N_PARTICLES);
        exit(-1);
    } 
    struct body* bodies = malloc(sizeof(struct body)*N_PARTICLES);

    //Initialise values:
    int S = 100;
    char x[2]={'x', 'y'};
    srand(seed);
    struct point* Forces = malloc(sizeof(struct point)*N_PARTICLES);
    for (int i=0; i < N_PARTICLES; i++){

            double mass = 5 * ((double) rand() / (double) RAND_MAX ); // 1,5
            double charge = 10 * ((double) rand() / (double) RAND_MAX ) - 5; // -5, 5
            struct point p = {.x = S * ((double) rand() / (double) RAND_MAX ) - S/2, // -50, 50
            .y = 100 * ((double) rand() / (double) RAND_MAX ) - 50};

            struct body b = {.mass = mass, .charge = charge, .pos = p };
            Forces[i].x = 0; Forces[i].y = 0;
            bodies[i] = b;
            // printf("%d: %c:[%f], %c:[%f] \n",i, x[0], bodies[i].pos.x, x[1], bodies[i].pos.y );
    
    }

    int track = 0; // To keep track of twig numbering
    struct quad *root = newNode(0, 100, 0, 0); //Size of s=100 and pint of reference being (0,0) equiv. to (x_root, y_root)  
    //printf("Root square size is: %f\n", root->s);
    
    ts = clock(); // Start timer
    count(root, bodies, &N_PARTICLES, &track);
    te = clock(); // End timer
    double t = (double)(te-ts)/CLOCKS_PER_SEC; // Bottom-up tree construction time
    printf("Checking queue\n");
    levelorder(root);
    // display_tree(root);
    force_summation(root,bodies, Forces, &N_PARTICLES);
    // check(root);
    char c;
    printf("Do you want to save the data? Y/n \n");
    scanf("%c", &c);
    
    if(c=='Y'){
        printf("Saving bodies data...\n");
        xyt_data_particles(bodies,&N_PARTICLES, t);
        printf("Saving tree data...\n");
        xy_trees(root);
        printf("Done\n");
    } else
    {
        printf("Continuing\n");   
    }
    
    // deconstruct the tree
    free(root->b); // As there will always be a pseudobody at 0
    deconstruct_tree(root);
    free(bodies);
    free(Forces);

    printf("Released memory succesfuly\n");
    printf("Program took %f\n", t);

    return 0; 
}

