#include<stdio.h>

/*
    Body structure, having coordinates in 2D, mass and charge.
*/
struct body 
{
    struct point pos; // Position
    double mass;   // Mass
    double charge;  // Charge
    struct point F_felt;
};