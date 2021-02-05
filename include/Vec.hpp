#ifndef VECTEUR_H_INCLUDED
#define VECTEUR_H_INCLUDED

#include "Point.hpp"
#include <iostream>
#include <cmath>

class Vec
{
public:
    Vec(float x, float y);
    Vec(Point *p1, Point *p2);

    float x, y, norme;

    void normalize();
    Vec getNormalVec();
    float dot(Vec v);
};

#endif // VECTEUR_H_INCLUDED
