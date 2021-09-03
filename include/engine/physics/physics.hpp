#pragma once
#include <functional>
#include <SFML/System/Vector2.hpp>
#include "engine/common/index_vector.hpp"
#include "engine/common/utils.hpp"
#include "constraints.hpp"


struct PhysicSolver
{
    CIVector<Particle>       objects;
    CIVector<LinkConstraint> constraints;
    // Simulator iterations count
    uint32_t solver_iterations;
    uint32_t sub_steps;

    PhysicSolver()
        : solver_iterations(1)
        , sub_steps(16)
    {}

    void update(float dt)
    {
        const float sub_step_dt = dt / to<float>(sub_steps);
        removeBrokenLinks();
        for (uint32_t i(sub_steps); i--;) {
            applyGravity();
            applyAirFriction();
            updatePositions(sub_step_dt);
            solveConstraints();
            updateDerivatives(sub_step_dt);
        }
    }

    void applyGravity()
    {
        const sf::Vector2f gravity(0.0f, 1500.0f);
        for (Particle& p : objects) {
            p.forces += gravity * p.mass;
        }
    }

    void applyAirFriction()
    {
        const float friction_coef = 0.5f;
        for (Particle& p : objects) {
            p.forces -= p.velocity * friction_coef;
        }
    }

    void updatePositions(float dt)
    {
        for (Particle& p : objects) {
            p.update(dt);
        }
    }

    void updateDerivatives(float dt)
    {
        for (Particle& p : objects) {
            p.updateDerivatives(dt);
        }
    }

    void solveConstraints()
    {
        for (uint32_t i(solver_iterations); i--;) {
            for (LinkConstraint &l: constraints) {
                l.solve();
            }
        }
    }

    void removeBrokenLinks()
    {
        for (LinkConstraint& l : constraints) {
            if (!l.isValid()) {
                constraints.erase(l.id);
            }
        }
    }

    civ::ID addParticle(sf::Vector2f position)
    {
        const civ::ID particle_id = objects.emplace_back(position);
        objects[particle_id].id = particle_id;
        return particle_id;
    }

    void addLink(civ::ID particle_1, civ::ID particle_2, float max_elongation_ratio = 1.5f)
    {
        const civ::ID link_id = constraints.emplace_back(objects.getRef(particle_1), objects.getRef(particle_2));
        constraints[link_id].id = link_id;
        constraints[link_id].max_elongation_ratio = max_elongation_ratio;
    }

    void map(const std::function<void(Particle&)>& callback)
    {
        for (Particle& p : objects) {
            callback(p);
        }
    }
};
