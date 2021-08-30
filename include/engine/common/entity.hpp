#pragma once
#include "engine/physics/physics.hpp"
#include "engine/render/object_renderer.hpp"


struct Entity
{
    PhysicObject physic_object;
    ObjectRenderer::Metadata graphic_data;

    Entity() = default;
    Entity(PhysicObject &object)
        : physic_object(object)
    {
    }

    Entity(uint32_t width, uint32_t height)
        : physic_object(width, height, 0.0f, 0.0f)
    {
    }

    void setTexture(const sf::Texture &t)
    {
        graphic_data.texture = &t;
        graphic_data.texture_step = sf::Vector2f(1.0f, 1.0f);
        graphic_data.texture_offset = sf::Vector2f(0.0f, 0.0f);
    }

    void setFitTexture(const sf::Texture &t)
    {
        graphic_data.texture = &t;
        graphic_data.texture_step = sf::Vector2f(t.getSize().x / float(physic_object.width), t.getSize().y / float(physic_object.height));
        graphic_data.texture_offset = sf::Vector2f(0.0f, 0.0f);
    }

    void setAtomTexture(const sf::Texture &t)
    {
        graphic_data.texture = &t;
        graphic_data.texture_step = sf::Vector2f(t.getSize().x, t.getSize().y);
        graphic_data.texture_offset = sf::Vector2f(0.0f, 0.0f);
    }
};
