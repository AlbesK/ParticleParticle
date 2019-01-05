#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

class Body { //Class for a particle containing:
    private:
    
    double x; double y; //position x, y for 2D case for now
    double mass; double charge; 

    public:

    Body(double x=0, double y=0, double mass=1, double charge=1){ //instantiate body particle
        this->x = x;
        this->y = y;
        this->mass = mass;
        this->charge = charge;
    }

    double getX(){return this->x;}
    double getY(){return this->y;}
    double getMass(){return this->mass;}
    double getCharge(){return this->charge;}

    ~Body(){}; //Destructor

};

class QuadTree {
    
};



int main(int argc, char const *argv[])
{
    /* code */
    int x = 0; int y = 0; int mass = 1; int charge = 1; 
    int seed = 1; int N_PARTICLES = 10; int N_DIMENSIONS = 2;
    double Total_Force[N_DIMENSIONS];
    double Total_Energy = 0.0;
    srand(seed);

    std::vector<Body> p_label; //Vector of Bodies
    
    for(int i=0; i<N_PARTICLES; i++){ //Initialise values
        x = 20 *  (double) rand() / (double) RAND_MAX -10 ;
        y = 20 *  (double) rand() / (double) RAND_MAX -10 ;
        mass = 5 * ( (double) rand() / (double) RAND_MAX );
        charge = 20 *  (double) rand() / (double) RAND_MAX -10 ;
        Body b(x, y, mass, charge);
        p_label.push_back(b);
    }

    for(int i=0; i<N_PARTICLES; i++){ //Print Values
        printf("Body %i has x = %f, y = %f, mass = %f, charge = %f \n", i, 
        p_label[i].getX(), p_label[i].getY(), p_label[i].getMass(),
        p_label[i].getCharge());
    }





    
    //delete [] p_label; //Gonna use this later for now lets stay on the stack
    return 0;
}
