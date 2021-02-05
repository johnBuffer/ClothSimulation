#ifndef VECTEUR_H_INCLUDED
#define VECTEUR_H_INCLUDED

#include "Point.hpp"
#include <iostream>
#include <cmath>

class Vec
{
public:
    Vec(double x, double y);
    Vec(Point *p1, Point *p2);

    double x, y, norme;

    void normalize();
    Vec getNormalVec();
    double dot(Vec v);
};

#endif // VECTEUR_H_INCLUDED
