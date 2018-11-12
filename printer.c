/*Printing the values to check for accuracy of the model */

for(int i=0; i<N_PARTICLES; ++i){
    printf("The potential at particle %d is: %f \n", i, V[i]);
}

for(int i=0; i<N_PARTICLES; ++i){
  //    printf("The force at particle %d is: %f \n", i, F[i]);
}

double energy = 0.0;
double total_force = 0.0;

for(int i=0; i<N_PARTICLES; ++i){
    energy += mass[i] * V[i];
    //total_force += F[i];
}
    
printf("Total energy: %e\n", energy);
//printf("Total force in the system is equal to: %f\n", total_force);
