#include "Vec.hpp"
#include <cmath>


Vec::Vec(float x, float y)
{
    this->x = x;
    this->y = y;

    this->norme = sqrt(x*x+y*y);
}

Vec::Vec(Point *p1, Point *p2)
{
    this->x = p1->x-p2->x;
    this->y = p1->y-p2->y;

    this->norme = sqrt(x*x+y*y);
}

void Vec::normalize()
{
    if (norme > 0)
    {
        x /= norme;
        y /= norme;
    }
    else
        std::cout<<"error : null norm"<<std::endl;
}

Vec Vec::getNormalVec()
{
    return Vec(-y, x);
}

float Vec::dot(Vec v)
{
    return x*v.x+y*v.y;
}
