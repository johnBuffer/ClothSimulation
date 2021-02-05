#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED

#include "Point.hpp"
#include "Vec.hpp"
#include <SFML/System/Vector2.hpp>


class Link
{
public:
    Link(Point* p1, Point* p2, float length = 0);
    void update(float dt, float x, float y);

    sf::Vector2f getPos1() {return sf::Vector2f(m_p1->x, m_p1->y);};
    sf::Vector2f getPos2() {return sf::Vector2f(m_p2->x, m_p2->y);};

    sf::Color getCol1() {return m_p1->color;};
    sf::Color getCol2() {return m_p2->color;};

    bool isBroken() {return m_broken;};

private:
    float m_length;
    Point *m_p1, *m_p2;
    bool m_broken;
};

#endif // LINK_H_INCLUDED
