#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

class Point
{
public:
    Point();
    Point(double x, double y, double m = 1);

    void updateV();
    void updatePos(double dt);

    bool fixed;
    double x, y;
    double vx, vy, ax, ay, mass;
    sf::Color color;

private:
    double last_x, last_y;
};

#endif // POINT_H_INCLUDED
