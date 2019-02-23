// Test InputManager Main
// Dale Armstrong

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include "InputManager.hpp"
#include "Actor.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Test");
    sf::Clock clock;

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/TestMap.png");
    sf::Sprite testMap(backgroundTexture);
    testMap.setScale(sf::Vector2f(2.f,2.f));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("images/survivor-idle_knife_0.png");
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    playerSprite.setOrigin(sf::Vector2f(playerTexture.getSize()) / 2.f);
    playerSprite.setPosition(sf::Vector2f(window.getSize() / 2u));
    playerSprite.setRotation(0);

    sf::View view(sf::FloatRect(620, 3130, window.getSize().x, window.getSize().y));
    window.setView(view);

    Actor player(view);
    InputManager input(player, playerSprite, view, window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        input.manageInput(event);

        window.clear(sf::Color::Black);
        window.setView(view);
        window.draw(testMap);
        window.draw(playerSprite);
        window.display();
    }

    return 0;
}
