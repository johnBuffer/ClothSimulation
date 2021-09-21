#pragma once
#include "engine/physics/physics.hpp"

namespace usr
{
struct Utils
{
    static bool isInRadius(const Particle& p, sf::Vector2f center, float radius)
    {
        const sf::Vector2f v = center - p.position;
        return v.x * v.x + v.y * v.y < radius* radius;
    }


    static void applyForceOnCloth(sf::Vector2f position, float radius, sf::Vector2f force, PhysicSolver& solver)
    {
        for (Particle& p : solver.objects) {
            if (isInRadius(p, position, radius)) {
                p.forces += force;
            }
        }
    }
};
}