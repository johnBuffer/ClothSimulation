#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "Link.hpp"

#include <iostream>

class World
{
public:
    World();

    void addPoint(Point* point) {m_points.push_back(point);};
    void addLink(Link* link) {m_links.push_back(link);};

    void addCloth(double x, double y, double l, double h);

    void update(double x, double y);
    void render(sf::RenderWindow &window);

private:
    sf::Clock m_clock;
    std::vector<Point*> m_points;
    std::vector<Link*> m_links;

};

#endif // WORLD_H_INCLUDED
