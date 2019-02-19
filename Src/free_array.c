#include <stdlib.h>
#include "Functions.h"

void free_array( int Particles, int Dimensions, double (*A)[Dimensions]){
    //for(int i=0; i<Particles*Dimensions; i++){
        free(A);
        
    //}
    
}