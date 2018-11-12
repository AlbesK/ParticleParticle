/* PP (Particle-Pair) model */

for(int i=0; i<N_PARTICLES; i++){
      V[i] = 0.0;
}

for(int i=0; i<N_PARTICLES; i++){
  
  //F[i] = 0.0;
}


for(int i=0; i<N_PARTICLES; i++){
    for(int j=i+1; j<N_PARTICLES; j++){
           
        double r = 0.0; //r storage of distance for N_DIMENSIONS vectors

        /*Find the distance between particle i and i+1,i+2,...,i+n etc 
        then increment i and find the distance for i+1 with i+2,i+3,...,
        i+n*/
        
        for(int n=0; n<N_DIMENSIONS; n++){
            
            /* finding the (x2-x1)^2 components for the total vector distance */
             
            r+=(A[i][n]-A[j][n])*(A[i][n]-A[j][n]); 
             
        }

        double sqr = sqrt(r); //Defining a value for the square root for efficiency

        V[i] += mass[j] * (1.0/sqr);  //Calculating Potentials
        V[j] += mass[i] * (1.0/sqr);

        //F[i] += mass[j] * (1.0/(sqr*sqr*sqr))*r; //Calculating Forces using the trick F = 1/r^3 * r, where r = r0 * k where k is direction
        //F[j] += -F[i];

        }
	
}
    

    
    
    

