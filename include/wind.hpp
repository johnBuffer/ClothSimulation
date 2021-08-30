#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "engine/physics/physics.hpp"


struct Wind
{
    sf::FloatRect rect;
    sf::Vector2f force;

    Wind(sf::Vector2f s, sf::Vector2f p, sf::Vector2f f)
        : rect(p, s)
        , force(f)
    {}

    void update(float dt)
    {
        rect.left += 5.0f * force.x * dt;
        //rect.top += force.y * dt;
    }
};


struct WindManager
{
    std::vector<Wind> winds;
    sf::Vector2f window_size;

    void update(PhysicSolver& solver, float dt)
    {
        for (Wind& w : winds) {
            w.update(dt);
            for (Particle& p : solver.objects) {
                if (w.rect.contains(p.position)) {
                    p.forces += 1.0f * w.force / dt;
                }
            }

            if (w.rect.left > window_size.x) {
                w.rect.left = -w.rect.width;
            }
        }
    }
};
