#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "engine/window_context_handler.hpp"
#include "engine/physics/physics.hpp"
#include "renderer.hpp"
#include "wind.hpp"


void applyForceOnCloth(sf::Vector2f position, float radius, sf::Vector2f force, PhysicSolver& solver)
{
    for (Particle& p : solver.objects) {
        const sf::Vector2f v = position - p.position;
        if (v.x * v.x + v.y * v.y < radius * radius) {
            p.forces += force;
        }
    }
}


int main()
{
	const int32_t window_width = 2500;
	const int32_t window_height = 1500;
	WindowContextHandler app("Cloth", {window_width, window_height}, sf::Style::Default);

    PhysicSolver solver;
    Renderer renderer(solver);

    const uint32_t cloth_width = 150;
    const uint32_t cloth_height = 120;
    const float links_length = 10.0f;
    const float start_x = (window_width - (cloth_width - 1) * links_length) * 0.5f;

    for (uint32_t y(0); y < cloth_height; ++y) {
        for (uint32_t x(0); x < cloth_width; ++x) {
            const uint32_t id = solver.addParticle(
                sf::Vector2f(start_x + x * links_length, y * links_length)
            );

            if (x > 0) {
                solver.addLink(id-1, id);
            }

            if (y > 0) {
                solver.addLink(id-cloth_width, id);
            } else {
                solver.objects[id].moving = false;
            }
        }
    }

	const float dt = 1.0f / 60.0f;

    sf::Vector2f last_mouse_position;
    bool clicking = false;
    bool erasing = false;
    app.getEventManager().addMousePressedCallback(sf::Mouse::Right, [&](sfev::CstEv) {
        clicking = true;
        last_mouse_position = app.getWorldMousePosition();
    });
    app.getEventManager().addMouseReleasedCallback(sf::Mouse::Right, [&](sfev::CstEv) {
        clicking = false;
    });
    app.getEventManager().addMousePressedCallback(sf::Mouse::Middle, [&](sfev::CstEv) {
        erasing = true;
    });
    app.getEventManager().addMouseReleasedCallback(sf::Mouse::Middle, [&](sfev::CstEv) {
        erasing = false;
    });

	while (app.run()) {
        if (clicking) {
            const sf::Vector2f mouse_position = app.getWorldMousePosition();
            const sf::Vector2f mouse_speed = mouse_position - last_mouse_position;
            last_mouse_position = mouse_position;
            applyForceOnCloth(mouse_position, 100.0f, mouse_speed * 8000.0f, solver);
        }

        if (erasing) {
            const sf::Vector2f mouse_position = app.getWorldMousePosition();
            for (Particle& p : solver.objects) {
                const float radius = 100.0f;
                const sf::Vector2f v = mouse_position - p.position;
                if (v.x * v.x + v.y * v.y < radius * radius) {
                    solver.objects.erase(p.id);
                }
            }
        }

        solver.update(dt);

        RenderContext& render_context = app.getRenderContext();
        render_context.clear();
        renderer.render(render_context);
        render_context.display();
	}

	return 0;
}
