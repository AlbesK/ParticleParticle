#ifndef _FUNCTIONS
#define _FUNCTIONS

void initialiser(int i, int j, double (*A)[j], double (*F)[j], double (*Vel)[j], double* Mass, double* Charge, int seed);
void ppmodel(int* i, int* j, double* V, double (*F)[*j], double (*A)[*j], double* Mass, double* Charge);
void free_array(int particles, int dimensions, double (*A)[dimensions]);
void leapfrog(int* particles, int* dimensions,double* Mass, double* Charge, 
double (*A)[*dimensions], double (*Vel)[*dimensions], 
double (*F)[*dimensions], double* Time, double* dt);

#endif
