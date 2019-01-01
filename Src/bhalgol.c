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
    
    int cut_node = 0;
    int pointer = 0;
    int ileaf = 0;
    int itwig = 0;
    int Depth = round(log(N_PARTICLES)); //Rounding the number to allocate the memory needed for the list.
    
    int ilevel = 0;
    int point1 = 0;
    int n_buds = 0;
    int M[Depth];
    int r_com[Depth];
    int parent[Depth];
    int inode = 0;
    int point_dau = 0;
    int ipoint[Depth*Depth];
    
    int node[Depth*Depth];    
    int level[Depth]; // ln(Depth) Depented particle depth, after we divide recursively space by half each time
    level[0] = 0;
    int first_dau[Depth*Depth]; //Trying Depth^2 for now as a guess
    int n_dau[N_PARTICLES]; 

    int fmaxmin(int list[], int size){ //max and min function for level mostly
        int max = 0; int min = 0; int mm[2];
        for(int i=0; i<size; i++){
            if(list[i]>max){
                max = list[i];
            }
            /*if(list[i]<min){
                min = list[i];
            }*/

        }

        /*mm[0] = max;
        mm[1] = min;*/

        return max;
    }


    //void SUBDIVIDE (cut_node, pointer){
        
        int iparent = cut_node;
        int ipoi = pointer;
        int ilev = level[iparent] + 1;
        first_dau[iparent] = ipoi;

        //count particles in subcells
        n_dau[iparent] = 4;//# new daughter nodes 

        //for(int i=0; i<cut_node; i++){ //For each-twig-node do:
            itwig = itwig-1;
            node[ipoi] = itwig;
            parent[ipoi] = iparent;
            level[itwig] = ilev;
            ipoi = ipoi + 1;

            printf("itwig = %i, node[%i] = %i, parent[%i] = %i, level[%i] = %i \n", itwig, ipoi, node[ipoi], parent[ipoi], iparent, itwig, level[itwig]);

        //}

        for(int i=0; i<Depth; i++){ //for each leaf-node
            ileaf = ileaf + 1;
            node[ipoi] = ileaf;
            parent[ipoi] = iparent;
            //plabel[ileaf] = particle # ( number then with # symbol)
            level[ileaf] = ilev;
            // Store positions and moments of particle
            ipoi = ipoi + 1;
        }

        printf("iparent = %i , ipoi = %i , ilev = %i \n", iparent, ipoi, ilev);
    //}

    
    int levmax =  Depth;//fmaxmin(level, Depth);



    //Pseudoparticle MOMENTS routine:
    //void MOMENTS(){
        
        ilevel = levmax - 1;
        itwig = -itwig; //-ntwig;

        for(int i = 0; i<Depth; i++) {//each level do
            //*repeat* for each mode on same level:
               
            pointer = ipoint[itwig]; //meaning that ipoi is ipoint?
            n_buds = n_dau[pointer]; //meaning n_buddies(?) and n_dau from above?
            point1 = first_dau[pointer];
            //zero moment sums:
            M[itwig] = 0;
            r_com[itwig] = 0;
            int in = 0;
            do {
                point_dau = point1 +i -1;
                inode = node[point_dau];
                //sum mass and centre of mass:
                M[itwig] = M[itwig] + M[inode];
                r_com[itwig] = r_com[itwig] + r_com[inode]; //Where r_c is same as r_com? Assuming it is from the book
            } while(in < n_buds);

            r_com[itwig] = r_com[itwig]/M[itwig];

            itwig = itwig + 1;
            //until level done 
            ilevel = ilevel + 1;
        //end do
        }
    //}

    //The pseudocode in the book seems to be a bit confusing, perhaps of some typos will try it on my own way from what I got after this test


    free(A); //Free memory
    free(Mass);
    free(V);  
    free(F);
    free(Charge);
    
    return 0;

}