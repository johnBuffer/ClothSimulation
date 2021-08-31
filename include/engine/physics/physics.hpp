#pragma once
#include "engine/common/index_vector.hpp"
#include "engine/common/math.hpp"


struct Particle
{
    uint32_t id = 0;
    float mass = 1.0f;
    sf::Vector2f position;
    sf::Vector2f position_old;
    sf::Vector2f velocity;
    sf::Vector2f forces;
    bool moving = true;

    Particle() = default;

    explicit
    Particle(sf::Vector2f pos)
        : position(pos)
        , position_old(pos)
    {}

    void update(float dt)
    {
        if (!moving) return;
        position_old = position;
        velocity += (forces / mass) * dt;
        position += velocity * dt;
    }

    void updateDerivatives(float dt)
    {
        velocity = (position - position_old) / dt;
        forces = {};
    }

    void move(sf::Vector2f v)
    {
        if (!moving) return;
        position += v;
    }
};


using ParticleRef = civ::Ref<Particle>;


struct LinkConstraint
{
    ParticleRef particle_1;
    ParticleRef particle_2;
    float distance = 1.0f;
    float strength = 1.0f;
    float max_elongation_ratio = 1.5f;
    bool broken = false;
    uint32_t id = 0;

    LinkConstraint() = default;

    LinkConstraint(ParticleRef p_1, ParticleRef p_2)
        : particle_1(p_1)
        , particle_2(p_2)
    {
        distance = MathVec2::length(p_1->position - p_2->position);
    }

    [[nodiscard]]
    bool isValid() const
    {
        return particle_2 && particle_1 && !broken;
    }

    void solve()
    {
        if (!isValid()) { return; }
        Particle& p_1 = *particle_1;
        Particle& p_2 = *particle_2;
        const sf::Vector2f v = p_1.position - p_2.position;
        const float dist = MathVec2::length(v);
        if (dist > distance) {
            broken = dist > distance * max_elongation_ratio;
            const sf::Vector2f n = v / dist;
            const float c = distance - dist;
            const sf::Vector2f p = -(c * strength) / (p_1.mass + p_2.mass) * n;
            // Apply position correction
            p_1.move(-p / p_1.mass);
            p_2.move( p / p_2.mass);
        }
    }
};


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
        removeLinks();
        for (uint32_t i(sub_steps); i--;) {
            applyGravity();
            applyAirFriction();
            updatePositions(sub_step_dt);
            for (uint32_t k(solver_iterations); k--;) {
                solveConstraints();
            }
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
        for (LinkConstraint& l : constraints) {
            l.solve();
        }
    }

    void removeLinks()
    {
        for (LinkConstraint& l : constraints) {
            if (!l.isValid()) {
                constraints.erase(l.id);
            }
        }
    }

    uint32_t addParticle(sf::Vector2f position)
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

    void map(std::function<void(Particle&)> callback)
    {
        for (Particle& p : objects) {
            callback(p);
        }
    }
};
