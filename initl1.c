/*Initialising the Array (A) of our particles and dimensions,
  later including charge and masses*/    

double (*A)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));  //Dynamically allocate memory

for (int i=0; i<N_PARTICLES; i++){
  for(int j=0; j<N_DIMENSIONS; j++){
    A[i][j] = 10.0 * (( (double) rand() / (double) RAND_MAX ) -0.5);
    printf("A[%i][%i] = %f\n", i, j, A[i][j]);
  }
 }


//double mass[N_PARTICLES];    
double *mass = malloc(sizeof(double) * N_PARTICLES);
for (int i=0; i<N_PARTICLES; i++){
      mass[i] = (( (double) rand() / (double) RAND_MAX ) -0.5);
      printf("%f \n", mass[i]);
}

double *V = malloc(sizeof(double) * N_PARTICLES);
double (*F)[N_DIMENSIONS] = malloc(sizeof(double[N_PARTICLES][N_DIMENSIONS]));
