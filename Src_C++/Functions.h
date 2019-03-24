#pragma once
#include <vector>

//Object approach
class Point {
  public:
  double x, y; //, z;
  
  void setX(double x){
    this->x = x;
  }
  void setY(double y){
    this->y = y;
  }
  // void setZ(double z){
  //   this->z = z;
  // }

  ~Point(){};
  
};

class Body: public Point {
  public:
  
  double mass;   //Mass
  double charge;  //Charge

  Body(double m = 1.0, double c = -1.0)
  { //Default Constructor
    
    this->mass = m;
    this->charge = c;
    // std::cout <<"Body constructed\n";
  }

  ~Body(){}; //Destructor


};

void initialiser(int seed, int particles, std::vector<Body> *Bodies, std::vector<Point> *Forces);
void ppmodel(int particles, std::vector<Body> *Bodies, std::vector<Point> *Forces);


