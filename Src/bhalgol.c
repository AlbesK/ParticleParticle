//Barnes-Hut Algorithm -- Implementation

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
    int N_DIMENSIONS = 2 ;
    int N_PARTICLES = 8;
    char c;
    //Physical_Properties_Array[Particles Position][Masses][Charges][..etc..] Perhaps better for all of these pointers.  
    double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));
    double *V = malloc(sizeof(double) * N_PARTICLES );
    double *Mass = malloc(sizeof(double) * N_PARTICLES);
    double *Charge = malloc(sizeof(double) * N_PARTICLES);
    double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));



    

    
    srand(1); //Seed time for random value generation 

    //Initialise arrays for now

    for (int i=0; i < N_PARTICLES; i++){
        for(int j=0; j < N_DIMENSIONS; j++){
            A[i][j] = 20 * ( (double) rand() / (double) RAND_MAX ) - 10;
            printf("Particle [%i] with [%f] \n", i, A[i][j]);
    }
    }

    for (int i = 0; i < N_PARTICLES; i++){
        Mass[i] = 5 * ((double) rand() / (double) RAND_MAX );
        Charge[i] = 10 * ((double) rand() / (double) RAND_MAX ) - 5;
        printf("Particle [%i] : Mass [%f], Charge [%f] \n", i, Mass[i], Charge[i]);
    }

    
    /* Asuming universe is 20 units [abstract for now] big in 2D then with root at center of [x,y] = [0,0] 
    we have it to be a square of 20x20. We gonna divide this clockwise like cartesian coordinates to NE, SE, SW, NW 
    accordingly. This means each square will have length s = 10 (20/2) and coordinates diagonals for NE [10,10], SE [10, -10]
    SW [-10, -10] and NW [-10, 10] */

    /*According to the book, twigs are labeled with -1,-2,-3 etc and leafs with 1,2,3 etc, with root being 0. */
    
    SUBDIVIDE (cut-node, pointer){
        
        iparent = cut-node;
        ipoi = pointer;
        ilev = level[iparent] + 1;
        1st_dau[iparent] = ipoi;

        //count particles in subcells
        //n_dau[iparent] = # new daughter nodes 

        for(each-twig-nod do:){
            itwig = itwig-1;
            node[ipoi] = itwig;
            parent[ipoi] = iparent;
            level[itwig] = ilev;
            ipoi = ipoi + 1

        }

        for(each leaf-node do:){
            ileaf = ileaf + 1
            node[ipoi] = ileaf;
            parent[ipoi] = iparent;
            //plabel[ileaf] = particle # ( number then with # symbol)
            level[ileaf] = ilev;
            // Store positions and moments of particle
            ipoi = ipoi + 1;
        }
    }

    //Pseudoparticle MOMENTS routine:
    MOMENTS(){
        
        ilevel = levmax - 1;
        itwig = -ntwig;

        for(each level do:){
            *repeat* for each mode on same level:
               
                pointer = ipoint[itwig]; //meaning that ipoi is ipoint?
                nbuds = ndau[pointer]; //meaning n_buddies(?) and n_dau from above?
                point1 = 1st_dau[pointer];
                //zero moment sums:
                M[itwig] = 0;
                r_com[itwig] = 0;

                do i=1,n_buds
                    point_dau = point1 +i -1;
                    inode = node[point_dau];
                    //sum mass and centre of mass:
                    M[itwig] = M[itwig] + M[inode];
                    r_com[itwig] = r_com[itwig] + r_c[inode]; //Where r_c is same as r_com?
                end do

                r_com[itwig] = r_com[itwig]/M[itwig];

                itwig = itwig + 1
            until level done 
            ilevel = ilevel + 1
        //end do
        }
    }

    
    return 0;

}