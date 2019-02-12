#ifndef _FUNCTIONS
#define _FUNCTIONS

void initialiser(int i, int j, double (*A)[j], double* Mass, double* Charge, int seed);
void ppmodel(int i, int j, double* V, double (*F)[j], double (*A)[j], double* Mass, double* Charge);
void free_array(int particles, int dimensions, double (*A)[dimensions]);

#endif
