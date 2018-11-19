#ifndef _FUNCTIONS
#define _FUNCTIONS

void initialiser(int i, int j, double (*A)[j], double* Mass);
void ppmodel(int i, int j, double* V, double (*F)[j], double (*A)[j], double* Mass);

#endif
