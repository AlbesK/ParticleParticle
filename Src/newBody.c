#include<stdio.h>
#include<stdlib.h>
#include"bhHeaders.h"

/*
    Assign new Pseudobody to node of quad tree
*/
void newBody(struct quad* nd, struct point pos, double mass, double charge)
{
    struct body* b = malloc(sizeof(struct body));
    b->pos.x = pos.x;
    b->pos.y = pos.y;
    b->mass = mass;
    b->charge = charge;
    nd->b = b;
};
