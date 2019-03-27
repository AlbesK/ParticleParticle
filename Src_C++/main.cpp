#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

#include "Functions.h"
    
/*
    Function to save X, Y coordinates of bodies and Time taken to run build the tree
*/
void particle_data(std::vector<Body> *bodies, std::vector<Point> *Forces, std::vector<Point> *Potentials, int* N_PARTICLES, double t){
    FILE * f; 
    f = fopen("/home/albes/Desktop/mcpp.txt", "w"); /* open the file for writing*/
    printf("Writting...\n");
    /* write 10 lines of text into the file stream*/    
    fprintf(f, "N,X,Y,M,C,Fx,Fy,Vx,Vy,TBuilt\n");

    for(int i = 0; i < *N_PARTICLES;i++){
        fprintf (f, "%d,%f,%f,%f,%f,%f,%f,%f,%f\n", i, (*bodies)[i].x, (*bodies)[i].y, (*bodies)[i].mass, (*bodies)[i].charge, (*Forces)[i].x, (*Forces)[i].y, (*Potentials)[i].x, (*Potentials)[i].y);
    }
    fprintf(f,",,,,,,,%f",t);

    /* close the file*/  
    fclose (f);
    printf("Closed file.\n");
}

int main()
{
  // Particle Number and Dimensions

  clock_t start, end;
  char term;

  int N_PARTICLES; int N_DIMENSIONS = 3; int seed=1;

  printf("How many particles?\n");
  if (scanf("%d%c", &N_PARTICLES, &term) != 2 || term != '\n') {//Stack overflow bit https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
    printf("Failure: Not an integer. Try again\n");
    exit(-1);
  } 

  printf("Calculating\n");
  if (N_PARTICLES < 2) {
    printf("Insufficent number of particles %i\n", N_PARTICLES);
    exit(-1);
  } 


  //Pointers and their initialization

  std::vector<Body> *Bodies;
  Bodies = new std::vector<Body>(N_PARTICLES);
  std::vector<Point> *Forces;
  Forces = new std::vector<Point>(N_PARTICLES);
  std::vector<Point> *Potentials;
  Potentials = new std::vector<Point>(N_PARTICLES);

  initialiser(seed, N_PARTICLES, Bodies, Forces);
  
  start = clock(); //start timer
  ppmodel(N_PARTICLES, Bodies, Forces, Potentials);
  end = clock(); //end timer
  double duration = (double)(end-start)/CLOCKS_PER_SEC;

  char c;
  printf("Do you want to save the data? Y/n \n");
  scanf("%c", &c);
  
  if(c=='Y'){
      printf("Saving bodies data...\n");
      particle_data(Bodies, Forces, Potentials, &N_PARTICLES, duration);
      printf("Done\n");
  } else
  {
      printf("Continuing\n");   
  }

  //Free Memory
  delete  Bodies;
  delete  Forces; 
  delete  Potentials;

  std::cout << "Pointers deleted succesfuly" << std::endl;

  printf("Time elapsed is: %f (s)\n", duration);

}

