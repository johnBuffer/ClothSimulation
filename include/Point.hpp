#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

class Point
{
public:
    Point();
    Point(float x, float y, float m = 1);

    void updateV();
    void updatePos(float dt);

    bool fixed;
    float x, y;
    float vx, vy, ax, ay, mass;
    sf::Color color;

private:
    float last_x, last_y;
};

#endif // POINT_H_INCLUDED
