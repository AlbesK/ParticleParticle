/*Initialising the Array (A) of our particles and dimensions,
later including charge and masses*/    
    
//double A[N_PARTICLES][N_DIMENSIONS];

double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));  //Dynamically allocate memory
free(A); //Free memory
    
A[0][0] = 0.0;  //Abstract units for now
A[1][0] = 0.0;
A[2][0] = 0.0;

A[0][1] = 1.0;  //Abstract units for now
A[1][1] = 2.0;
A[2][1] = 3.0;    


double *mass = malloc(sizeof(double[N_PARTICLES]));  //Dynamically allocate memory

mass[0] = 1.0;
mass[1] = 2.0;
mass[2] = 1.0;

// Potential at each atom
double V[N_PARTICLES];
    
//Force at each atom
double F[N_PARTICLES];
