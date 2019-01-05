#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

class Body { //Class for a particle containing:
    private:
    
    double x; //position x, y for 2D case for now
    double y;
    double mass; 
    double charge; 


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



int main(int argc, char const *argv[])
{
    /* code */
    int x = 0; int y = 0; int mass = 1; int charge = 1; 
    int seed = 1; int N_PARTICLES = 10;
    srand(seed);

    std::vector<Body> *p_label = new std::vector<Body>(N_PARTICLES);
    
    for(int i=0; i<N_PARTICLES; i++){
        x = 20 *  (double) rand() / (double) RAND_MAX -10 ;
        y = 20 *  (double) rand() / (double) RAND_MAX -10 ;
        mass = 5 * ( (double) rand() / (double) RAND_MAX );
        charge = 20 *  (double) rand() / (double) RAND_MAX -10 s;
        (*p_label)[0]->x = x;
    }
    
    delete [] p_label;
    return 0;
}
