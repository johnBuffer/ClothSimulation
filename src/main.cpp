#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "World.hpp"


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cloth", sf::Style::Default);
    window.setVerticalSyncEnabled(false);

    World world;

    world.addCloth(300, 0, 100, 75);
    bool click = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                click = true;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                click = false;
            }

        }

        window.clear(sf::Color::Black);

        sf::Vector2i localPosition = sf::Mouse::getPosition(window);

        if (click)
            world.update(localPosition.x, localPosition.y);
        else
            world.update(-10000.0f, -10000.0f);

        world.render(window);

        window.display();
    }

    return 0;
}
