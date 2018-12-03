#pragma once

void initialiser(int i, int j, double (*A)[j], double* Mass, double* Charge, int seed);
void ppmodel(int i, int j, double* V, double (*F)[j], double (*A)[j], double* Mass, double* Charge);


