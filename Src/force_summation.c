#include<stdio.h>
#include<math.h>
#include"bhHeaders.h"

/*
    Get force summation
*/
void force_summation(struct quad* nd, struct body* bodies, struct point* Forces, int* N_PARTICLES){
    double d[2] = {0,0};
    double m;
    for(int i=0; i<*N_PARTICLES; i++){
        difference(&bodies[i].pos, &nd->b->pos, d);
        m = mag(d);
        // printf("|d|:%f, [%f,%f]\n",m,d[0],d[1]);
        // printf("s/d = %f\n", nd->s/m);
        if(nd->s/m<=5){
            // printf("True\n");
            Forces[i].x = (bodies[i].charge * nd->b->charge)/(m*m*m)*d[0];
            Forces[i].y = (bodies[i].charge * nd->b->charge)/(m*m*m)*d[1];
            // printf("TF_[%i] = [%f,%f] \n", i,Forces[i].x, Forces[i].y);  

        } else
        {
            // printf("False\n");
            // levelorder()

        }
        
    }
}