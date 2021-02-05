#include "Point.hpp"


Point::Point()
{
    x = 0;
    y = 0;

    vx = 0;
    vy = 0;

    ax = 0;
    ay = 0;

    mass = 0;

    last_x = 0;
    last_y = 0;

    fixed = false;
}

Point::Point(double x, double y, double m)
{
    this->x = x;
    this->y = y;

    last_x = x;
    last_y = y;

    vx = 0;
    vy = 0;

    ax = 0;
    ay = 0;

    mass = m;

    fixed = false;
}

void Point::updateV()
{
    ay = 0;

    if (fixed)
    {
        vx = 0;
        vy = 0;
    }
}

void Point::updatePos(double dt)
{
    if (!fixed)
    {
        ay += 20000;
        ax += 5000;

        double y_soil = 900;

        if (y > y_soil)
        {
            y = y_soil;
            ax = -2*vx/dt;
        }

        if (y < 0)
        {
            y = 0;
        }

        if (x > 1600)
        {
            x = 1600;
        }

        if (x < 0)
        {
            x = 0;
        }

        ax += -vx*0.05/dt/mass;
        ay += -vy*0.05/dt/mass;

        double new_x = 2*x-last_x+ax*dt*dt;
        double new_y = 2*y-last_y+ay*dt*dt;

        last_x = x;
        last_y = y;

        x = new_x;
        y = new_y;

        vx = x-last_x;
        vy = y-last_y;

        ax = 0;
        ay = 0;
    }
}
